#include "PipelineSimulation.h"

PipelineSimulation::PipelineSimulation(TraceInput* trace_input, int width) {
    instruction_manager = new InstructionManager();
    stats_manager = new StatsManager();
    this->trace_input = trace_input;
    this->width = width;
    current_cycle = 0;
    instruction_in_system = 0;
}

PipelineSimulation::~PipelineSimulation() {
    delete instruction_manager;
    delete stats_manager;
}

/**
 * Write Back
 * - WB -> Retire
 */
void PipelineSimulation::writeBackToRetire() {
    Instruction instruction;
    while (!instruction_manager->isWriteBackEmpty()) {
        instruction = instruction_manager->dequeueWriteBack();
        stats_manager->retireInstruction(instruction);
        instruction_in_system--;
    }
}

/**
 * Memory
 * - Mem -> WB
 */    
void PipelineSimulation::memoryToWriteBack() {
    Instruction instruction;
    int count = 0;
    
    instruction_manager->memorizeInstructions(width);

    while (count < width && !instruction_manager->isMemoryEmpty()) {
        instruction = instruction_manager->dequeueMemory();
        instruction_manager->enqueueWriteBack(instruction);
        count++;
    }
}

/**
 * Execute
 * - Ex -> MEM
 * - Except:
 * -   Only 1 Load or Store
 */
void PipelineSimulation::executeToMemory() {
    Instruction instruction;
    bool load_instruction = false;
    bool store_instruction = false;
    InstructionType type;
    int count = 0;

    instruction_manager->executeInstructions(width);

    while (count < width && !instruction_manager->isExecuteEmpty()) {
        type = instruction_manager->nextTypeExecute();
        if (type == InstructionType::LOAD) {
            if (load_instruction) {
                break;
            } else {
                load_instruction = true;
            }
        } else if (type == InstructionType::STORE) {
            if (store_instruction) {
                break;
            } else {
                store_instruction = true;
            }
        }

        instruction = instruction_manager->dequeueExecute();
        instruction_manager->enqueueMemory(instruction);
        count++;
    }
}

/**
 * Decode
 * - ID -> Ex
 * - Except:
 * -    Dependencies
 * -    Only 1 Branch/Int/Float
 */
void PipelineSimulation::decodeToExecute() {
    Instruction instruction;
    bool integer_instruction = false;
    bool floating_instruction = false;
    bool branch_instruction = false;
    InstructionType type;
    int count = 0;

    while (count < width && !instruction_manager->isDecodeEmpty()) {
        if (!instruction_manager->isNextDecodeSatisfied()) {
            break;
        }

        type = instruction_manager->nextTypeDecode();

        if (type == InstructionType::INTEGER) {
            if (integer_instruction) {
                break;
            } else {
                integer_instruction = true;
            }
        } else if (type == InstructionType::FLOATING_POINT) {
            if (floating_instruction) {
                break;
            } else {
                floating_instruction = true;
            }
        } else if (type == InstructionType::BRANCH) {
            if (branch_instruction) {
                break;
            } else {
                branch_instruction = true;
            }
        }

        instruction = instruction_manager->dequeueDecode();
        instruction_manager->enqueueExecute(instruction);
        count++;
    }
}

/**
 * Fetch to Decode
 * - IF -> ID
 */
void PipelineSimulation::fetchToDecode() {
    Instruction instruction;
    int count = 0;
    while (count < width && !instruction_manager->isFetchEmpty()) {
        instruction = instruction_manager->dequeueFetch();
        instruction_manager->enqueueDecode(instruction);
        count++;
    }
}

/**
 * New To Fetch
 * - Fetch new instruction from trace
 * - unless previous branch haven't passed
 */
void PipelineSimulation::newToFetch() {
    Instruction instruction;
    int count = 0;
    while (count < width && trace_input->needNewInstruction() && !instruction_manager->branch_halt) {
        instruction = trace_input->getNextInstruction();
        instruction_manager->enqueueFetch(instruction);
        instruction_in_system++;

        if (instruction.type == InstructionType::BRANCH) {
            instruction_manager->branch_halt = true;
        }
        count++;
    }
}

void PipelineSimulation::start() {
    while ( instruction_in_system != 0 || trace_input->needNewInstruction()) {
        writeBackToRetire();
        memoryToWriteBack();
        executeToMemory();
        decodeToExecute();
        fetchToDecode();
        newToFetch();
        
        current_cycle++;
    }

    stats_manager->printReport(current_cycle);
    trace_input->closeFile();
}
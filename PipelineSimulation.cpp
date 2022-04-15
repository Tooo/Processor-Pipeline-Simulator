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
void PipelineSimulation::writeBack() {
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
void PipelineSimulation::memory() {
    Instruction instruction;
    for (int i = 0; i < width; i++) {
        if (instruction_manager->isMemoryEmpty()) {
            break;
        }
        instruction = instruction_manager->dequeueMemory();
        instruction_manager->enqueueWriteBack(instruction);
    }
}

/**
 * Execute
 * - Ex -> MEM
 * - Except:
 * -   Only 1 Load or Store
 */
void PipelineSimulation::execute() {
    Instruction instruction;
    bool load_instruction = false;
    bool store_instruction = false;
    InstructionType type;

    for (int i = 0; i < width; i++) {
        if (instruction_manager->isExecuteEmpty()) {
            break;
        }

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
        } else if (type == InstructionType::BRANCH) {
            instruction_manager->branch_halt = false;
        }

        instruction = instruction_manager->dequeueExecute();
        instruction_manager->enqueueMemory(instruction);
    }
}

/**
 * Decode
 * - ID -> Ex
 * - Except:
 * -    Dependencies
 * -    Only 1 Branch/Int/Float
 */
void PipelineSimulation::decode() {
    Instruction instruction;
    bool integer_instruction = false;
    bool floating_instruction = false;
    bool branch_instruction = false;
    InstructionType type;

    for (int i = 0; i < width; i++) {
        if (instruction_manager->isDecodeEmpty()) {
            break;
        }

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
    }
}

/**
 * Fetch
 * - IF -> ID
 */
void PipelineSimulation::fetch() {
    Instruction instruction;
    for (int i = 0; i < width; i++) {
        if (instruction_manager->isFetchEmpty()) {
            break;
        }
        instruction = instruction_manager->dequeueFetch();
        instruction_manager->enqueueDecode(instruction);
    }
}

/**
 * Fetch New
 * - Fetch new instruction from trace
 * - unless previous branch haven't passed
 */
void PipelineSimulation::fetchNew() {
    Instruction instruction;
    for (int i = 0; i < width; i++) {
        if (!trace_input->needNewInstruction()) {
            break;
        }

        if (instruction_manager->branch_halt) {
            break;
        }

        instruction = trace_input->getNextInstruction();
        instruction_manager->enqueueFetch(instruction);
        instruction_in_system++;

        if (instruction.type == InstructionType::BRANCH) {
            instruction_manager->branch_halt = true;
            break;
        }
    }

}

void PipelineSimulation::start() {
    while ( instruction_in_system != 0 || trace_input->needNewInstruction()) {
        writeBack();
        memory();
        execute();
        decode();
        fetch();
        fetchNew();
        
        current_cycle++;
    }

    stats_manager->printReport(current_cycle);
    trace_input->closeFile();
}
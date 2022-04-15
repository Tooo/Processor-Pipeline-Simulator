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
        instruction = instruction_manager->removeWriteBack();
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
        instruction = instruction_manager->removeMemory();
        instruction_manager->insertWriteBack(instruction);
    }
}

/**
 * Execute
 * - Ex -> MEM, max 1 load/store 
 */
void PipelineSimulation::execute() {





    Instruction instruction;
    while (!instruction_manager->isExecuteEmpty()) {
        instruction = instruction_manager->removeExecute();
        instruction_manager->enqueueMemory(instruction);
    }

    bool integer_instruction = false;
    bool floating_instruction = false;
    bool branch_instruction = false;
    InstructionType type;

    for (int i = 0; i < width; i++) {
        if (instruction_manager->isExecuteQueueEmpty()) {
            break;
        }
        type = instruction_manager->nextTypeExecute();

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
            instruction_manager->branch_halt = false;
            if (branch_instruction) {
                break;
            } else {
                branch_instruction = true;
            }
        }

        if (!instruction_manager->isNextExecuteSatisfied()) {
            break;
        }

        instruction = instruction_manager->dequeueExecute();
        instruction_manager->insertExecute(instruction);
    }

        Instruction instruction;
    while (!instruction_manager->isMemoryEmpty()) {
        instruction = instruction_manager->removeMemory();
        instruction_manager->enqueueWriteBack(instruction);
    }

    bool load_instruction = false;
    bool store_instruction = false;
    InstructionType type;

    for (int i = 0; i < width; i++) {
        if (instruction_manager->isMemoryQueueEmpty()) {
            break;
        }
        type = instruction_manager->nextTypeMemory();

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

        instruction = instruction_manager->dequeueMemory();
        instruction_manager->insertMemory(instruction);
    }
}

/**
 * Decode
 * - Remove decode -> Enqueue execute queue
 * - Loop to width
 * - Dequeue decode -> insert decode
 * - Unless no more in decode queue
 */
void PipelineSimulation::decode() {
    Instruction instruction;
    while (!instruction_manager->isDecodeEmpty()) {
        instruction = instruction_manager->removeDecode();
        instruction_manager->enqueueExecute(instruction);
    }

    for (int i = 0; i < width; i++) {
        if (instruction_manager->isDecodeQueueEmpty()) {
            break;
        }
        instruction = instruction_manager->dequeueDecode();
        instruction_manager->insertDecode(instruction);
    }
}

/**
 * Fetch
 * - 
 */
void PipelineSimulation::fetch() {
    Instruction instruction;
    for (int i = 0; i < width; i++) {
        if (instruction_manager->isFetchEmpty()) {
            break;
        }
        instruction = instruction_manager->removeFetch();
        instruction_manager->insertDecode(instruction);
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
        instruction_manager->insertFetch(instruction);
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
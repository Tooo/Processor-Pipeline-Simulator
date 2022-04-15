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
 * Fetch
 * - Remove fetch -> Enqueue decode queue
 * - If not branch halt
 * - Loop to width 
 * - Get Next Instruction -> Insert fetch
 * - Unless branch halt or no more next instructions
 */
void PipelineSimulation::fetch() {
    Instruction instruction;
    while (!instruction_manager->isFetchEmpty()) {
        instruction = instruction_manager->removeFetch();
        instruction_manager->enqueueDecode(instruction);
    }

    if (!instruction_manager->branch_halt) {
        for (int i = 0; i < width; i++) {
            if (!trace_input->needNewInstruction()) {
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
 * Execute
 * - Remove execute -> Enqueue memory queue
 * - Loop to width
 * - Dequeue execute -> insert execute
 * - Unless no more in execute queue
 * - or if more than one integer
 * - or if more than one floating
 * - or int/float dependencies in execute
 * - or load/store dependencies in memoryqueue
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
}

/**
 * Memory
 * - Remove execute -> Enqueue memory queue
 * - Loop to width
 * - Dequeue execute -> insert execute
 * - Unless no more in execute queue
 * - or if more than one load
 * - or if more than one store
 */    
void PipelineSimulation::memory() {
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
        
void PipelineSimulation::writeBack() {
    Instruction instruction;
    while (!instruction_manager->isWriteBackEmpty()) {
        instruction = instruction_manager->removeWriteBack();
        stats_manager->retireInstruction(instruction);
        instruction_in_system--;
    }

    for (int i = 0; i < width; i++) {
        if (instruction_manager->isWriteBackQueueEmpty()) {
            break;
        }
        instruction = instruction_manager->dequeueWriteBack();
        instruction_manager->insertWriteBack(instruction);
    }
}

void PipelineSimulation::start() {
    while ( instruction_in_system != 0 || trace_input->needNewInstruction()) {
        fetch();
        decode();
        execute();
        memory();
        writeBack();

        current_cycle++;
    }

    stats_manager->printReport(current_cycle);
    trace_input->closeFile();
}
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

            instruction = *trace_input->getNextInstruction();
            instruction_manager->insertFetch(instruction);

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
        }

        if (!instruction_manager->isNextInstructionSatisfied()) {
            break;
        }

        instruction = instruction_manager->dequeueExecute();
        instruction_manager->insertExecute(instruction);
    }
}
        
void PipelineSimulation::memory() {

}
        
void PipelineSimulation::writeBack() {

}

void PipelineSimulation::start() {
    while ( instruction_in_system != 0 || trace_input->needNewInstruction()) {
        
        Instruction* instruction = trace_input->getNextInstruction();
        //cout << instruction->toString();
        stats_manager->retireInstruction(*instruction);
        delete instruction;

        current_cycle++;
    }

    stats_manager->printReport(current_cycle);
    trace_input->closeFile();
}
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
 * - Loop to width get Next Instruction
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

void PipelineSimulation::decode() {

}

void PipelineSimulation::execute() {

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
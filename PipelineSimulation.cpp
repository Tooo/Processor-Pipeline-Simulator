#include "PipelineSimulation.h"

PipelineSimulation::PipelineSimulation(TraceInput* trace_input, int width) {
    instruction_manager = new InstructionManager();
    stats_manager = new StatsManager();
    this->trace_input = trace_input;
    this->width = width;
    current_cycle = 0;
}

PipelineSimulation::~PipelineSimulation() {
    delete instruction_manager;
    delete stats_manager;
}

void PipelineSimulation::start() {
    while (trace_input->needNewInstruction()) {
        current_cycle++;
        Instruction* instruction = trace_input->getNextInstruction();
        //cout << instruction->toString();
        stats_manager->retireInstruction(*instruction);
        delete instruction;
    }

    stats_manager->printReport(current_cycle);
    trace_input->closeFile();
}
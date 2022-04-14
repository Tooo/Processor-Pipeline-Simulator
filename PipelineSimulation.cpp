#include "PipelineSimulation.h"

PipelineSimulation::PipelineSimulation(TraceInput* trace_input, int width) {
    this->trace_input = trace_input;
    this->width = width;
}

PipelineSimulation::~PipelineSimulation() {
    delete instruction_manager;
    delete stats_manager;
}

void PipelineSimulation::start() {
    while (trace_input->needNewInstruction()) {
        Instruction* instruction = trace_input->getNextInstruction();
        cout << instruction->toString();
    }

    trace_input->closeFile();
}
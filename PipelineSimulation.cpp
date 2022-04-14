#include "PipelineSimulation.h"

PipelineSimulation::PipelineSimulation(TraceInput* trace_input, int width) {
    this->trace_input = trace_input;
    this->width = width;
}

PipelineSimulation::~PipelineSimulation() {

}

void PipelineSimulation::start() {
    while (trace_input->needNewInstruction()) {
        Instruction* instruction = trace_input->getNextInstruction();
        cout << instruction->toString();
    }

}
#include "PipelineSimulation.h"

PipelineSimulation::PipelineSimulation(TraceInput* trace_input, int width) {
    this->trace_input = trace_input;
    this->width = width;
}

PipelineSimulation::~PipelineSimulation() {

}

void PipelineSimulation::start() {
    for (int i = 0; i < 100; i++) {
        Instruction instruction = trace_input->nextInstruction();
        cout << instruction.toString();
    }

}
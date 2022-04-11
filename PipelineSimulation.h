#include "TraceInput.h"

#ifndef PIPELINESIMULATION_H_
#define PIPELINESIMULATION_H_
class PipelineSimulation {
    private:
        int width;
        TraceInput* trace_input;
    
    public:
        PipelineSimulation(TraceInput* trace_input, int width);
        ~PipelineSimulation();
        
        void start();
};
#endif
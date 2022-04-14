#include "TraceInput.h"
#include "InstructionManager.h"
#include "StatsManager.h"

#ifndef PIPELINESIMULATION_H_
#define PIPELINESIMULATION_H_
class PipelineSimulation {
    private:
        int width;
        TraceInput* trace_input;
        InstructionManager* instruction_manager;
        StatsManager* stats_manager;
    
    public:
        PipelineSimulation(TraceInput* trace_input, int width);
        ~PipelineSimulation();
        
        void start();
};
#endif
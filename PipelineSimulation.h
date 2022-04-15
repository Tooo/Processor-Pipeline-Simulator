#include "TraceInput.h"
#include "InstructionManager.h"
#include "StatsManager.h"

#ifndef PIPELINESIMULATION_H_
#define PIPELINESIMULATION_H_
class PipelineSimulation {
    private:
        InstructionManager* instruction_manager;
        StatsManager* stats_manager;
        int width;
        TraceInput* trace_input;
        int current_cycle;
        int instruction_in_system;

        void writeBack();
        void memory();
        void execute();
        void decode();
        void fetch();
        void fetchNew();

        
    public:
        PipelineSimulation(TraceInput* trace_input, int width);
        ~PipelineSimulation();
        
        void start();
};
#endif
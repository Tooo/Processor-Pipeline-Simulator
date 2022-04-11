#include <iostream> 
using namespace std;

#include "PipelineSimulation.h"
#include "TraceInput.h"

int main (int argc, char* argv[]) {
    // ./proj2 trace_file_name start_inst inst_count W

    if (argc < 5) {
        cout << "Insufficient number of arguments provided!" << endl;
        return 0;
    }

    string trace_file_name = argv[1];
    int start_inst = atoi(argv[2]);
    int inst_count = atoi(argv[3]);
    int width = atoi(argv[4]);

    cout << "Simulating Processor Pipeline" << endl;
    cout << "Trace File Name: " << trace_file_name << endl;
    printf("start_inst: %d, inst_count: %d, width: %d\n", start_inst, inst_count, width);

    TraceInput* trace_input = new TraceInput(trace_file_name, start_inst, inst_count);
    PipelineSimulation* pipeline_simulation = new PipelineSimulation(trace_input, width);

    pipeline_simulation->start();

    delete trace_input;
    delete pipeline_simulation;
}
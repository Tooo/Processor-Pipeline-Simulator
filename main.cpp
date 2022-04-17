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

    if (start_inst <= 0) {
        cout << "Invalid start trace number! Start trace must be greater than 0!" << endl;
        return 0;
    }

    if (inst_count <= 0) {
        cout << "Invalid trace count! Trace count must be greater than 0!" << endl;
        return 0;
    }

    if (width <= 0) {
        cout << "Invalid width! Width must be greater than 0!" << endl;
        return 0;
    }

    TraceInput* trace_input = new TraceInput(trace_file_name, start_inst, inst_count);

    if (trace_input->file_failed) {
        cout << "File failed to open! Make sure the file exists and spelled correctly!" << endl;
        delete trace_input;
        return 0;
    }

    PipelineSimulation* pipeline_simulation = new PipelineSimulation(trace_input, width);

    cout << "Simulating Processor Pipeline" << endl;
    cout << "Trace File Name: " << trace_file_name << endl;
    printf("start_inst: %d, inst_count: %d, width: %d\n", start_inst, inst_count, width);

    pipeline_simulation->start();

    delete trace_input;
    delete pipeline_simulation;
}
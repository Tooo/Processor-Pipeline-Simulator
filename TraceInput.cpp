#include "TraceInput.h"
#include <iostream>
#include <fstream>
#include <string>


TraceInput::TraceInput(string trace_file_name, int start_inst, int inst_count) {
    this->trace_file_name = trace_file_name;
    this->start_inst = start_inst;
    this->inst_count = inst_count;

    prepFile();
}

int TraceInput::getCurrLine(){
    return curr_line;
}

void TraceInput::prepFile(){

    std::ifstream traceFile (trace_file_name);

    if(traceFile.is_open()){

        while(curr_line < start_inst){
            traceFile.get();
            curr_line++;
        }
    }
}

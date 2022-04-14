#include <string>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

#include "Instruction.h"

#ifndef TRACEINPUT_H_
#define TRACEINPUT_H_
class TraceInput {
    private:
        string trace_file_name;
        int start_inst;
        int inst_count;

        int curr_line;
        ifstream trace_file;

    public:
        TraceInput(string trace_file_name, int start_inst, int inst_count);

        void prepFile();
        bool needNewInstruction();
        Instruction* getNextInstruction();

};
#endif
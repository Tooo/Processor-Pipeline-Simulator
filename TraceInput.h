#include <string>
#include <iostream>
#include <fstream>
#include "Instruction.h"
#include <bits/stdc++.h>

using namespace std;

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
        int getCurrLine();
        void prepFile();
        Instruction getNextInstruction();

};
#endif
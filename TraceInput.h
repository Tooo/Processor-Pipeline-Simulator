#include <string>
using namespace std;

#ifndef TRACEINPUT_H
#define TRACEINPUT_H
class TraceInput {
    private:
        string trace_file_name;
        int start_inst;
        int inst_count;
    
    public:
        TraceInput(string trace_file_name, int start_inst, int inst_count);

};
#endif
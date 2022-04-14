#include "TraceInput.h"


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

    traceFile.open(trace_file_name);

    if(traceFile.is_open()){

        while(curr_line < start_inst){
            traceFile.get();
            curr_line++;
        }
    }
}

Instruction TraceInput::nextInstruction(){

    string line;

    if(traceFile.is_open()){
        line = traceFile.get();

        //split string
        string info = "";
        int count = 0;
         for (auto rem : line) 
        { 
            if (rem==',') 
            {
                
                if(count == 0){
                    //initial address
                }
                else if(count == 1){
                    //instruction type
                }
                else{
                    //dependency
                }
                
                info=""; 
                count++;
            } 
            else
            { 
                info=info+rem; 
            } 
        }  
    }
    else{
       cout << "File not open!\n"; 
    }
}



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

    trace_file.open(trace_file_name);

    if(trace_file.is_open()){

        while(curr_line < start_inst){
            trace_file.get();
            curr_line++;
        }
    }
}

Instruction TraceInput::getNextInstruction(){
    string line;
    Instruction* op = new Instruction();

    if(trace_file.is_open()){
        getline(trace_file, line);
        //cout << line << endl;
        
        //split string
        string info = "";
        int count = 0;
         for (auto rem : line) 
        { 
            if (rem==',') 
            {
                
                if(count == 0){
                    //initial address
                    op->program_counter = info;
                }
                else if(count == 1){
                    //instruction type => convert it to int then enum
                    int type = stoi(info);
                    cout << info << endl;
                    op->type = static_cast<InstructionType>(type);
                    //is there a more succint way to do this?
                }
                else{
                    //dependencies
                    op->addDependency(info);
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
    return *op;
}



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

    if (trace_file.is_open()) {

        while (curr_line < start_inst) {
            trace_file.get();
            curr_line++;
        }
    }
}

Instruction* TraceInput::getNextInstruction(){
    if (!trace_file.is_open()) {
        cout << "File failed to open!\n";
        return NULL;
    }

    string line;
    getline(trace_file, line);
    vector<string> input;
    stringstream line_stream(line);

    while (line_stream.good()) {
        string sub_string;
        getline(line_stream, sub_string, ',');
        input.push_back(sub_string);
    }

    int size = input.size();

    if (size < 2) {
        cout << "Invalid line\n";
        return NULL;
    }

    Instruction * instruction = new Instruction();
    instruction->program_counter = input[0];

    int type = stoi(input[1]);
    instruction->type = static_cast<InstructionType>(type);

    for (int i = 2; i < size; i++) {
        instruction->addDependency(input[i]);
    }

    return instruction;
}



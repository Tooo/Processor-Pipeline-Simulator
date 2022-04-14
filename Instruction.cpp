#include <sstream>

#include "Instruction.h"

Instruction::Instruction(string program_counter, InstructionType type, vector<string> dependencies) {
    this->program_counter = program_counter;
    this->type = type;
    this->dependencies = dependencies;
}


Instruction::Instruction() {
    dependencies = {};
}

void Instruction::addDependency(string dependency){
    dependencies.push_back(dependency);
}

string Instruction::toString() {
    stringstream ss;
    ss << "PC: " << program_counter;
    ss << " Type: " << int(type);

    int size = int(dependencies.size());

    if (size != 0) {
        ss << " Dependencies ";
        for (int i = 0; i < size-1; i++) {
            ss << dependencies[i] << ", ";
        }
        ss << dependencies[size-1];
    }
    
    ss << endl;
    return ss.str();
}
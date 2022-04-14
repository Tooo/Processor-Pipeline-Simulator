#include <sstream>

#include "Instruction.h"

Instruction::Instruction(string program_counter, InstructionType type, vector<string> dependencies) {
    this->program_counter = program_counter;
    this->type = type;
    this->dependencies = dependencies;
}


Instruction::Instruction() {
    dependencies = vector <string> (5);
}

void Instruction::addDependency(string dependency){
    dependencies.push_back(dependency);
}

string Instruction::toString() {
    stringstream ss;
    ss << "PC: " << program_counter;
    ss << " Type: " << int(type);
    ss << " Dependeices";

    for (int i = 0; i < dependencies.size(); i++) {
        ss << dependencies[i];
    }
    ss << endl;
    return ss.str();
}
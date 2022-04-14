#include "Instruction.h"

Instruction::Instruction(string program_counter, InstructionType type, vector<string> dependencies) {
    this->program_counter = program_counter;
    this->type = type;
    this->dependencies = dependencies;
}


Instruction::Instruction(){
    dependencies = vector <string> (5);
}

void Instruction::addDependency(string dependency){
    dependencies.push_back(dependency);
}


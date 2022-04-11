#include "Instruction.h"

Instruction::Instruction(std::string program_counter, InstructionType type, std::vector<std::string> dependencies) {
    this->program_counter = program_counter;
    this->type = type;
    this->dependencies = dependencies;
}
#include <string>
#include <vector>

#ifndef INSTRUCTION_H
#define INSTRUCTION_H
/*
    Instruction Type
  - Enum class for Instruction Type
*/
enum class InstructionType {
    INTEGER,
    FLOATING_POINT,
    BRANCH,
    LOAD,
    STORE
};

class Instruction {
    public:
        Instruction();

        std::string program_counter;
        InstructionType type;
        std::vector<std::string> dependencies;

};
#endif
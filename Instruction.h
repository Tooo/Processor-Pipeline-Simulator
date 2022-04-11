#include <string>
#include <vector>
using namespace std;

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
        Instruction(string program_counter, InstructionType type, vector<string> dependencies);

        string program_counter;
        InstructionType type;
        vector<string> dependencies;

};
#endif
#include <string>
#include <vector>
using namespace std;

#ifndef INSTRUCTION_H_
#define INSTRUCTION_H_
/*
    Instruction Type
  - Enum class for Instruction Type
*/
enum class InstructionType {
    NAN,
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
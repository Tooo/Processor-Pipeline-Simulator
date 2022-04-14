#include <vector>
#include <deque>
using namespace std;

#include "Instruction.h"

#ifndef PIPELINESIMULATION_H_
#define PIPELINESIMULATION_H_
class InstructionManager {
    public:
        deque<Instruction> fetch_queue;
        vector<Instruction> fetch_vector;

        deque<Instruction> decode_queue;
        vector<Instruction> decode_vector;

        deque<Instruction> execute_queue;
        vector<Instruction> execute_vector;

        deque<Instruction> memory_queue;
        vector<Instruction> memory_vector;

        deque<Instruction> retire_queue;
        vector<Instruction> retire_vector;

};
#endif
#include <vector>
#include <deque>
using namespace std;

#include "Instruction.h"

#ifndef PIPELINESIMULATION_H_
#define PIPELINESIMULATION_H_
class InstructionManager {
    public:
        InstructionManager();

        deque<Instruction> fetch_queue;
        vector<Instruction> fetch_vector;
        bool branch_halt;

        deque<Instruction> decode_queue;
        vector<Instruction> decode_vector;

        deque<Instruction> execute_queue;
        vector<Instruction> execute_vector;
        bool integer_in_execute;
        bool floating_in_execute;
        bool branch_in_execute;

        deque<Instruction> memory_queue;
        vector<Instruction> memory_vector;
        bool load_in_memory;
        bool store_in_memory;

        deque<Instruction> write_back_queue;
        vector<Instruction> write_back_vector;

};
#endif
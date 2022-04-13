#include <vector>
#include <deque>
using namespace std;

#include "Instruction.h"

#ifndef PIPELINESIMULATION_H_
#define PIPELINESIMULATION_H_
class InstructionManager {
    private:
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
    
    public:
        void enqueueFetch(Instruction instruction);
        Instruction dequeueFetch();
        void insertFetch(Instruction instruction);
        Instruction removeFetch();

        void enqueueDecode(Instruction instruction);
        Instruction dequeueDecode();
        void insertDecode(Instruction instruction);
        Instruction removeDecode();

        void enqueueExecute(Instruction instruction);
        Instruction dequeueExecute();
        void insertExecute(Instruction instruction);
        Instruction removeExecute();

        void enqueueMemory(Instruction instruction);
        Instruction dequeueMemory();
        void insertMemory(Instruction instruction);
        Instruction removeMemory();

        void enqueueRetire(Instruction instruction);
        Instruction dequeueRetire();
        void insertRetire(Instruction instruction);
        Instruction removeRetire();

};
#endif
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
        bool isFetchQueueEmpty() {return fetch_queue.empty();}
        bool isFetchEmpty() {return fetch_vector.empty();}

        void enqueueDecode(Instruction instruction);
        InstructionType nextTypeDecode();
        Instruction dequeueDecode();
        void insertDecode(Instruction instruction);
        Instruction removeDecode();
        bool isDecodeQueueEmpty() {return decode_queue.empty();}
        bool isDecodeEmpty() {return decode_vector.empty();}

        void enqueueExecute(Instruction instruction);
        InstructionType nextTypeExecute();
        Instruction dequeueExecute();
        void insertExecute(Instruction instruction);
        Instruction removeExecute();
        bool isExecuteQueueEmpty() {return execute_queue.empty();}
        bool isExecuteEmpty() {return execute_vector.empty();}

        void enqueueMemory(Instruction instruction);
        InstructionType nextTypeMemory();
        Instruction dequeueMemory();
        void insertMemory(Instruction instruction);
        Instruction removeMemory();
        bool isMemoryQueueEmpty() {return memory_queue.empty();}
        bool isMemoryEmpty() {return memory_vector.empty();}

        void enqueueRetire(Instruction instruction);
        InstructionType nextTypeRetire();
        Instruction dequeueRetire();
        void insertRetire(Instruction instruction);
        Instruction removeRetire();
        bool isRetireQueueEmpty() {return memory_queue.empty();}
        bool isRetireEmpty() {return memory_vector.empty();}

};
#endif
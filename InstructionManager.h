#include <vector>
#include <deque>
using namespace std;

#include "Instruction.h"

#ifndef INSTRUCTIONMANAGER_H_
#define INSTRUCTIONMANAGER_H_
class InstructionManager {
    private:
        deque<Instruction> fetch_vector;

        deque<Instruction> decode_queue;
        deque<Instruction> decode_vector;

        deque<Instruction> execute_queue;
        deque<Instruction> execute_vector;

        deque<Instruction> memory_queue;
        deque<Instruction> memory_vector;

        deque<Instruction> write_back_queue;
        deque<Instruction> write_back_vector;

    public:
        InstructionManager();

        
        bool branch_halt;

        void enqueueFetch(Instruction instruction);
        Instruction dequeueFetch();
        void insertFetch(Instruction instruction);
        Instruction removeFetch();
        bool isFetchEmpty() {return fetch_vector.empty();}

        void enqueueDecode(Instruction instruction);
        Instruction dequeueDecode();
        void insertDecode(Instruction instruction);
        Instruction removeDecode();
        bool isDecodeQueueEmpty() {return decode_queue.empty();}
        bool isDecodeEmpty() {return decode_vector.empty();}

        void enqueueExecute(Instruction instruction);
        Instruction dequeueExecute();
        void insertExecute(Instruction instruction);
        Instruction removeExecute();
        InstructionType nextTypeExecute() {return execute_queue.front().type;}
        bool isNextExecuteSatisfied();
        bool isExecuteQueueEmpty() {return execute_queue.empty();}
        bool isExecuteEmpty() {return execute_vector.empty();}

        void enqueueMemory(Instruction instruction);
        Instruction dequeueMemory();
        void insertMemory(Instruction instruction);
        Instruction removeMemory();
        InstructionType nextTypeMemory() {return memory_queue.front().type;}
        bool isMemoryQueueEmpty() {return memory_queue.empty();}
        bool isMemoryEmpty() {return memory_vector.empty();}

        void enqueueWriteBack(Instruction instruction);
        Instruction dequeueWriteBack();
        void insertWriteBack(Instruction instruction);
        Instruction removeWriteBack();
        bool isWriteBackQueueEmpty() {return write_back_queue.empty();}
        bool isWriteBackEmpty() {return write_back_vector.empty();}

};
#endif
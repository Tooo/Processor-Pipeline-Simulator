#include <vector>
#include <deque>
using namespace std;

#include "Instruction.h"

#ifndef INSTRUCTIONMANAGER_H_
#define INSTRUCTIONMANAGER_H_
class InstructionManager {
    private:
        deque<Instruction> fetch_queue;
        deque<Instruction> decode_queue;
        deque<Instruction> execute_queue;
        deque<Instruction> memory_queue;
        deque<Instruction> write_back_queue;

    public:
        InstructionManager();

        bool branch_halt;

        void enqueueFetch(Instruction instruction);
        Instruction dequeueFetch();
        bool isFetchEmpty() {return fetch_queue.empty();}

        void enqueueDecode(Instruction instruction);
        Instruction dequeueDecode();
        bool isDecodeEmpty() {return decode_queue.empty();}
        InstructionType nextTypeDecode() {return decode_queue.front().type;}
        bool isNextDecodeSatisfied();

        void enqueueExecute(Instruction instruction);
        Instruction dequeueExecute();
        InstructionType nextTypeExecute() {return execute_queue.front().type;}
        bool isExecuteEmpty() {return execute_queue.empty();}
        void executeInstructions(int width);

        void enqueueMemory(Instruction instruction);
        Instruction dequeueMemory();
        bool isMemoryEmpty() {return memory_queue.empty();}
        void memorizeInstructions(int width);

        void enqueueWriteBack(Instruction instruction);
        Instruction dequeueWriteBack();
        bool isWriteBackEmpty() {return write_back_queue.empty();}

};
#endif
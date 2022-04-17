#include "InstructionManager.h"

InstructionManager::InstructionManager() {
    branch_halt = false;
}

// Fetch
void InstructionManager::enqueueFetch(Instruction instruction) {
    fetch_queue.push_back(instruction);
}

Instruction InstructionManager::dequeueFetch() {
    Instruction instruction = fetch_queue.front();
    fetch_queue.pop_front();
    return instruction;
}

// Decode
void InstructionManager::enqueueDecode(Instruction instruction) {
    decode_queue.push_back(instruction);
}

Instruction InstructionManager::dequeueDecode() {
    Instruction instruction = decode_queue.front();
    decode_queue.pop_front();
    return instruction;
}

bool InstructionManager::isNextDecodeSatisfied() {
    vector<string> dependencies = decode_queue.front().dependencies;
    int size = dependencies.size();

    for (int i = 0; i < size; i++) {
        string dependent = dependencies[i];
        Instruction instruction;
        
        int execute_size = execute_queue.size();
        for (int j = 0; j < execute_size; j++) {
            instruction = execute_queue[j];
            if (!dependent.compare(instruction.program_counter)) {
                if (!instruction.executed) {
                    return false;
                }
            }
        }

        int memory_size = memory_queue.size();
        for (int j = 0; j < memory_size; j++) {
            instruction = memory_queue[j];
            if (!dependent.compare(instruction.program_counter)) {
                if (instruction.type == InstructionType::LOAD ||instruction.type == InstructionType::STORE ) {
                    if (!instruction.memorized) {
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

// Execute
void InstructionManager::enqueueExecute(Instruction instruction) {
    execute_queue.push_back(instruction);
}

Instruction InstructionManager::dequeueExecute() {
    Instruction instruction = execute_queue.front();
    execute_queue.pop_front();
    return instruction;
}

void InstructionManager::executeInstructions(int width) {
    int size = execute_queue.size();
    int checked = 0;
    int index = 0;
    while (index < size && checked < width) {
        if (!execute_queue[index].executed) {
            execute_queue[index].executed = true;
            if (execute_queue[index].type == InstructionType::BRANCH) {
                branch_halt = false;
            }
            checked++;
        }
        index++;
    }
}



// Memory
void InstructionManager::enqueueMemory(Instruction instruction) {
    memory_queue.push_back(instruction);
}

Instruction InstructionManager::dequeueMemory() {
    Instruction instruction = memory_queue.front();
    memory_queue.pop_front();
    return instruction;
}

void InstructionManager::memorizeInstructions(int width) {
    int size = memory_queue.size();
    int checked = 0;
    int index = 0;
    while (index < size && checked < width) {
        if (!memory_queue[index].memorized) {
            memory_queue[index].memorized = true;
            checked++;
        }
        index++;
    }
}

// WriteBack
void InstructionManager::enqueueWriteBack(Instruction instruction) {
    write_back_queue.push_back(instruction);
}

Instruction InstructionManager::dequeueWriteBack() {
    Instruction instruction = write_back_queue.front();
    write_back_queue.pop_front();
    return instruction;
}
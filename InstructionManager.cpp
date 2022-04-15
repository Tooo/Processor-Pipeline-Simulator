#include "InstructionManager.h"

InstructionManager::InstructionManager() {
    branch_halt = false;
}

// Fetch
void InstructionManager::insertFetch(Instruction instruction) {
    fetch_vector.push_back(instruction);
}

Instruction InstructionManager::removeFetch() {
    Instruction instruction = fetch_vector.front();
    fetch_vector.pop_front();
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

void InstructionManager::insertDecode(Instruction instruction) {
    decode_vector.push_back(instruction);
}

Instruction InstructionManager::removeDecode() {
    Instruction instruction = decode_vector.front();
    decode_vector.pop_front();
    return instruction;
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

void InstructionManager::insertExecute(Instruction instruction) {
    execute_vector.push_back(instruction);
}

Instruction InstructionManager::removeExecute() {
    Instruction instruction = execute_vector.front();
    execute_vector.pop_front();
    return instruction;
}

bool InstructionManager::isNextExecuteSatisfied() {
    vector<string> dependencies = execute_queue.front().dependencies;
    int size = dependencies.size();

    for (int i = 0; i < size; i++) {
        string dependent = dependencies[i];
        Instruction instruction;
        
        int execute_size = execute_vector.size();
        for (int j = 0; j < execute_size; j++) {
            instruction = execute_vector[j];
            if (!dependent.compare(instruction.program_counter)) {
                return false;
            }
        }

        int memory_size = memory_queue.size();
        for (int j = 0; j < memory_size; j++) {
            instruction = memory_queue[j];
            if (!dependent.compare(instruction.program_counter)) {
                if (instruction.type == InstructionType::LOAD ||instruction.type == InstructionType::STORE ) {
                    return false;
                }
            }
        }
    }

    return true;
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

void InstructionManager::insertMemory(Instruction instruction) {
    memory_vector.push_back(instruction);
}

Instruction InstructionManager::removeMemory() {
    Instruction instruction = memory_vector.front();
    memory_vector.pop_front();
    return instruction;
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

void InstructionManager::insertWriteBack(Instruction instruction) {
    write_back_vector.push_back(instruction);
}

Instruction InstructionManager::removeWriteBack() {
    Instruction instruction = write_back_vector.front();
    write_back_vector.pop_front();
    return instruction;
} 
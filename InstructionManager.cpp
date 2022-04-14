#include "InstructionManager.h"

InstructionManager::InstructionManager() {
    branch_halt = false;
    integer_in_execute = false;
    floating_in_execute = false;
    branch_in_execute = false;
    load_in_memory = false;
    store_in_memory = false;
}

// Fetch
void InstructionManager::insertFetch(Instruction instruction) {
    fetch_vector.push_back(instruction);
}

Instruction InstructionManager::removeFetch() {
    Instruction instruction = fetch_vector.front();
    fetch_vector.pop_back();
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
    decode_vector.pop_back();
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
    execute_vector.pop_back();
    return instruction;
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
    memory_vector.pop_back();
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
    write_back_vector.pop_back();
    return instruction;
} 
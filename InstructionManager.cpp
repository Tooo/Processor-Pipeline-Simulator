#include "InstructionManager.h"

InstructionManager::InstructionManager() {
    branch_halt = false;
    integer_in_execute = false;
    floating_in_execute = false;
    branch_in_execute = false;
    load_in_memory = false;
    store_in_memory = false;
}
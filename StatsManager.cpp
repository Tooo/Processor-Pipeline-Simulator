#include <iostream>
using namespace std;

#include "StatsManager.h"

StatsManager::StatsManager() {
    retired_integer = 0;
    retired_floating = 0;
    retired_branch = 0;
    retired_load = 0;
    retired_store = 0;
}

void StatsManager::retireInstruction(Instruction instruction) {
    switch(instruction.type) {
        case InstructionType::INTEGER:
            retired_integer++;
            break;
        case InstructionType::FLOATING_POINT:
            retired_floating++;
            break;
        case InstructionType::BRANCH:
            retired_branch++;
            break;
        case InstructionType::LOAD:
            retired_load++;
            break;
        case InstructionType::STORE:
            retired_store++;
            break;
        default:
            break;

    }
}

void StatsManager::printReport(int current_cycle) {
    cout << "Total Execution Time: " << current_cycle << endl;

    cout << "Histogram of retired instructions" << endl;


}
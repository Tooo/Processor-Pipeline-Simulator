#include <iostream>
using namespace std;

#include "StatsManager.h"

StatsManager::StatsManager() {
    retired_integer = 0;
    retired_floating = 0;
    retired_branch = 0;
    retired_load = 0;
    retired_store = 0;
    total_retired = 0;
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
    total_retired++;
}

void StatsManager::printReport(int current_cycle) {
    cout << "Total Execution Time: " << current_cycle << endl;

    cout << "Histogram of retired instructions" << endl;

    cout << "Integer Instructions: " << retired_integer / total_retired << "%" << endl;
    cout << "Floating Point Instructions: " << retired_floating / total_retired << "%" << endl;
    cout << "Branch Instructions: " << retired_branch / total_retired << "%" << endl;
    cout << "Load Instructions: " << retired_load / total_retired << "%" << endl;
    cout << "Store Instructions: " << retired_store / total_retired << "%" << endl;

}
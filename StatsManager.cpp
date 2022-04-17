#include <iostream>
#include <math.h>
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

    int integer_percentage = round(100 * float(retired_integer)/total_retired);
    cout << "Integer Instructions: " << integer_percentage << "%" << endl;

    int floating_percentage = round(100 * float(retired_floating)/total_retired);
    cout << "Floating Point Instructions: " << floating_percentage << "%" << endl;

    int branch_percentage = round(100 * float(retired_branch)/total_retired);
    cout << "Branch Instructions: " << branch_percentage << "%" << endl;

    int load_percentage = round(100 * float(retired_load)/total_retired);
    cout << "Load Instructions: " << load_percentage << "%" << endl;

    int store_percentage = round(100 * float(retired_store)/total_retired);
    cout << "Store Instructions: " << store_percentage << "%" << endl;

}
#include "Instruction.h"

#ifndef STATSMANAGER_H_
#define STATSMANAGER_H_
class StatsManager {
    private:
        int retired_integer;
        int retired_floating;
        int retired_branch;
        int retired_load;
        int retired_store;

    public:
        StatsManager();

        void retireInstruction(Instruction instruction);
        void printReport(int current_cycle);

};
#endif
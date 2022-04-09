#include <iostream> 
using namespace std;

int main (int argc, char* argv[]) {
    // ./proj2 trace_file_name start_inst inst_count W

    if (argc < 5) {
        cout << "Insufficient number of arguments provided!" << endl;
        return 0;
    }

    string trace_file_name = argv[1];
    int start_inst = atoi(argv[2]);
    int inst_count = atoi(argv[3]);
    int width = atoi(argv[4]);
}
#include "compute_biological_info.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

double ComputeResilience(std::string fragmentation_path) {
    double resilience = 0.0;
    ifstream fragmentation(fragmentation_path.c_str());
    string line;

    while (getline(fragmentation, line)) {
        cout << line << endl;
    }

    return resilience;
}

#include <iostream>
#include "compute_biological_info.h"

using namespace std;

int main() {
    string fragmentation_path = "../data/input/ppi_graph_statistics/fragmentation/394random";
    ComputeResilience(fragmentation_path);
    return 0;
}


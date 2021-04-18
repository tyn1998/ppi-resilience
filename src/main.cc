#include <iostream>

#include "compute_biological_info.h"
#include "string"

using namespace std;

int main() {
    string strategy = "random";
    string list[5] = {"394", "882", "883", "1140", "1148"};

    cout << "stratege: " << strategy << endl;

    for (int i = 0; i < 5; i++) {
        string fragmentation_path =
            "./data/input/ppi_graph_statistics/fragmentation/" + list[i] +
            strategy;
        double resilience = ComputeResilience(fragmentation_path);

        cout << list[i] << ": " << resilience << endl;
    }

    return 0;
}

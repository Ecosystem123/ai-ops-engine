//bridge.cpp
#include <iostream>
#include <fstream>
#include <string>
#include "global.hpp"
using namespace std;
void addFile(bool kubernetes)
{
    int counter1 = 0;
    int counter2 = 0;
    ifstream input("modules/metrics_collector/variable.txt");
    if (input.is_open()) {
        input >> counter1;
        input >> counter2;
        input.close();
    }
    if (kubernetes) {
        counter1++;
    }
    else {
        counter2++;
    }
    // Write both updated values
    ofstream input1("modules/metrics_collector/variable.txt");
    if (!input1.is_open()) {
        cout << "Failed to open variable.txt\n";
        return;
    }
    input1 << counter1 << "\n";
    input1 << counter2 << "\n";
    input1.close();
}

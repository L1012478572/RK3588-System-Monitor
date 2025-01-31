#include <iostream>
#include <memory>

#include "Memory.h"

using namespace std;

int main() {
    Memory memory;
    memory.updateMemoryInfo();
    cout << "Total memory: " << memory.getTotalMemory() << " kB" << endl;
    cout << "Used memory: " << memory.getUsedMemory() << " kB" << endl;
    cout << "Free memory: " << memory.getFreeMemory() << " kB" << endl;
    cout << "Cached memory: " << memory.getCachedMemory() << " kB" << endl;
    cout << "Buffers memory: " << memory.getBuffersMemory() << " kB" << endl;
    cout << "Total swap: " << memory.getTotalSwap() << " kB" << endl;
    cout << "Used swap: " << memory.getUsedSwap() << " kB" << endl;
    cout << "Free swap: " << memory.getFreeSwap() << " kB" << endl;

    cout << "--------------------------------" << endl;

    cout << "Memory usage: " << memory.getMemoryUsagePercentage() << "%" << endl;
    cout << "Swap usage: " << memory.getSwapUsagePercentage() << "%" << endl;
    cout << "--------------------------------" << endl;

    return 0;
}
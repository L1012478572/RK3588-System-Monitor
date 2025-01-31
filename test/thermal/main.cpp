#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "RK3588Thermal.h"

using namespace std;    

int main() {
    ThermalConfig config;
    config.MAX_SENSORS = 7;
    config.TEMP_SCALE = 1000;
    config.MIN_TEMP = 0;
    config.MAX_TEMP = 100;

    RK3588Thermal thermal(config);
    vector<float> temperatures = thermal.getAllTemperatures();
    for (float temp : temperatures) {
        cout << "Temperature: " << temp << "°C" << endl;
    }   
    return 0;
}
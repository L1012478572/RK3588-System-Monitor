#include <iostream>
#include "CPUUsage.h"
#include <unistd.h>
#include <sys/sysinfo.h>
#include <time.h>

int main() {
    CPUUsage cpu;
    double usage = cpu.GetUsage();
    std::cout << "CPU使用率: " << usage << "%" << std::endl;

    // 获取CPU核心数
    int core_num = cpu.GetCoreNum();
    std::cout << "CPU核心数: " << core_num << std::endl;

    // 延时1s
    sleep(1);

    // 获取CPU使用率
    usage = static_cast<int>(cpu.GetUsage());
    std::cout << "CPU使用率: " << usage << "%" << std::endl;

    return 0;
}
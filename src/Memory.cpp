#include "Memory.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

/**
 * 构造函数
 */
Memory::Memory() : 
    totalMemory(0), usedMemory(0), freeMemory(0), 
    cachedMemory(0), buffersMemory(0),
    totalSwap(0), usedSwap(0), freeSwap(0) {
    updateMemoryInfo();
}

/**
 * 析构函数
 */
Memory::~Memory() {
}

/**
 * 更新内存信息
 * @note 读取/proc/meminfo
 */
void Memory::updateMemoryInfo() {
    std::ifstream meminfo("/proc/meminfo");
    std::string line;
    
    if (!meminfo.is_open()) {
        std::cerr << "无法打开 /proc/meminfo" << std::endl;
        return;
    }

    // 用于临时存储读取的值
    unsigned long memTotal = 0, memFree = 0, cached = 0;
    unsigned long buffers = 0, swapTotal = 0, swapFree = 0;

    while (std::getline(meminfo, line)) {
        if (line.compare(0, 9, "MemTotal:") == 0)
            sscanf(line.c_str(), "MemTotal: %lu kB", &memTotal);
        else if (line.compare(0, 8, "MemFree:") == 0)
            sscanf(line.c_str(), "MemFree: %lu kB", &memFree);
        else if (line.compare(0, 8, "Cached:") == 0 && line.compare(0, 15, "SwapCached:") != 0)
            sscanf(line.c_str(), "Cached: %lu kB", &cached);
        else if (line.compare(0, 8, "Buffers:") == 0)
            sscanf(line.c_str(), "Buffers: %lu kB", &buffers);
        else if (line.compare(0, 9, "SwapTotal:") == 0)
            sscanf(line.c_str(), "SwapTotal: %lu kB", &swapTotal);
        else if (line.compare(0, 8, "SwapFree:") == 0)
            sscanf(line.c_str(), "SwapFree: %lu kB", &swapFree);
    }

    meminfo.close();

    // 更新类成员变量
    totalMemory = memTotal;
    freeMemory = memFree;
    cachedMemory = cached;
    buffersMemory = buffers;
    // 计算实际使用的内存（总内存 - 空闲 - 缓存 - 缓冲）
    usedMemory = totalMemory - freeMemory - cachedMemory - buffersMemory;

    // 更新交换空间信息
    totalSwap = swapTotal;
    freeSwap = swapFree;
    usedSwap = swapTotal - swapFree;
}

/**
 * 获取内存使用率（百分比）
 * @return 内存使用率
 */
double Memory::getMemoryUsagePercentage() const {
    if (totalMemory == 0) return 0.0;
    return (static_cast<double>(usedMemory) / totalMemory) * 100.0;
}

/**
 * 获取交换空间使用率（百分比）
 * @return 交换空间使用率
 */
double Memory::getSwapUsagePercentage() const {
    if (totalSwap == 0) return 0.0;
    return (static_cast<double>(usedSwap) / totalSwap) * 100.0;
}

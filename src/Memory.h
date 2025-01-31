#ifndef MEMORY_H
#define MEMORY_H

class Memory {
private:
    // 内存相关数据
    unsigned long totalMemory;     // 总物理内存
    unsigned long usedMemory;      // 已使用内存
    unsigned long freeMemory;      // 空闲内存
    unsigned long cachedMemory;    // 缓存内存
    unsigned long buffersMemory;   // 缓冲内存
    
    // 交换空间相关数据
    unsigned long totalSwap;       // 总交换空间
    unsigned long usedSwap;        // 已使用交换空间
    unsigned long freeSwap;        // 空闲交换空间

public:
    Memory();  // 构造函数
    ~Memory(); // 析构函数

    // 更新内存信息
    void updateMemoryInfo();

    // 获取内存信息的方法
    unsigned long getTotalMemory() const { return totalMemory; }
    unsigned long getUsedMemory() const { return usedMemory; }
    unsigned long getFreeMemory() const { return freeMemory; }
    unsigned long getCachedMemory() const { return cachedMemory; }
    unsigned long getBuffersMemory() const { return buffersMemory; }

    // 获取交换空间信息的方法
    unsigned long getTotalSwap() const { return totalSwap; }
    unsigned long getUsedSwap() const { return usedSwap; }
    unsigned long getFreeSwap() const { return freeSwap; }

    // 获取内存使用率（百分比）
    double getMemoryUsagePercentage() const;
    // 获取交换空间使用率（百分比）
    double getSwapUsagePercentage() const;
};

#endif // MEMORY_H

#ifndef CPUUSAGE_H
#define CPUUSAGE_H

#ifdef _WIN32
#include <windows.h>
#include <pdh.h>
#endif

class CPUUsage 
{
public:
    CPUUsage();
    ~CPUUsage();

    // 获取CPU使用率（返回百分比，范围0-100）
    double GetUsage();
    // 获取CPU核心数
    int GetCoreNum();

private:
#ifdef _WIN32
    // Windows系统相关变量
    ULARGE_INTEGER m_lastCPU;        // 上次CPU时间
    ULARGE_INTEGER m_lastSysCPU;     // 上次系统CPU时间
    ULARGE_INTEGER m_lastUserCPU;    // 上次用户CPU时间
    int m_numProcessors;             // CPU核心数
    HANDLE m_self;                   // 进程句柄
#else
    // Linux系统相关变量
    unsigned long long m_lastTotalUser;    // 上次用户态时间
    unsigned long long m_lastTotalNice;    // 上次nice值时间
    unsigned long long m_lastTotalSystem;  // 上次系统态时间
    unsigned long long m_lastTotalIdle;    // 上次空闲时间
#endif

    // 初始化CPU信息
    void Initialize();
};

#endif // CPUUSAGE_H 
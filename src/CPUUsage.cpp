#include "CPUUsage.h"

#ifdef _WIN32
#include <pdh.h>
#pragma comment(lib, "pdh.lib")
#else
#include <unistd.h>
#include <fstream>
#include <string>
#include <sstream>
#endif

CPUUsage::CPUUsage()
{
    Initialize();
}

CPUUsage::~CPUUsage()
{
#ifdef _WIN32
    if (m_self) {
        CloseHandle(m_self);
    }
#endif
}

void CPUUsage::Initialize()
{
#ifdef _WIN32
    // Windows系统初始化
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    m_numProcessors = sysInfo.dwNumberOfProcessors;

    // 获取进程句柄
    m_self = GetCurrentProcess();

    // 初始化CPU时间
    GetSystemTimeAsFileTime((LPFILETIME)&m_lastCPU);
    GetProcessTimes(m_self, (LPFILETIME)&m_lastCPU, 
                           (LPFILETIME)&m_lastCPU, 
                           (LPFILETIME)&m_lastSysCPU, 
                           (LPFILETIME)&m_lastUserCPU);
#else
    // Linux系统初始化
    m_lastTotalUser = 0;
    m_lastTotalNice = 0;
    m_lastTotalSystem = 0;
    m_lastTotalIdle = 0;
#endif
}

double CPUUsage::GetUsage()
{
#ifdef _WIN32
    FILETIME nowTime, sysTime, userTime;
    ULARGE_INTEGER now, sys, user;

    GetSystemTimeAsFileTime(&nowTime);
    GetProcessTimes(m_self, &nowTime, &nowTime, &sysTime, &userTime);

    memcpy(&now, &nowTime, sizeof(FILETIME));
    memcpy(&sys, &sysTime, sizeof(FILETIME));
    memcpy(&user, &userTime, sizeof(FILETIME));

    // 计算时间差
    double percent = static_cast<double>((sys.QuadPart - m_lastSysCPU.QuadPart) +
                                       (user.QuadPart - m_lastUserCPU.QuadPart));
    percent /= (now.QuadPart - m_lastCPU.QuadPart);
    percent /= m_numProcessors;

    // 更新上次的值
    m_lastCPU = now;
    m_lastUserCPU = user;
    m_lastSysCPU = sys;

    return percent * 100.0;

#else
    std::ifstream statFile("/proc/stat");   // 读取/proc/stat文件
    std::string line;
    if (std::getline(statFile, line)) {
        std::istringstream iss(line);
        std::string cpu;
        unsigned long long totalUser, totalNice, totalSystem, totalIdle,
                          totalIowait, totalIrq, totalSoftirq;

        iss >> cpu >> totalUser >> totalNice >> totalSystem >> totalIdle
            >> totalIowait >> totalIrq >> totalSoftirq;

        // 计算总的时间差
        unsigned long long totalTime = (totalUser - m_lastTotalUser) +
                                     (totalNice - m_lastTotalNice) +
                                     (totalSystem - m_lastTotalSystem);
        
        unsigned long long idleTime = (totalIdle - m_lastTotalIdle);
        unsigned long long totalTimeDiff = totalTime + idleTime;

        // 更新上次的值
        m_lastTotalUser = totalUser;
        m_lastTotalNice = totalNice;
        m_lastTotalSystem = totalSystem;
        m_lastTotalIdle = totalIdle;

        // 计算CPU使用率
        if (totalTimeDiff == 0) return 0.0;
        return (totalTime * 100.0) / totalTimeDiff;
    }
    return 0.0;
#endif
}

int CPUUsage::GetCoreNum() {
#ifdef _WIN32
    return m_numProcessors;
#else
    return sysconf(_SC_NPROCESSORS_CONF);
#endif
}
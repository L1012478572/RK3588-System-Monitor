#ifndef RK3588_THERMAL_H
#define RK3588_THERMAL_H

#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>

// 温度传感器类型 枚举
enum ThermalSensorType {
    SOC_THERMAL = 0,         // SoC整体温度传感器
    BIGCORE0_THERMAL = 1,    // 大核心0温度传感器
    BIGCORE1_THERMAL = 2,    // 大核心1温度传感器
    LITTLECORE_THERMAL = 3,  // 小核心温度传感器
    CENTER_THERMAL = 4,      // SoC中心区域温度传感器
    GPU_THERMAL = 5,         // GPU温度传感器
    NPU_THERMAL = 6,          // NPU温度传感器
    UNKNOWN_THERMAL = 7      // 未知传感器类型
};

// RK3588 温度传感器配置信息
struct ThermalConfig {
    static int MAX_SENSORS;       // 最大传感器数量
    static int TEMP_SCALE;        // 温度缩放因子
    static float MIN_TEMP;        // 最低温度限制
    static float MAX_TEMP;        // 最高温度限制
};

// 温度传感器数据结构
struct ThermalSensor {
    ThermalSensorType type; // 传感器类型
    float temperature;      // 温度值
    bool isAlert;           // 温度是否告警
};

class RK3588Thermal {
public:
    // 构造函数
    RK3588Thermal(struct ThermalConfig config);

    // 析构函数
    ~RK3588Thermal();

    // 获取指定传感器的温度
    float getTemperature(int sensorIndex) const;
    
    // 获取所有传感器的温度
    std::vector<float> getAllTemperatures() const;

private:
    struct ThermalConfig config; // 温度传感器配置信息
    std::vector<ThermalSensor> sensors; // 温度传感器列表
    
    // 温度传感器路径
    static constexpr const char* THERMAL_PATH = "/sys/class/thermal/";
    
    // 从文件读取温度值
    float readTemperatureFromFile(const std::string& path) const;
    
    // 检查传感器索引是否有效
    void validateSensorIndex(int sensorIndex) const;

    // 获取传感器的类型
    ThermalSensorType getSensorType(int sensorIndex) const;
};

#endif // RK3588_THERMAL_H

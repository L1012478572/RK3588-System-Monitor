#include "RK3588Thermal.h"

/**
 * 构造函数
 * @param config 温度传感器配置信息
 */
RK3588Thermal::RK3588Thermal(struct ThermalConfig config) : config(config) {
    this->sensors.reserve(config.MAX_SENSORS);    // 预留传感器数量

    // 初始化传感器
    for (int i = 0; i < config.MAX_SENSORS; i++) {
        ThermalSensor sensor;
        sensor.type = getSensorType(i);
        sensor.temperature = 0.0f;
        sensor.isAlert = false;
        this->sensors.push_back(sensor);
    }
}

/**
 * 析构函数
 */
RK3588Thermal::~RK3588Thermal() {
    this->sensors.clear();
}

/**
 * 获取指定传感器的温度
 * @param sensorIndex 传感器索引
 * @return 温度值
 */
float RK3588Thermal::getTemperature(int sensorIndex) const {
    validateSensorIndex(sensorIndex);
    return readTemperatureFromFile(THERMAL_PATH + std::to_string(sensorIndex) + "/temp");
}

/**
 * 获取所有传感器的温度
 * @return 温度值列表
 */
std::vector<float> RK3588Thermal::getAllTemperatures() const {
    std::vector<float> temperatures;
    temperatures.reserve(config.MAX_SENSORS);
    
    for (int i = 0; i < config.MAX_SENSORS; i++) {
        temperatures.push_back(getTemperature(i));
    }
    
    return temperatures;
}

/**
 * 从文件读取温度值
 * @param path 传感器文件路径
 * @return 温度值
 * @note 读取/sys/class/thermal/thermal_zoneX/temp
 */
float RK3588Thermal::readTemperatureFromFile(const std::string& path) const {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("无法打开温度传感器文件: " + path);
    }
    
    int rawTemp;
    file >> rawTemp;
    
    float temp = static_cast<float>(rawTemp) / ThermalConfig::TEMP_SCALE;
    
    if (temp < ThermalConfig::MIN_TEMP || temp > ThermalConfig::MAX_TEMP) {
        throw std::runtime_error("温度值超出有效范围");
    }
    
    return temp;
}

/**
 * 检查传感器索引是否有效
 * @param sensorIndex 传感器索引
 */
void RK3588Thermal::validateSensorIndex(int sensorIndex) const {
    if (sensorIndex < 0 || sensorIndex >= config.MAX_SENSORS) {
        throw std::out_of_range("传感器索引超出范围");
    }
}

/**
 * 获取传感器的类型
 * @param sensorIndex 传感器索引
 * @return 传感器类型
 * @note 读取/sys/class/thermal/thermal_zoneX/type
 */
ThermalSensorType RK3588Thermal::getSensorType(int sensorIndex) const {
    std::string path = THERMAL_PATH + std::to_string(sensorIndex) + "/type";
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("无法打开传感器类型文件: " + path);
    }
    std::string type;
    file >> type;
    file.close();
    if (type == "soc-thermal") {
        return SOC_THERMAL;
    }
    else if (type == "bigcore0-thermal") {
        return BIGCORE0_THERMAL;
    }
    else if (type == "bigcore1-thermal") {
        return BIGCORE1_THERMAL;
    }
    else if (type == "littlecore-thermal") {    
        return LITTLECORE_THERMAL;
    }
    else if (type == "center-thermal") {
        return CENTER_THERMAL;
    }
    else if (type == "gpu-thermal") {
        return GPU_THERMAL;
    }
    else if (type == "npu-thermal") {
        return NPU_THERMAL;
    }   
    else {
        throw std::runtime_error("未知传感器类型: " + type);
        return UNKNOWN_THERMAL;
    }
}
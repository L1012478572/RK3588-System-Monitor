#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGridLayout>
#include <QDesktopWidget>
#include <QApplication>
#include <QDebug>

/**
 * @brief 构造函数
 * @param parent 父窗口
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 设置窗口标题
    this->setWindowTitle("RK3588-System-Monitor");
    // 设置窗口大小
    this->setFixedSize(200, 400);
    // 设置窗口无边框
    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
    // 设置窗口位置 右上角
    this->move(QApplication::desktop()->width() - this->width(), 0);

    // 设置背景颜色为灰褐色
    this->setStyleSheet("background-color: #8B4513;");

    // 设置窗口固定在最顶层 其他窗口无法掩盖
    this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);

    // 初始化标签
    init_label();

    // 初始化温度传感器
    ThermalConfig thermal_config = {
        .MAX_SENSORS = 7,
        .TEMP_SCALE = 1000,
        .MIN_TEMP = -10.0f,
        .MAX_TEMP = 60.0f
    };
    thermal = new RK3588Thermal(thermal_config);

    // 初始化内存传感器
    memory = new Memory();

    // 初始化CPU使用率
    cpu_usage = new CPUUsage();
    double usage = cpu_usage->GetUsage();

    // 初始化定时器
    timer = new QTimer(this);
    timer->start(1000);
    connect(timer, &QTimer::timeout, this, &MainWindow::timer_slot);
}

/**
 * @brief 析构函数
 */
MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
    delete thermal; 
    delete memory;
    delete average_label;
    delete cpuBig0_label;
    delete cpuBig1_label;
    delete cpuSmall_label;
    delete gpu_label;
    delete npu_label;
    delete memory_label;
    delete cpu_usage_label;
    delete cpu_usage;
}

/**
 * @brief 初始化标签
 */
void MainWindow::init_label()
{
    // 获取窗口大小
    int window_width = this->width();
    int window_height = this->height();

    qDebug() << "window_width: " << window_width;
    qDebug() << "window_height: " << window_height;


    // 创建标签 平均温度
    average_label = new ThermalLabel(this);
    // 创建标签 CPU大核0
    cpuBig0_label = new ThermalLabel(this);
    // 创建标签 CPU大核1
    cpuBig1_label = new ThermalLabel(this);
    // 创建标签 CPU小核
    cpuSmall_label = new ThermalLabel(this);
    // 创建标签 GPU
    gpu_label = new ThermalLabel(this);
    // 创建标签 NPU
    npu_label = new ThermalLabel(this);
    // 创建标签 内存
    memory_label = new MemoryLabel(this);
    // 创建标签 CPU使用率
    cpu_usage_label = new CpuUsageLabel(this);

    average_label->set_label_name("AVE");
    average_label->move(10, 10);    // 设置标签位置  0，0
    average_label->set_temperature(25.0);   // 设置温度
    average_label->set_temperature_alarm(-10.0f, 60.0f);   // 设置温度报警范围      
    average_label->set_label_size((window_width / 2 - 20), (window_height / 4 - 20));   // 设置标签尺寸

    cpuBig0_label->set_label_name("cpu_big0");
    cpuBig0_label->move(window_width / 2 + 10, 10);    // 设置标签位置 0， 1
    cpuBig0_label->set_temperature(25.0);   // 设置温度
    cpuBig0_label->set_temperature_alarm(-10.0f, 60.0f);   // 设置温度报警范围      
    cpuBig0_label->set_label_size((window_width / 2 - 20), (window_height / 4 - 20));   // 设置标签尺寸

    cpuBig1_label->set_label_name("cpu_big1");
    cpuBig1_label->move(10, window_height / 4 + 10);    // 设置标签位置 1， 0
    cpuBig1_label->set_temperature(25.0);   // 设置温度
    cpuBig1_label->set_temperature_alarm(-10.0f, 60.0f);   // 设置温度报警范围      
    cpuBig1_label->set_label_size((window_width / 2 - 20), (window_height / 4 - 20));   // 设置标签尺寸

    cpuSmall_label->set_label_name("cpu_small");
    cpuSmall_label->move(window_width / 2 + 10, window_height / 4 + 10);    // 设置标签位置 1， 1
    cpuSmall_label->set_temperature(25.0);   // 设置温度
    cpuSmall_label->set_temperature_alarm(-10.0f, 60.0f);   // 设置温度报警范围      
    cpuSmall_label->set_label_size((window_width / 2 - 20), (window_height / 4 - 20));   // 设置标签尺寸

    gpu_label->set_label_name("GPU");
    gpu_label->move(10, window_height / 2 + 10);    // 设置标签位置 2， 0
    gpu_label->set_temperature(25.0);   // 设置温度
    gpu_label->set_temperature_alarm(-10.0f, 60.0f);   // 设置温度报警范围      
    gpu_label->set_label_size((window_width / 2 - 20), (window_height / 4 - 20));   // 设置标签尺寸 

    npu_label->set_label_name("NPU");
    npu_label->move(window_width / 2 + 10, window_height / 2 + 10);    // 设置标签位置 2， 1
    npu_label->set_temperature(25.0);   // 设置温度
    npu_label->set_temperature_alarm(-10.0f, 60.0f);   // 设置温度报警范围      
    npu_label->set_label_size((window_width / 2 - 20), (window_height / 4 - 20));   // 设置标签尺寸  

    memory_label->set_label_name("Memory");
    memory_label->move(10, (window_height / 4 * 3 )+ 10);    // 设置标签位置 3， 0
    memory_label->set_memory_usage(25.0);   // 设置内存使用率
    memory_label->set_memory_alarm(80.0);   // 设置内存使用率报警范围      
    memory_label->set_label_size((window_width / 2 - 20), (window_height / 4 - 20));   // 设置标签尺寸  

    cpu_usage_label->set_label_name("CpuUsage");
    cpu_usage_label->move(window_width / 2 + 10, (window_height / 4 * 3 )+ 10);    // 设置标签位置 3， 1
    cpu_usage_label->set_cpu_usage(25.0);   // 设置CPU使用率
    cpu_usage_label->set_cpu_alarm(80.0);   // 设置CPU使用率报警阈值      
    cpu_usage_label->set_label_size((window_width / 2 - 20), (window_height / 4 - 20));   // 设置标签尺寸  
 
}

/**
 * @brief 定时器槽函数
 */
void MainWindow::timer_slot()
{
    timer->stop();
    try{
        // 获取所有传感器数据
        std::vector<ThermalSensor> sensors = thermal->getAllSensors();
        // 更新标签
        for (int i = 0; i < sensors.size(); i++) {
            if (sensors[i].type == ThermalSensorType::SOC_THERMAL) {
                average_label->set_temperature(sensors[i].temperature);
            }
            else if (sensors[i].type == ThermalSensorType::BIGCORE0_THERMAL) {
                cpuBig0_label->set_temperature(sensors[i].temperature);
            }
            else if (sensors[i].type == ThermalSensorType::BIGCORE1_THERMAL) {
                cpuBig1_label->set_temperature(sensors[i].temperature);
            }
            else if (sensors[i].type == ThermalSensorType::LITTLECORE_THERMAL) {
                cpuSmall_label->set_temperature(sensors[i].temperature);
            }
            else if (sensors[i].type == ThermalSensorType::GPU_THERMAL) {
                gpu_label->set_temperature(sensors[i].temperature);
            }
            else if (sensors[i].type == ThermalSensorType::NPU_THERMAL) {
                npu_label->set_temperature(sensors[i].temperature);
            }
        }

        // 更新内存标签
        memory->updateMemoryInfo();
        memory_label->set_memory_usage(memory->getMemoryUsagePercentage());

        // 更新CPU使用率标签
        cpu_usage_label->set_cpu_usage(static_cast<float>(cpu_usage->GetUsage()));
    }
    catch (const std::exception& e) {
        qDebug() << "获取传感器数据失败: " << e.what();
    }
    timer->start(1000);
}


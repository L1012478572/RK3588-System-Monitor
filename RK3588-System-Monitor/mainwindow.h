#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "ui_src/ThermalLabel.h"
#include "ui_src/MemoryLabel.h"
#include "ui_src/CpuUsageLabel.h"
#include "RK3588Thermal.h"
#include "Memory.h"
#include "CPUUsage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // 初始化标签
    void init_label();

private slots:
    // 定时器槽函数
    void timer_slot();

private:
    Ui::MainWindow *ui;
    // 定时器
    QTimer *timer;
    // 温度传感器
    RK3588Thermal *thermal;
    // 内存传感器
    Memory *memory;
    // CPU使用率
    CPUUsage *cpu_usage;
    // 标签
    ThermalLabel *average_label;
    ThermalLabel *cpuBig0_label;
    ThermalLabel *cpuBig1_label;
    ThermalLabel *cpuSmall_label;
    ThermalLabel *gpu_label;
    ThermalLabel *npu_label;
    MemoryLabel *memory_label;
    CpuUsageLabel *cpu_usage_label;
};
#endif // MAINWINDOW_H

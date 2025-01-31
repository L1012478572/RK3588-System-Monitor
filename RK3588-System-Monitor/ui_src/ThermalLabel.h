#ifndef THERMAL_LABEL_H
#define THERMAL_LABEL_H

#include <QLabel>
#include <QColor>
#include <QMouseEvent>
#include <QPainter>
#include <QPen>
#include <QFont>
#include <QFontMetrics>
#include <QTimer>

class ThermalLabel : public QLabel
{
    Q_OBJECT
public:
    // 构造函数
    ThermalLabel(QWidget *parent = nullptr);
    // 析构函数
    ~ThermalLabel();

    // 设置label尺寸
    void set_label_size(int width, int height);
    // 设置温度
    void set_temperature(float temperature);
    // 设置温度报警范围
    void set_temperature_alarm(float temperature_alarm_min, float temperature_alarm_max);
    // 设置标签名称
    void set_label_name(QString label_name);

// signals:
//     void clicked();              // 点击信号
//     void doubleClicked();        // 双击信号
//     void rightClicked();         // 右键点击信号
//     void released();            // 释放信号
    
protected:
    // 绘制事件
    void paintEvent(QPaintEvent *event);

private:
    // 初始化label
    void init_label();
private:
    // 温度
    float temperature;
    // 温度报警范围
    float temperature_alarm_min;
    float temperature_alarm_max;
    // 标签尺寸
    int label_width = 50;
    int label_height = 50;
    // 标签名称
    QString label_name = "label";
};

#endif // THERMAL_LABEL_H

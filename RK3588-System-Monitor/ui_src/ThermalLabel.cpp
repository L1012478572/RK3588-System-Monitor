#include "ThermalLabel.h"
#include <QDebug>

/**
 * @brief 构造函数
 * @param parent 父窗口
 */
ThermalLabel::ThermalLabel(QWidget *parent) : QLabel(parent)
{
    // 初始化温度
    temperature = 0;
}

/**
 * @brief 析构函数
 */
ThermalLabel::~ThermalLabel()
{
}

/**
 * @brief 设置label尺寸
 * @param width 宽度
 * @param height 高度
 */
void ThermalLabel::set_label_size(int width, int height)
{
    label_width = width;
    label_height = height;
    this->setFixedSize(width, height);
    qDebug() << "label_width: " << label_width;
    qDebug() << "label_height: " << label_height;
    init_label();
}

/**
 * @brief 设置标签名称
 * @param label_name 标签名称
 */
void ThermalLabel::set_label_name(QString label_name)
{
    this->label_name = label_name;
}

/**
 * @brief 初始化label
 */
void ThermalLabel::init_label()
{
    this->setFixedSize(label_width, label_height);
    // 设置对齐方式
    this->setAlignment(Qt::AlignCenter);    
    // 重新绘制
    update();
}

/**
 * @brief 设置温度
 * @param temperature 温度
 */
void ThermalLabel::set_temperature(float temperature)
{
    this->temperature = temperature;
    update();
}

/**
 * @brief 设置温度报警范围
 * @param temperature_alarm_min 最小温度
 * @param temperature_alarm_max 最大温度
 */
void ThermalLabel::set_temperature_alarm(float temperature_alarm_min, float temperature_alarm_max)
{
    this->temperature_alarm_min = temperature_alarm_min;
    this->temperature_alarm_max = temperature_alarm_max;
}

/**
 * @brief 绘制事件
 * @param event 事件
 */
void ThermalLabel::paintEvent(QPaintEvent *event)
{
    // 获取label的位置  
    // QPoint pos = this->pos();
    QPainter painter(this);
    // 设置字体
    QFont font("Arial", 10);
    painter.setFont(font);
    // 在左上角绘制标签名称
    // painter.drawText(pos.x() + 10, pos.y() + 10, label_name);
    painter.drawText(10, 10, label_name);

    // 设置字体为20
    QFont font2("Arial", 20);
    painter.setFont(font2);
    // 在右下角绘制温度 温度值大小占label的3/5
    if (temperature >= temperature_alarm_min && temperature <= temperature_alarm_max)
    {
        painter.setPen(Qt::green);
    }
    else
    {
        painter.setPen(Qt::red);
    }
    painter.drawText(label_width * 2 / 5-10, label_height * 3 / 5, QString("%1").arg(temperature, 0, 'f', 1)); // 保留一位小数
}

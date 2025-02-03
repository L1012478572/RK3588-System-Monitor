#include "CpuUsageLabel.h"
#include <QPainter>
#include <QFont>
#include <QColor>

/**
 * 构造函数
 * @param parent 父窗口
 */
CpuUsageLabel::CpuUsageLabel(QWidget *parent) : QLabel(parent)
{
    // 初始化变量
    cpu_usage = 0.0f;
    cpu_alarm_max = 80.0f;
    label_name = "CpuUsage";
    label_width = 100;
    label_height = 50;

    init_label();
}

/**
 * 析构函数
 */
CpuUsageLabel::~CpuUsageLabel()
{
    
}

/**
 * 初始化label
 */
void CpuUsageLabel::init_label()
{
    // 设置固定大小
    setFixedSize(label_width, label_height);
    // 设置对齐方式
    setAlignment(Qt::AlignCenter);
}

/**
 * 设置label尺寸
 * @param width 宽度
 * @param height 高度
 */
void CpuUsageLabel::set_label_size(int width, int height)
{
    label_width = width;
    label_height = height;
    setFixedSize(label_width, label_height);
}

/**
 * 设置CPU使用率
 * @param usage CPU使用率
 */
void CpuUsageLabel::set_cpu_usage(float usage)
{
    this->cpu_usage = usage;
    update();
}

// 设置CPU使用率报警范围
void CpuUsageLabel::set_cpu_alarm(float cpu_alarm_max)
{
    this->cpu_alarm_max = cpu_alarm_max;
}

// 设置标签名称
void CpuUsageLabel::set_label_name(QString label_name)
{
    this->label_name = label_name;
}

/**
 * 绘制事件
 * @param event 事件
 */
void CpuUsageLabel::paintEvent(QPaintEvent *event)
{
    // 调用父类的绘制事件
    QLabel::paintEvent(event);

    // 创建QPainter对象
    QPainter painter(this);

    // 设置背景颜色为黑色
    painter.fillRect(rect(), Qt::black);

    // 设置字体颜色为白色
    painter.setPen(Qt::white);

    // 设置字体
    QFont font = painter.font();
    font.setPointSize(12);
    painter.setFont(font);

    // 绘制标签名称
    painter.drawText(rect(), Qt::AlignTop | Qt::AlignHCenter, label_name);

    // 计算CPU使用率的颜色（绿色到红色的渐变）
    int red = static_cast<int>((cpu_usage / 100.0f) * 255);
    int green = 255 - red;
    QColor usageColor(red, green, 0);

    // 设置CPU使用率的颜色
    painter.setPen(usageColor);

    // 绘制CPU使用率百分比
    QString usageText = QString::number(cpu_usage, 'f', 2) + "%";
    painter.drawText(rect(), Qt::AlignCenter, usageText);
}
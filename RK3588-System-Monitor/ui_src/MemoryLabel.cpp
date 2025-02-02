#include "MemoryLabel.h"

// 构造函数
MemoryLabel::MemoryLabel(QWidget *parent) : QLabel(parent)
{
    // 初始化变量
    memory_usage = 0;
    memory_alarm_max = 80;
    label_name = "Memory";
    label_width = 100;
    label_height = 50;

    init_label();
}

// 析构函数
MemoryLabel::~MemoryLabel()
{
}

// 初始化label
void MemoryLabel::init_label()
{
    // 设置固定大小
    setFixedSize(label_width, label_height);
    // 设置对齐方式
    setAlignment(Qt::AlignCenter);
}

// 设置label尺寸
void MemoryLabel::set_label_size(int width, int height)
{
    label_width = width;
    label_height = height;
    setFixedSize(label_width, label_height);
}

// 设置内存使用率
void MemoryLabel::set_memory_usage(float usage)
{
    memory_usage = usage;
    update();
}

// 设置内存使用率报警范围
void MemoryLabel::set_memory_alarm(float memory_alarm_max)
{
    this->memory_alarm_max = memory_alarm_max;
}

// 设置标签名称
void MemoryLabel::set_label_name(QString label_name)
{
    this->label_name = label_name;
    update();
}

// 绘制事件
void MemoryLabel::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制背景
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(40, 40, 40));
    painter.drawRect(rect());

    // 绘制内存使用率进度条
    int margin = 5;
    int bar_height = 10;
    QRect bar_rect(margin, height() - margin - bar_height, 
                   width() - 2 * margin, bar_height);
    
    // 背景
    painter.setBrush(QColor(80, 80, 80));
    painter.drawRect(bar_rect);
    
    // 进度
    if (memory_usage >= memory_alarm_max) {
        painter.setBrush(QColor(255, 0, 0));
    } else {
        painter.setBrush(QColor(0, 255, 0));
    }
    int bar_width = (width() - 2 * margin) * memory_usage / 100;
    painter.drawRect(margin, height() - margin - bar_height, bar_width, bar_height);

    // 绘制文字
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 10));
    
    // 绘制标签名称
    painter.drawText(rect(), Qt::AlignTop | Qt::AlignHCenter, label_name);
    
    // 绘制使用率
    QString usage_text = QString::number(memory_usage, 'f', 1) + "%";
    painter.drawText(rect(), Qt::AlignCenter, usage_text);
}

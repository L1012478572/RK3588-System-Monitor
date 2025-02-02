#ifndef MEMORY_LABEL_H
#define MEMORY_LABEL_H

#include <QLabel>
#include <QColor>
#include <QMouseEvent>
#include <QPainter>
#include <QPen>
#include <QFont>
#include <QFontMetrics>
#include <QTimer>

class MemoryLabel : public QLabel
{
    Q_OBJECT
public:
    // 构造函数
    MemoryLabel(QWidget *parent = nullptr);
    // 析构函数
    ~MemoryLabel();

    // 设置label尺寸
    void set_label_size(int width, int height);
    // 设置内存使用率
    void set_memory_usage(float usage);
    // 设置内存使用率报警范围
    void set_memory_alarm(float memory_alarm_max);
    // 设置标签名称
    void set_label_name(QString label_name);
    
protected:
    // 绘制事件
    void paintEvent(QPaintEvent *event);

private:
    // 初始化label
    void init_label();
private:
    // 内存使用率
    float memory_usage;
    // 内存使用率报警范围
    float memory_alarm_max;
    // 标签名称
    QString label_name;
    // 标签尺寸
    int label_width;
    int label_height;
};

#endif // MEMORY_LABEL_H

#ifndef CPUUSAGELABEL_H
#define CPUUSAGELABEL_H

#include <QLabel>
#include <QWidget>
#include <QString>

class CpuUsageLabel : public QLabel
{
    Q_OBJECT

public:
    explicit CpuUsageLabel(QWidget *parent = nullptr);
    ~CpuUsageLabel();

    // 设置label尺寸
    void set_label_size(int width, int height);
    // 设置CPU使用率
    void set_cpu_usage(float usage);
    // 设置CPU使用率报警范围
    void set_cpu_alarm(float cpu_alarm_max);
    // 设置标签名称
    void set_label_name(QString label_name);

    // 初始化label
    void init_label();

protected:
    // 绘制事件
    void paintEvent(QPaintEvent *event);

private:
    float cpu_usage;
    float cpu_alarm_max;
    QString label_name;
    int label_width;
    int label_height;
};

#endif // CPUUSAGELABEL_H

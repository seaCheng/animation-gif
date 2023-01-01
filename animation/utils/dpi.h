#ifndef DPI_H
#define DPI_H

#include <QObject>

class DPI : public QObject
{
    Q_OBJECT
public:
    explicit DPI(QObject *parent = nullptr);
    //返回缩放的比率
    static double getScale();

    //************************************
    // Method:    getScaleUI -- 获取缩放的大小
    // Parameter: int ori -- 原始值大小
    //************************************
    static int getScaleUI(int ori);
    static QSize getScaleUISize(int wid, int hei);
    //监听显示设置DPI大小变化
    static void logicalDotsPerInchChanged(qreal dpi);

signals:
private:
    static bool s_bInit;
    static double s_beishu;
};

#endif // DPI_H

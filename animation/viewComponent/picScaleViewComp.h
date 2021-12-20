#pragma once
#include <QWidget>

class QHBoxLayout;
class QScrollArea;
class PicScaleViewComp :public QWidget
{
    Q_OBJECT
public:

    PicScaleViewComp(QWidget *parent = nullptr);
    void initial();
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    QHBoxLayout * m_layout = nullptr;
    QScrollArea * m_scroll = nullptr;
};

#pragma once
#include <QFrame>

class QHBoxLayout;
class QScrollArea;
class PicScaleComp;

class PicScaleViewComp :public QFrame
{
    Q_OBJECT
public:

    PicScaleViewComp(QWidget *parent = nullptr);
    void initial();
    void setConnect();
public slots:
     void refreashState();
protected:
    //void paintEvent(QPaintEvent *event) override;
private:
    QHBoxLayout * m_layout = nullptr;
    QScrollArea * m_scroll = nullptr;

    PicScaleComp * m_picScaleCli = nullptr;
};

#pragma once
#include <QFrame>

class QLabel;
class AspectRatioPixmapLabel;
class QVBoxLayout;
class PicScaleComp :public QFrame
{
    Q_OBJECT
public:

    PicScaleComp(QWidget *parent = nullptr);
    void initial();

    void setPicIndexInterval(QString index, QString interval);
    void setPic(QPixmap pic);
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    QFrame * m_frameBottom = nullptr;
    QLabel *m_labelLeft = nullptr;
    QLabel *m_labelRight = nullptr;

    AspectRatioPixmapLabel *m_lPic = nullptr;
    QVBoxLayout * m_layout = nullptr;
};

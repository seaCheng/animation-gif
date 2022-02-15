#pragma once
#include <QFrame>
#include "connectableitemcontroller.h"

class QLabel;
class AspectRatioPixmapLabel;
class QVBoxLayout;
class ConnectableItem;

class PicScaleComp :public QFrame
{
    Q_OBJECT
public:

    PicScaleComp(ConnectableItem* item, QWidget *parent = nullptr);
    void initial();

    void setPicIndexInterval(QString index, QString interval);
    void setPic(QPixmap pic);

    ConnectableItem* connectableItem();

signals:
    void s_clicked();
protected:
    virtual void paintEvent(QPaintEvent *) override;
    virtual void mouseReleaseEvent(QMouseEvent *ev) override;
private:
    QFrame * m_frameBottom = nullptr;
    QLabel *m_labelLeft = nullptr;
    QLabel *m_labelRight = nullptr;

    AspectRatioPixmapLabel *m_lPic = nullptr;
    QVBoxLayout * m_layout = nullptr;

    ConnectableItem * m_item{nullptr};
    std::unique_ptr<ConnectableItemController> m_controller;
};

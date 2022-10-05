#pragma once
#include <QFrame>
#include "pictureItemcontroller.h"

class QLabel;
class AspectRatioPixmapLabel;
class QVBoxLayout;
class PictureItem;
class QMenu;

class PicScaleComp :public QFrame
{
    Q_OBJECT
public:

    PicScaleComp(QMenu * menu,PictureItem* item, QWidget *parent = nullptr);
    void initial();

    void setPicIndexInterval(QString index, QString interval);
    void setPic(QPixmap pic);

    PictureItem * getPictureItem();

signals:
    void s_clicked(bool bShow = true);
protected:
    virtual void paintEvent(QPaintEvent *) override;
    virtual void mouseReleaseEvent(QMouseEvent *ev) override;

    void contextMenuEvent(QContextMenuEvent *ev) Q_DECL_OVERRIDE;
private:
    QFrame * m_frameBottom = nullptr;
    QLabel *m_labelLeft = nullptr;
    QLabel *m_labelRight = nullptr;

    AspectRatioPixmapLabel *m_lPic = nullptr;
    QVBoxLayout * m_layout = nullptr;

    PictureItem * m_item = nullptr;
    std::unique_ptr<PictureItemController> m_controller;

    QMenu * myContextMenu = nullptr;
};

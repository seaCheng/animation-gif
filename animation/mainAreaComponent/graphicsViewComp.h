#pragma once
#include <QGraphicsView>

class PictureItem;
class GraphicsViewComp :public QGraphicsView
{
    Q_OBJECT
public:

    GraphicsViewComp(QWidget *parent = nullptr);
    void setPicItem(PictureItem * pItem);
protected:
    void paintEvent(QPaintEvent *event) override;
private:

    QGraphicsWidget * m_GraWid = nullptr;
};

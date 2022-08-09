#include "graphicsViewComp.h"
#include "pictureItem.h"
#include <QGraphicsScene>
#include <QPushButton>
#include <QGraphicsWidget>
#include <QGraphicsLinearLayout>
#include <QTextEdit>
#include <QToolButton>

GraphicsViewComp::GraphicsViewComp(QWidget *parent)
    :QGraphicsView(parent)
{
    QGraphicsScene * scene = new QGraphicsScene();

    setScene(scene);
}

void GraphicsViewComp::paintEvent(QPaintEvent *event)
{

    QGraphicsView::paintEvent(event);
}

void GraphicsViewComp::setPicItem(PictureItem * pItem)
{
    //QGraphicsView view;
    setBackgroundBrush(pItem->pic().toImage());
    setCacheMode(QGraphicsView::CacheBackground);

}

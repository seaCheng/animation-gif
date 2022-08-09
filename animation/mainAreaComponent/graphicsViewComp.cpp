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
    mscene = new PicGraphicsScene();
    mscene->setSceneRect(0,0,450,450);
    setFixedSize(450,450);
    setScene(mscene);
}

void GraphicsViewComp::paintEvent(QPaintEvent *event)
{

    QGraphicsView::paintEvent(event);
}

void GraphicsViewComp::setPicItem(PictureItem * pItem)
{
    mscene->setPicItem(pItem);
    mscene->update();
    //setCacheMode(QGraphicsView::CacheBackground);
}


////////////////////////////////PicGraphicsScene ///////////////////////////////////
PicGraphicsScene::PicGraphicsScene()
    :QGraphicsScene()
{
    //
}

void PicGraphicsScene::drawBackground(QPainter *painter, const QRectF &rect)
{


    if(views().count()==0)
           return;

    if(mpItem == nullptr)
          return;

    // 计算视窗的大小,消除图元拖动时出现的残影
    QGraphicsView* pView=views().first();
    QRect contentRect=pView->viewport()->contentsRect();
    QRectF sceneRect =pView->mapToScene(contentRect).boundingRect();

    //绘制指定图片作为背景
    painter->drawPixmap(sceneRect,mpItem->pic(),QRect());

    QGraphicsScene::drawBackground(painter, rect);
}

#include "graphicsViewComp.h"
#include "pictureItem.h"
#include <QGraphicsScene>
#include <QPushButton>
#include <QGraphicsWidget>
#include <QGraphicsLinearLayout>
#include <QTextEdit>
#include <QToolButton>
#include <QDebug>

GraphicsViewComp::GraphicsViewComp(QWidget *parent)
    :QGraphicsView(parent)
{
    mscene = new PicGraphicsScene();
    //mscene->setSceneRect(1,1,318,318);
    //setFixedSize(320,320);
    setScene(mscene);
}

void GraphicsViewComp::paintEvent(QPaintEvent *event)
{

    QGraphicsView::paintEvent(event);

    QWidget * wid = parentWidget();
    if(wid != nullptr && pPicItem != nullptr)
    {

        int iheigth = wid->height() - 40;
        int iwidth = pPicItem->x() / pPicItem->y() * iheigth;
        setFixedSize(iwidth,iheigth);
        mscene->setSceneRect(2,2,iwidth -4,iheigth -4);

    }

}

void GraphicsViewComp::resizeEvent(QResizeEvent *event)
{

    QWidget * wid = parentWidget();
    if(wid != nullptr && pPicItem != nullptr)
    {

        int iheigth = wid->height() - 40;
        int iwidth = pPicItem->x() / pPicItem->y() * iheigth;
        setFixedSize(iwidth,iheigth);
        mscene->setSceneRect(1,1,iwidth -2,iheigth -2);
    }

    QGraphicsView::resizeEvent(event);
}

void GraphicsViewComp::setPicItem(PictureItem * pItem)
{
    QWidget * wid = parentWidget();
    if(wid != nullptr && pItem != nullptr)
    {

        int iheigth = wid->height() - 40;
        int iwidth = pItem->x() / pItem->y() * iheigth;
        setFixedSize(iwidth,iheigth);
        mscene->setSceneRect(2,2,iwidth -4,iheigth -4);

    }

    pPicItem = pItem;
    mscene->setPicItem(pItem);
    mscene->update();

}


////////////////////////////////PicGraphicsScene ///////////////////////////////////
PicGraphicsScene::PicGraphicsScene()
    :QGraphicsScene()
{
    setBackgroundBrush(Qt::white);
}

void PicGraphicsScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    QGraphicsScene::drawBackground(painter, rect);

    if(views().count()==0)
           return;

    if(mpItem == nullptr)
          return;

    // 计算视窗的大小,消除图元拖动时出现的残影
    QGraphicsView* pView=views().first();
    QRect contentRect=pView->viewport()->contentsRect();
    QRectF sceneRect =pView->mapToScene(contentRect).boundingRect();

    //绘制指定图片作为背景
    //QPixmap
    QPixmap pix = mpItem->pic();
    pix = pix.scaled(sceneRect.width(), sceneRect.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter->drawPixmap(sceneRect,mpItem->pic(),QRect());
}

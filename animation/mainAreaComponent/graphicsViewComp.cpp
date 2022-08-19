#include "graphicsViewComp.h"
#include "pictureItem.h"
#include <QGraphicsScene>
#include <QPushButton>
#include <QGraphicsWidget>
#include <QGraphicsLinearLayout>
#include <QTextEdit>
#include <QToolButton>
#include <QDebug>

GraphicsViewComp::GraphicsViewComp(QGraphicsScene *scene, QWidget *parent)
    :QGraphicsView(scene, parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void GraphicsViewComp::setGifSize(const QSize & size)
{
    sizeInf = size;
    refreashSize();
}

void GraphicsViewComp::refreashSize()
{
    QWidget * wid = parentWidget();
    if(wid != nullptr && pPicItem != nullptr)
    {
        PicGraphicsScene * pScene = (PicGraphicsScene *)scene();
        if(!pScene)
        {
            return;
        }


        int iheigth = wid->height() - 40;
        int iwidth = sizeInf.width() / sizeInf.height() * iheigth;
        if(sizeInf.width() > iwidth)
        {
            //wid->resize(iwidth,iheigth);
            setFixedSize(iwidth,iheigth);
            pScene->setSceneRect(0,0,sizeInf.width(),sizeInf.height());
        }else
        {
            //wid->resize(sizeInf.width(),sizeInf.height());
            setFixedSize(sizeInf.width(),sizeInf.height());
            pScene->setSceneRect(0,0,sizeInf.width(),sizeInf.height());
        }
        pScene->update();

    }
}

void GraphicsViewComp::paintEvent(QPaintEvent *event)
{

    QGraphicsView::paintEvent(event);
    //refreashSize();

}

void GraphicsViewComp::resizeEvent(QResizeEvent *event)
{
    //refreashSize();
    QGraphicsView::resizeEvent(event);
}

void GraphicsViewComp::setPicItem(PictureItem * pItem)
{

    pPicItem = pItem;

    PicGraphicsScene * pScene = (PicGraphicsScene *)scene();
    if(pScene)
    {
        pScene->setPicItem(pItem);

    }
    repaint();
}


////////////////////////////////PicGraphicsScene ///////////////////////////////////
PicGraphicsScene::PicGraphicsScene(QWidget * p)
    :QGraphicsScene(p)
{
    setBackgroundBrush(Qt::white);
}

void PicGraphicsScene::setPicItem(PictureItem * pItem)
{
    mpItem = pItem;
    if(pItem != nullptr)
    {
        pic = mpItem->pic();
        //setBackgroundBrush(pic);
    }
}


void PicGraphicsScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    QGraphicsScene::drawBackground(painter, rect);

    if(views().count()==0)
           return;

    if(mpItem == nullptr)
          return;

    QRectF sizeRec = sceneRect();
    //绘制指定图片作为背景
    //
    pic = pic.scaled(sizeRec.width(), sizeRec.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter->drawPixmap(sizeRec,pic,QRect());

}


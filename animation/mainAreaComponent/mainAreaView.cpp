#include "mainAreaView.h"
#include "emptyAreaView.h"
#include "graphicsViewComp.h"
#include "sacleButtonView.h"

#include<QPainter>
#include<QDebug>
#include<QHBoxLayout>

GraphicFrame::GraphicFrame(QWidget *parent)
    :QFrame(parent)
{
    scaleView = new ScaleButtonView(this);
    setConnect();

}

void GraphicFrame::setConnect()
{
    connect(scaleView, &ScaleButtonView::s_scaleFreash, this, &GraphicFrame::s_scaleFreash);
}

void GraphicFrame::showEvent(QShowEvent *event)
{
    if(isVisible())
    {
       scaleView->setGeometry(width() - 52, height() - 140, 50, 130);
    }
}

void GraphicFrame::resizeEvent(QResizeEvent *)
{
    scaleView->setGeometry(width() - 52, height() - 140, 50, 130);
}

/*----------GraphicFrame------------------*/

/*----------MainAreaView------------------*/
MainAreaView::MainAreaView(QWidget *parent)
    : QStackedWidget(parent)
{

    emptyView = new EmptyAreaView;
    addWidget(emptyView);

    graWid = new GraphicFrame;
    graWid->setFrameShape(QFrame::Panel);
    graWid->setFrameShadow(QFrame::Sunken);
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setContentsMargins(1,1,1,1);
    graWid->setLayout(layout);
    pScene = new PicGraphicsScene(graWid);
    graphicView = new GraphicsViewComp(pScene);
    layout->addWidget(graphicView);
    addWidget(graWid);

    setCurrentWidget(emptyView);

    setConnect();
}

void MainAreaView::setConnect()
{
    connect(emptyView, &EmptyAreaView::s_clicked, this, &MainAreaView::s_clicked);
    connect(graWid, &GraphicFrame::s_scaleFreash, this, [&](qreal lValue){
        //
        graphicView->scale(lValue, lValue);
    });
}

void MainAreaView::setGifCommpro(std::shared_ptr<propertyInf> inf)
{
    graphicView->setGifCommpro(inf);

}

void MainAreaView::slot_selPicItem(PictureItem * pItem)
{
    if(pItem == nullptr)
    {
        graphicView->setPicItem(pItem);
        setCurrentWidget(emptyView);
    }else
    {
        graphicView->setPicItem(pItem);
        setCurrentWidget(graWid);
    }

}

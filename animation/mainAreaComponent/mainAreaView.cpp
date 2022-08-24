#include "mainAreaView.h"
#include "emptyAreaView.h"
#include "graphicsViewComp.h"
#include<QPainter>
#include<QDebug>
#include<QHBoxLayout>

MainAreaView::MainAreaView(QWidget *parent)
    : QStackedWidget(parent)
{

    emptyView = new EmptyAreaView;
    addWidget(emptyView);

    graWid = new QFrame;
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

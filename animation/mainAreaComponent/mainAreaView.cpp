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

    graWid = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setContentsMargins(0,0,0,0);
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

void MainAreaView::setGifSize(const QSize & size)
{
    graphicView->setGifSize(size);
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

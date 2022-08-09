#include "mainAreaView.h"
#include "emptyAreaView.h"
#include "graphicsViewComp.h"
#include<QPainter>
#include<QDebug>

MainAreaView::MainAreaView(QWidget *parent)
    : QStackedWidget(parent)
{
    emptyView = new EmptyAreaView;
    addWidget(emptyView);
    graphicView = new GraphicsViewComp;
    addWidget(graphicView);

    setCurrentWidget(emptyView);

    setConnect();
}

void MainAreaView::setConnect()
{
    connect(emptyView, &EmptyAreaView::s_clicked, this, &MainAreaView::s_clicked);
}

void MainAreaView::slot_selPicItem(PictureItem * pItem)
{
    graphicView->setPicItem(pItem);
    setCurrentWidget(graphicView);
}

#include "propertyAreaView.h"
#include "commonPropertyView.h"

#include "dpi.h"
#include "tabbarpri.h"

#include "whiteBoardPropertyView.h"

#include<QDebug>
#include<QHBoxLayout>
#include <QTabBar>
#include <QStackedWidget>


PropertyAreaView::PropertyAreaView(QWidget *parent)
    : QWidget(parent)
{
    initial();
    setConnect();
}

void PropertyAreaView::setConnect()
{
    connect(commView, &CommonPropertyView::s_commproFresh, this, &PropertyAreaView::s_commproFresh);
    connect(whiteBoardView, &WhiteBoardPropertyView::s_whiteBoardProFresh, this, &PropertyAreaView::s_whiteBoardProFresh);
    connect(whiteBoardView, &WhiteBoardPropertyView::s_sceneItemInsert, this, &PropertyAreaView::s_sceneItemInsert);

    connect(whiteBoardView, &WhiteBoardPropertyView::s_saveToCurrentPicture, this, &PropertyAreaView::s_saveToCurrentPicture);
    connect(whiteBoardView, &WhiteBoardPropertyView::s_saveToAllPictures, this, &PropertyAreaView::s_saveToAllPictures);
    connect(whiteBoardView, &WhiteBoardPropertyView::s_clearGraphicsItems, this, &PropertyAreaView::s_clearGraphicsItems);


    connect(tabBar, &TabBarPri::sigCheckedChange, this, [&](int iIndex){
        tabWid->setCurrentIndex(iIndex);
    });
}

void PropertyAreaView::paintEvent(QPaintEvent *e)
{
    QWidget * wid = parentWidget();
    if(wid && wid->width() > width())
    {
        resize(QSize(wid->width(), height()));
    }
    QWidget::paintEvent(e);
}

void PropertyAreaView::initial()
{
    setObjectName("PropertyAreaView");
    QVBoxLayout * lay = new QVBoxLayout(this);
    lay->setContentsMargins(2,2,2,2);

    tabWid = new QStackedWidget;
    tabBar = new TabBarPri();
    tabBar->setWidth(105);
    lay->addWidget(tabBar);
    lay->addWidget(tabWid);

    commproInf = std::make_shared<propertyInf>();
    commView = new CommonPropertyView(commproInf);
    tabWid->addWidget(commView);
    tabBar->addTab(tr("Common"), tabStatus_checked);
    //addTab(commView, tr("Common"));

    whBoardProInf = std::make_shared<whiteBoardProInf>();
    whiteBoardView = new WhiteBoardPropertyView(whBoardProInf);
    tabWid->addWidget(whiteBoardView);
    //addTab(whiteBoardView, tr("White board"));
    tabBar->addTab(tr("White board"));
    tabWid->setCurrentIndex(0);
    tabBar->setCurrentIndex(0);
    setMinimumWidth(DPI::getScaleUI(320));
    setMinimumHeight(DPI::getScaleUI(780));
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
}

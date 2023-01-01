#include "propertyAreaView.h"
#include "commonPropertyView.h"

#include "dpi.h"

#include "whiteBoardPropertyView.h"

#include<QDebug>
#include<QHBoxLayout>
#include <QTabBar>


PropertyAreaView::PropertyAreaView(QWidget *parent)
    : QTabWidget(parent)
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
}

void PropertyAreaView::paintEvent(QPaintEvent *e)
{
    QWidget * wid = parentWidget();
    if(wid && wid->width() > width())
    {
        resize(QSize(wid->width(), height()));
    }
    QTabWidget::paintEvent(e);
}

void PropertyAreaView::initial()
{
    setObjectName("PropertyAreaView");

    commproInf = std::make_shared<propertyInf>();
    commView = new CommonPropertyView(commproInf);

    addTab(commView, QStringLiteral("Common"));

    whBoardProInf = std::make_shared<whiteBoardProInf>();
    whiteBoardView = new WhiteBoardPropertyView(whBoardProInf);
    addTab(whiteBoardView, QStringLiteral("whiteboard"));

    setMinimumWidth(DPI::getScaleUI(320));
    setMinimumHeight(DPI::getScaleUI(780));
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
}

#include "propertyAreaView.h"
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
    //connect(emptyView, &EmptyAreaView::s_clicked, this, &MainAreaView::s_clicked);
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
    addTab(new QWidget(), QStringLiteral("Common"));
    addTab(new QWidget(), QStringLiteral("specific"));
    addTab(new QWidget(), QStringLiteral("whiteboard"));
    addTab(new QWidget(), QStringLiteral("effects"));


    setMinimumWidth(320);
    setMinimumHeight(780);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);


}

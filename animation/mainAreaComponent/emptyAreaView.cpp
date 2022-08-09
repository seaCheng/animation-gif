#include "emptyAreaView.h"
#include<QDebug>
#include<QToolButton>
#include <QHBoxLayout>

EmptyAreaView::EmptyAreaView(QWidget *parent)
    : QWidget(parent)
{

    QToolButton *toolPicWid =  new QToolButton();
    connect(toolPicWid, &QToolButton::clicked, this, [=](){
        emit s_clicked(type_import::import_pic);
    });
    toolPicWid->setObjectName("toolPicWid");
    toolPicWid->setText(tr("pic add"));
    toolPicWid->setFixedSize(185,185);

    QToolButton *toolGifWid =  new QToolButton();
    connect(toolGifWid, &QToolButton::clicked, this, [=](){
        emit s_clicked(type_import::import_gif);
    });

    toolGifWid->setObjectName("toolGifWid");
    toolGifWid->setText(tr("gif load"));
    toolGifWid->setFixedSize(185,185);


    QHBoxLayout *layout = new QHBoxLayout;
    layout->setContentsMargins(10,10,10,10);
    layout->addStretch();
    layout->setSpacing(10);
    layout->addWidget(toolPicWid);
    layout->addWidget(toolGifWid);
    layout->addStretch();


    setLayout(layout);
}


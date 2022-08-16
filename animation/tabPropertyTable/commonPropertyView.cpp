#include "commonPropertyView.h"
#include<QDebug>
#include<QHBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QListWidget>
#include <QLineEdit>

CommonPropertyView::CommonPropertyView(QWidget *parent)
    : QFrame(parent)
{
    initial();
    setConnect();
}

void CommonPropertyView::setConnect()
{
    //connect(emptyView, &EmptyAreaView::s_clicked, this, &MainAreaView::s_clicked);
}

void CommonPropertyView::paintEvent(QPaintEvent *e)
{

    QFrame::paintEvent(e);
}

void CommonPropertyView::initial()
{
    setObjectName("CommonPropertyView");


    comSize = new QComboBox;
    comSize->setMinimumWidth(200);
    //comSize->setView(new  QListView());

    comSize->addItem(QStringLiteral("88 * 31 pix"));
    comSize->addItem(QStringLiteral("230 * 33 pix"));
    comSize->addItem(QStringLiteral("234 * 60 pix"));
    comSize->addItem(QStringLiteral("336 * 280 pix"));
    comSize->addItem(QStringLiteral("468 * 60 pix"));
    comSize->addItem(QStringLiteral("60 * 60 pix"));
    comSize->addItem(QStringLiteral("75 * 75 pix"));
    comSize->addItem(QStringLiteral("120 * 120 pix"));
    comSize->addItem(QStringLiteral("120 * 240 pix"));
    comSize->addItem(QStringLiteral("360 * 240 pix"));
    comSize->addItem(QStringLiteral("640 * 960 pix"));
    comSize->addItem(QStringLiteral("360 * 480 pix"));
    comSize->addItem(QStringLiteral("120 * 90 pix"));
    comSize->addItem(QStringLiteral("640 * 480 pix"));
    comSize->addItem(QStringLiteral("180 * 150 pix"));
    comSize->addItem(QStringLiteral("300 * 250 pix"));
    comSize->addItem(QStringLiteral("640 * 400 pix"));



    comSize->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    QLabel *lSize = new QLabel;
    lSize->setText(QStringLiteral("size:"));
    lSize->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    QHBoxLayout * sizeLay = new QHBoxLayout;
    sizeLay->setContentsMargins(0,0,0,0);
    sizeLay->setSpacing(5);
    sizeLay->addStretch(1);
    sizeLay->addWidget(lSize);
    sizeLay->addWidget(comSize);

    sizeLay->addStretch(1);

    QVBoxLayout * lay = new QVBoxLayout;
    lay->setContentsMargins(0,0,0,0);
    lay->setSpacing(5);
    lay->addItem(sizeLay);
    lay->addStretch(15);

    setLayout(lay);
}


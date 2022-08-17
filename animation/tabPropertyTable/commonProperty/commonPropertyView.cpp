#include "commonPropertyView.h"
#include<QDebug>
#include<QHBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QListWidget>
#include <QLineEdit>

#include <QUuid>
#include <QStyledItemDelegate>

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

    pSizeOp = std::make_unique<GifSizeOp>();

    connect(pSizeOp.get(), &GifSizeOp::s_insertItem, this, [&](QString name, QString uuid){
        comSize->addItem(name, uuid.toStdString().c_str());
    });
    pSizeOp->readData();
    prIndex = comSize->currentIndex();
    comSize->insertSeparator(comSize->count());

    uuid = QUuid::createUuid().toByteArray().data();

    comSize->addItem(QStringLiteral("管理自定义尺寸"), uuid.toStdString().c_str());
    connect(comSize, &QComboBox::currentIndexChanged, this, [&](int index){

        if(index == comSize->count() - 1)
        {
            comSize->blockSignals(true);
            comSize->setCurrentIndex(prIndex);
            comSize->blockSignals(false);
        }else
        {
            prIndex = index;
        }

    });


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


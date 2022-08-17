#include "commonPropertyView.h"
#include<QDebug>
#include<QHBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>

#include <QUuid>
#include <QStyledItemDelegate>


/*--------------------customSizeOp--------------------------------------*/
customSizeOp::customSizeOp(QWidget *parent)
    : QFrame(parent)
{
    initial();
    setConnect();
}

void customSizeOp::setConnect()
{
    //connect(emptyView, &EmptyAreaView::s_clicked, this, &MainAreaView::s_clicked);
}

void customSizeOp::paintEvent(QPaintEvent *e)
{
    QFrame::paintEvent(e);
}

void customSizeOp::initial()
{
    setObjectName("customSizeOp");

    QListView * view = new QListView;
    view->setMinimumSize(350, 270);

    QPushButton * addBtn = new QPushButton;
    addBtn->setText(QStringLiteral("+"));
    addBtn->setFixedSize(40,30);

    QPushButton * minuBtn = new QPushButton;
    minuBtn->setText(QStringLiteral("-"));
    minuBtn->setFixedSize(40,30);

    QPushButton * okBtn = new QPushButton;
    okBtn->setText(QStringLiteral("OK"));

    QHBoxLayout * hlBoxLayout = new QHBoxLayout;
    hlBoxLayout->setContentsMargins(0,0,0,0);
    hlBoxLayout->setSpacing(15);

    hlBoxLayout->addWidget(addBtn);
    hlBoxLayout->addWidget(minuBtn);
    hlBoxLayout->addStretch(5);
    hlBoxLayout->addWidget(okBtn);

    QVBoxLayout * hlVBoxLayout = new QVBoxLayout;
    hlVBoxLayout->setContentsMargins(0,0,0,0);
    hlVBoxLayout->setSpacing(15);

    hlVBoxLayout->addWidget(view);
    hlVBoxLayout->addItem(hlBoxLayout);

    QHBoxLayout * hrwBoxLayout = new QHBoxLayout;
    hrwBoxLayout->setContentsMargins(0,0,0,0);
    hrwBoxLayout->setSpacing(15);

    QLabel * lWidth = new QLabel;
    lWidth->setText(QStringLiteral("width:"));
    lWidth->setAlignment(Qt::AlignRight | Qt::AlignHCenter);
    hrwBoxLayout->addWidget(lWidth);
    QLineEdit * edWidth = new QLineEdit;
    hrwBoxLayout->addWidget(edWidth);

    QHBoxLayout * hrhBoxLayout = new QHBoxLayout;
    hrhBoxLayout->setContentsMargins(0,0,0,0);
    hrhBoxLayout->setSpacing(15);

    QLabel * lheigth = new QLabel;
    lheigth->setText(QStringLiteral("heigth:"));
    lheigth->setAlignment(Qt::AlignRight | Qt::AlignHCenter);
    hrhBoxLayout->addWidget(lWidth);

    QLineEdit * edHeigth = new QLineEdit;
    hrhBoxLayout->addWidget(edHeigth);

    QVBoxLayout * hRVBoxLayout = new QVBoxLayout;
    hRVBoxLayout->setContentsMargins(0,0,0,0);
    hRVBoxLayout->setSpacing(15);

    hRVBoxLayout->addItem(hrwBoxLayout);
    hRVBoxLayout->addItem(hrhBoxLayout);


    QHBoxLayout * hLayout = new QHBoxLayout;
    hLayout->setContentsMargins(0,0,0,0);
    hLayout->setSpacing(15);

    hLayout->addItem(hlVBoxLayout);
    hLayout->addItem(hRVBoxLayout);

    setLayout(hLayout);
}

/*--------------------customSizeOp--------------------------------------*/

/*--------------------CommonPropertyView--------------------------------------*/
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
    pSizeOp->readData();

    std::vector<sizeInf> lst = pSizeOp->getSizeInf();
    for(const auto &u : lst)
    {
        comSize->addItem(u.name, u.uuid.toStdString().c_str());
    }
    prIndex = comSize->currentIndex();
    comSize->insertSeparator(comSize->count());

    uuid = QUuid::createUuid().toByteArray().data();

    comSize->addItem(QStringLiteral("管理自定义"), uuid.toStdString().c_str());
    connect(comSize, &QComboBox::currentIndexChanged, this, [&](int index){

        if(index == comSize->count() - 1)
        {
            comSize->blockSignals(true);
            comSize->setCurrentIndex(prIndex);
            comSize->blockSignals(false);

            customSizeOp * cust = new customSizeOp;
            cust->show();
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
    lay->setContentsMargins(0,10,0,0);
    lay->setSpacing(5);
    lay->addItem(sizeLay);
    lay->addStretch(15);

    setLayout(lay);
}


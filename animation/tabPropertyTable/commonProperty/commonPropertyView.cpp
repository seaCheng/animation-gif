#include "commonPropertyView.h"
#include "propertyAreaView.h"

#include<QDebug>
#include<QHBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>

#include <QUuid>
#include <QPainter>
#include <QStyledItemDelegate>
#include <QRegExp>
#include <QIntValidator>
#include <QStandardItemModel>
#include <QStringListModel>
#include <QRadioButton>
#include <QColorDialog>
#include <QTabBar>
#include <QSpinBox>


/*---------------------QFrameColor-------------------------------------*/

QColorFrame::QColorFrame()
{
    setObjectName("QColorFrame");

    setFixedSize(60,30);
    setLineWidth(1);

    setFrameShadow(QFrame::Plain);
    setFrameShape(QFrame::Box);
    setStyleSheet("border:1px solid rgb(0,0,0); \
                  background-color:rgba(214,249,255, 100);");
}

void QColorFrame::paintEvent(QPaintEvent *e)
{
    QFrame::paintEvent(e);
    QPainter p;
    p.setPen(gifColor);
    QRectF rectangle(8, 8, width() - 8*2, height() - 8 * 2);
    QPainter painter(this);
    painter.setBrush(gifColor);
    painter.drawRect(rectangle);
}

void QColorFrame::mousePressEvent(QMouseEvent *e)
{
    setStyleSheet("border:1px solid rgb(0,0,0); \
                  background-color:rgba(214,249,255, 250);");
}

void QColorFrame::mouseReleaseEvent(QMouseEvent *e)
{
    setStyleSheet("border:1px solid rgb(0,0,0); \
                  background-color:rgba(214,249,255, 100);");
            QFrame::mouseReleaseEvent(e);

    emit s_clicked();
}

bool QColorFrame::event( QEvent *e)
{
    static int counting=0;
    if (e->type() ==QEvent::Enter)
    {
        setStyleSheet("border:1px solid rgb(0,0,0); \
                      background-color:rgba(214,249,255, 150);");
        qDebug() << counting++ << " Enter: " << this->objectName();
    }
    if (e->type() ==QEvent::Leave)
    {
        setStyleSheet("border:1px solid rgb(0,0,0); \
                      background-color:rgba(214,249,255, 100);");
        qDebug() << counting++ << " Leave: " << this->objectName();
    }

    return QFrame::event(e);
}

void QColorFrame::setGifColor(const QColor & color)
{
    gifColor = color;
    repaint();

}

/*---------------------QFrameColor-------------------------------------*/

/*--------------------customSizeOp--------------------------------------*/
customSizeOp::customSizeOp(QWidget *parent)
    : QDialog(parent)
{
    initial();
    setConnect();
}

void customSizeOp::setConnect()
{

    connect(stModel, &QStandardItemModel::itemChanged, [&](QStandardItem *item){
        QModelIndex index = item->index();
        QString str = stModel->data(index, Qt::UserRole).toString();
        GifSizeOp::getInstance()->setName(item->text(), str);

    });
    connect(this, &customSizeOp::s_dataFrash, [&]{

        QModelIndex index = view->currentIndex();

        QString str = stModel->data(index, Qt::UserRole).toString();
        sizeInf inf = GifSizeOp::getInstance()->getSizeInfBU(str);
        edWidth->blockSignals(true);
        edWidth->setText(QString("%1").arg(inf.width));
        edWidth->blockSignals(false);

        edHeigth->blockSignals(true);
        edHeigth->setText(QString("%1").arg(inf.heigth));
        edHeigth->blockSignals(false);

    });

    connect(okBtn, &QPushButton::clicked, [&]{

        //if(icount != stModel->rowCount())
        {
            GifSizeOp::getInstance()->saveData();
            QModelIndex index = view->currentIndex();
            QString str = stModel->data(index, Qt::UserRole).toString();

            emit s_customData(str);
        }

        close();
    });

    connect(cancelBtn, &QPushButton::clicked, [&]{

        close();
    });

    connect(addBtn, &QPushButton::clicked, [&]{
        int row = stModel->rowCount();
        QString name = QString("untitled_%1").arg(row);

        stModel->appendRow(new QStandardItem(name));
        // Get the row for Edit mode
        QModelIndex index = stModel->index(row, 0);
        sizeInf inf;
        inf.bCustom = true;
        inf.width = 360;
        inf.heigth = 240;
        inf.name = name;
        inf.uuid = QUuid::createUuid().toByteArray().data();

        GifSizeOp::getInstance()->addSizeInf(inf);

        stModel->blockSignals(true);
        stModel->setData(index, inf.uuid, Qt::UserRole);
        stModel->blockSignals(false);

        view->setCurrentIndex(index);
        view->edit(index);

        emit s_dataFrash();
    });

    connect(subBtn, &QPushButton::clicked, [&]{

        QModelIndex index = view->currentIndex();
        if(!index.isValid())
        {
            return;
        }
        GifSizeOp::getInstance()->removeSize(stModel->data(index, Qt::UserRole).toString());
        stModel->removeRow(index.row());

        emit s_dataFrash();

    });


    connect(view, &QListView::clicked, [&](const QModelIndex &index){
        QString str = stModel->data(index, Qt::UserRole).toString();
        sizeInf inf = GifSizeOp::getInstance()->getSizeInfBU(str);
        edWidth->blockSignals(true);
        edWidth->setText(QString("%1").arg(inf.width));
        edWidth->blockSignals(false);

        edHeigth->blockSignals(true);
        edHeigth->setText(QString("%1").arg(inf.heigth));
        edHeigth->blockSignals(false);

    });

    connect(edWidth, &QLineEdit::textChanged, [&](const QString & str){

        int iwidth = edWidth->text().toInt();
        int iheigth = edHeigth->text().toInt();

        QModelIndex index = view->currentIndex();

        GifSizeOp::getInstance()->setdata(iwidth, iheigth, stModel->data(index, Qt::UserRole).toString());

    });

    connect(edHeigth, &QLineEdit::textChanged, [&](const QString & str){
        int iwidth = edWidth->text().toInt();
        int iheigth = edHeigth->text().toInt();

        QModelIndex index = view->currentIndex();

        GifSizeOp::getInstance()->setdata(iwidth, iheigth, stModel->data(index, Qt::UserRole).toString());

    });

}

void customSizeOp::showEvent(QShowEvent *event)
{
    stModel->clear();
    std::vector<sizeInf> lst = GifSizeOp::getInstance()->getSizeInf();
    QStandardItem * pItem = nullptr;
    for(const auto &u : lst)
    {
        if(u.bCustom)
        {
            pItem = new QStandardItem(u.name);
            pItem->setData(u.uuid, Qt::UserRole);
            stModel->appendRow(pItem);

            sizeInf inf = GifSizeOp::getInstance()->getSizeInfBU(u.uuid);

            edWidth->blockSignals(true);
            edWidth->setText(QString("%1").arg(inf.width));
            edWidth->blockSignals(false);

            edHeigth->blockSignals(true);
            edHeigth->setText(QString("%1").arg(inf.heigth));
            edHeigth->blockSignals(false);

            view->setCurrentIndex(pItem->index());

        }
    }

    icount = stModel->rowCount();

}

void customSizeOp::paintEvent(QPaintEvent *e)
{
    QDialog::paintEvent(e);
}

void customSizeOp::initial()
{
    setObjectName("customSizeOp");

    view = new QListView;
    view->setMinimumSize(350, 270);

    stModel = new QStandardItemModel;
    QStringList lst;

    view->setModel(stModel);

    addBtn = new QPushButton;
    addBtn->setText(QStringLiteral("+"));
    addBtn->setFixedSize(40,30);

    subBtn = new QPushButton;
    subBtn->setText(QStringLiteral("-"));
    subBtn->setFixedSize(40,30);

    okBtn = new QPushButton;
    okBtn->setText(QStringLiteral("OK"));

    cancelBtn = new QPushButton;
    cancelBtn->setText(QStringLiteral("Cancel"));

    QHBoxLayout * hlBoxLayout = new QHBoxLayout;
    hlBoxLayout->setContentsMargins(10,0,10,0);
    hlBoxLayout->setSpacing(15);

    hlBoxLayout->addWidget(addBtn);
    hlBoxLayout->addWidget(subBtn);
    hlBoxLayout->addStretch(5);
    hlBoxLayout->addWidget(cancelBtn);
    hlBoxLayout->addWidget(okBtn);

    QVBoxLayout * hlVBoxLayout = new QVBoxLayout;
    hlVBoxLayout->setContentsMargins(0,0,0,0);
    hlVBoxLayout->setSpacing(15);

    hlVBoxLayout->addWidget(view);
    hlVBoxLayout->addItem(hlBoxLayout);

    QHBoxLayout * hrwBoxLayout = new QHBoxLayout;
    hrwBoxLayout->setContentsMargins(10,0,10,0);
    hrwBoxLayout->setSpacing(15);

    QLabel * lWidth = new QLabel;
    lWidth->setText(QStringLiteral("width:"));
    lWidth->setAlignment(Qt::AlignRight | Qt::AlignHCenter);
    lWidth->setFixedWidth(45);
    hrwBoxLayout->addWidget(lWidth);

    QValidator *validator = new QIntValidator(10, 2000, this);
    edWidth = new QLineEdit;
    edWidth->setFixedWidth(160);
    edWidth->setValidator(validator);
    hrwBoxLayout->addWidget(edWidth);

    QHBoxLayout * hrhBoxLayout = new QHBoxLayout;
    hrhBoxLayout->setContentsMargins(0,0,0,0);
    hrhBoxLayout->setSpacing(15);

    QLabel * lheigth = new QLabel;
    lheigth->setText(QStringLiteral("heigth:"));
    lheigth->setAlignment(Qt::AlignRight | Qt::AlignHCenter);
    lheigth->setFixedWidth(45);
    hrhBoxLayout->addWidget(lheigth);

    edHeigth = new QLineEdit;
    edHeigth->setFixedWidth(160);
    edHeigth->setValidator(validator);

    hrhBoxLayout->addWidget(edHeigth);

    QVBoxLayout * hRVBoxLayout = new QVBoxLayout;
    hRVBoxLayout->setContentsMargins(0,20,0,0);
    hRVBoxLayout->setSpacing(25);

    hRVBoxLayout->addItem(hrwBoxLayout);
    hRVBoxLayout->addItem(hrhBoxLayout);

    hRVBoxLayout->addStretch(5);

    QHBoxLayout * hLayout = new QHBoxLayout;
    hLayout->setContentsMargins(0,0,0,10);
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
    connect(comSize, &QComboBox::currentIndexChanged, this, [&](int index){

        if(index == comSize->count() - 1)
        {
            comSize->blockSignals(true);
            comSize->setCurrentIndex(prIndex);
            comSize->blockSignals(false);

            custOP->exec();
        }else
        {
            prIndex = index;
            refreashGifSize();
        }

    });

    connect(custOP.get(), &customSizeOp::s_customData, this, [&](QString strUUid){
        comSize->clear();

        std::vector<sizeInf> lst = GifSizeOp::getInstance()->getSizeInf();
        for(const auto &u : lst)
        {
            comSize->addItem(u.name, u.uuid.toStdString().c_str());
        }

        int index = comSize->count();
        comSize->insertSeparator(comSize->count());
        uuid = QUuid::createUuid().toByteArray().data();
        comSize->addItem(QStringLiteral("管理自定义"), uuid.toStdString().c_str());
        comSize->setCurrentIndex(index - 1);
        prIndex = comSize->currentIndex();

    });

    connect(fColor, &QColorFrame::s_clicked, this, [&](){

        const QColorDialog::ColorDialogOptions options = QFlag(QColorDialog::ShowAlphaChannel);
        const QColor color = QColorDialog::getColor(Qt::white, this, "Select Color", options);

        if (color.isValid()) {
             fColor->setGifColor(color);
        }
    });

}

void CommonPropertyView::paintEvent(QPaintEvent *e)
{
    QFrame::paintEvent(e);
}

void CommonPropertyView::initial()
{
    setObjectName("CommonPropertyView");
    //size
    comSize = new QComboBox;
    comSize->setMinimumWidth(200);
    GifSizeOp::getInstance()->readData();
    custOP = std::make_unique<customSizeOp>();

    std::vector<sizeInf> lst = GifSizeOp::getInstance()->getSizeInf();
    for(const auto &u : lst)
    {
        comSize->addItem(u.name, u.uuid.toStdString().c_str());
    }

    comSize->insertSeparator(comSize->count());
    uuid = QUuid::createUuid().toByteArray().data();
    comSize->addItem(QStringLiteral("管理自定义"), uuid.toStdString().c_str());
    prIndex = comSize->currentIndex();
    refreashGifSize();

    comSize->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    QLabel *lSize = new QLabel;
    lSize->setText(QStringLiteral("size:"));
    lSize->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lSize->setFixedWidth(100);

    QHBoxLayout * sizeLay = new QHBoxLayout;
    sizeLay->setContentsMargins(0,0,0,0);
    sizeLay->setSpacing(5);

    sizeLay->addWidget(lSize);
    sizeLay->addWidget(comSize);

    sizeLay->addStretch(1);

    //横屏 &竖屏幕
    hRadioBtn = new QRadioButton;
    hRadioBtn->setChecked(true);
    hRadioBtn->setText(QStringLiteral("横屏"));
    vRadioBtn = new QRadioButton;
    vRadioBtn->setText(QStringLiteral("竖屏"));
    QHBoxLayout * hRadLay = new QHBoxLayout;
    hRadLay->setContentsMargins(0,0,0,0);
    hRadLay->setSpacing(24);
    hRadLay->addStretch(1);
    hRadLay->addWidget(hRadioBtn);
    hRadLay->addWidget(vRadioBtn);
    hRadLay->addStretch(1);

    //填充方式
    QLabel *lfill = new QLabel;
    lfill->setText(QStringLiteral("填充方式:"));
    lfill->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lfill->setFixedWidth(100);

    comFill = new QComboBox;
    comFill->addItem(QStringLiteral("充满"), fill_full);
    comFill->addItem(QStringLiteral("适应"), fill_adjust);
    comFill->addItem(QStringLiteral("拉伸"), fill_stretch);
    comFill->setMinimumWidth(200);

    QHBoxLayout * fillLay = new QHBoxLayout;
    fillLay->setContentsMargins(0,0,0,0);
    fillLay->setSpacing(5);

    fillLay->addWidget(lfill);
    fillLay->addWidget(comFill);
    fillLay->addStretch(1);

    //颜色
    QLabel *lColor = new QLabel;
    lColor->setText(QStringLiteral("颜色:"));
    lColor->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lColor->setFixedWidth(100);

    fColor = new QColorFrame;
    QHBoxLayout * colorLay = new QHBoxLayout;
    colorLay->setContentsMargins(0,0,0,0);
    colorLay->setSpacing(5);

    colorLay->addWidget(lColor);
    colorLay->addWidget(fColor);
    colorLay->addStretch(1);

    //速度
    QLabel *lSpeedBar = new QLabel;
    lSpeedBar->setText(QStringLiteral("速度:"));
    lSpeedBar->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lSpeedBar->setFixedWidth(100);

    speedBar = new QTabBar;
    speedBar->setObjectName("speedBar");
    speedBar->addTab(QStringLiteral("常规"));
    speedBar->addTab(QStringLiteral("自动"));

    QHBoxLayout * speedbarLay = new QHBoxLayout;
    speedbarLay->setContentsMargins(0,0,0,0);
    speedbarLay->setSpacing(5);
    speedbarLay->addWidget(lSpeedBar);
    speedbarLay->addWidget(speedBar);

    //帧延时     QSpinBox * timeSpinBox = nullptr;

    QLabel *lSpeedTime = new QLabel;
    lSpeedTime->setText(QStringLiteral("帧延时(ms):"));
    lSpeedTime->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lSpeedTime->setFixedWidth(100);

    secondSpinBox = new QSpinBox;
    secondSpinBox->setRange(20, 10000);

    QHBoxLayout * timerLay = new QHBoxLayout;
    timerLay->setContentsMargins(0,0,0,0);
    timerLay->setSpacing(5);
    timerLay->addWidget(lSpeedTime);
    timerLay->addWidget(secondSpinBox);

    QLabel *lSpeedSecond= new QLabel;
    lSpeedSecond->setText(QStringLiteral("帧数(p-s):"));
    lSpeedSecond->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lSpeedSecond->setFixedWidth(100);

    timeSpinBox = new QSpinBox;
    timeSpinBox->setRange(1, 30);

    QHBoxLayout * secondLay = new QHBoxLayout;
    secondLay->setContentsMargins(0,0,0,0);
    secondLay->setSpacing(5);
    secondLay->addWidget(lSpeedSecond);
    secondLay->addWidget(timeSpinBox);


    QVBoxLayout * lay = new QVBoxLayout;
    lay->setContentsMargins(25,25,25,25);
    lay->setSpacing(12);
    lay->addItem(sizeLay);
    lay->addItem(hRadLay);
    lay->addItem(fillLay);
    lay->addItem(colorLay);

    QFrame *fLine = new QFrame;
    fLine->setStyleSheet("border:1px solid rgba(10,10,10, 30);");
    fLine->setFixedHeight(1);
    lay->addWidget(fLine);

    lay->addItem(speedbarLay);
    lay->addItem(timerLay);
    lay->addItem(secondLay);

    lay->addStretch(15);

    setLayout(lay);
}

void CommonPropertyView::refreashGifSize()
{
    QString strUUid = comSize->currentData().toString();

    sizeInf inf = GifSizeOp::getInstance()->getSizeInfBU(strUUid);
    gifSize = QSize(inf.width, inf.heigth);

    emit s_sizeFresh(gifSize);
}

QSize CommonPropertyView::getGifSize()
{
    return gifSize;
}

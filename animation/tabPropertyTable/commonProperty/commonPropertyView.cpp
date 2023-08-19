#include "commonPropertyView.h"
#include "dpi.h"

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
#include <QButtonGroup>
#include <QEvent>


/*---------------------QFrameColor-------------------------------------*/

QColorFrame::QColorFrame()
{
    setObjectName("QColorFrame");

    setFixedSize(DPI::getScaleUI(60),DPI::getScaleUI(30));
    setLineWidth(DPI::getScaleUI(1));

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
    QRectF rectangle(DPI::getScaleUI(8), DPI::getScaleUI(8), width() - DPI::getScaleUI(16), height() - DPI::getScaleUI(16));
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
    }
    if (e->type() ==QEvent::Leave)
    {
        setStyleSheet("border:1px solid rgb(0,0,0); \
                      background-color:rgba(214,249,255, 100);");
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
    view->setMinimumSize(DPI::getScaleUI(350), DPI::getScaleUI(270));

    stModel = new QStandardItemModel;
    QStringList lst;

    view->setModel(stModel);

    addBtn = new QPushButton;
    addBtn->setText(QStringLiteral("+"));
    addBtn->setFixedSize(DPI::getScaleUI(40),DPI::getScaleUI(30));

    subBtn = new QPushButton;
    subBtn->setText(QStringLiteral("-"));
    subBtn->setFixedSize(DPI::getScaleUI(40),DPI::getScaleUI(30));

    okBtn = new QPushButton;
    okBtn->setText(tr("OK"));

    cancelBtn = new QPushButton;
    cancelBtn->setText(tr("Cancel"));

    QHBoxLayout * hlBoxLayout = new QHBoxLayout;
    hlBoxLayout->setContentsMargins(DPI::getScaleUI(10),0,DPI::getScaleUI(10),0);
    hlBoxLayout->setSpacing(DPI::getScaleUI(15));

    hlBoxLayout->addWidget(addBtn);
    hlBoxLayout->addWidget(subBtn);
    hlBoxLayout->addStretch(DPI::getScaleUI(5));
    hlBoxLayout->addWidget(cancelBtn);
    hlBoxLayout->addWidget(okBtn);

    QVBoxLayout * hlVBoxLayout = new QVBoxLayout;
    hlVBoxLayout->setContentsMargins(0,0,0,0);
    hlVBoxLayout->setSpacing(DPI::getScaleUI(15));

    hlVBoxLayout->addWidget(view);
    hlVBoxLayout->addItem(hlBoxLayout);

    QHBoxLayout * hrwBoxLayout = new QHBoxLayout;
    hrwBoxLayout->setContentsMargins(DPI::getScaleUI(10),0,DPI::getScaleUI(10),0);
    hrwBoxLayout->setSpacing(DPI::getScaleUI(15));

    QLabel * lWidth = new QLabel;
    lWidth->setText(tr("width:"));
    lWidth->setAlignment(Qt::AlignRight | Qt::AlignHCenter);
    lWidth->setFixedWidth(DPI::getScaleUI(45));
    hrwBoxLayout->addWidget(lWidth);

    QValidator *validator = new QIntValidator(10, 2000, this);
    edWidth = new QLineEdit;
    edWidth->setFixedWidth(DPI::getScaleUI(160));
    edWidth->setValidator(validator);
    hrwBoxLayout->addWidget(edWidth);

    QHBoxLayout * hrhBoxLayout = new QHBoxLayout;
    hrhBoxLayout->setContentsMargins(0,0,0,0);
    hrhBoxLayout->setSpacing(DPI::getScaleUI(15));

    QLabel * lheigth = new QLabel;
    lheigth->setText(tr("heigth:"));
    lheigth->setAlignment(Qt::AlignRight | Qt::AlignHCenter);
    lheigth->setFixedWidth(DPI::getScaleUI(45));
    hrhBoxLayout->addWidget(lheigth);

    edHeigth = new QLineEdit;
    edHeigth->setFixedWidth(DPI::getScaleUI(160));
    edHeigth->setValidator(validator);

    hrhBoxLayout->addWidget(edHeigth);

    QVBoxLayout * hRVBoxLayout = new QVBoxLayout;
    hRVBoxLayout->setContentsMargins(0,DPI::getScaleUI(20),0,0);
    hRVBoxLayout->setSpacing(DPI::getScaleUI(25));

    hRVBoxLayout->addItem(hrwBoxLayout);
    hRVBoxLayout->addItem(hrhBoxLayout);

    hRVBoxLayout->addStretch(DPI::getScaleUI(5));

    QHBoxLayout * hLayout = new QHBoxLayout;
    hLayout->setContentsMargins(0,0,0,DPI::getScaleUI(10));
    hLayout->setSpacing(DPI::getScaleUI(15));

    hLayout->addItem(hlVBoxLayout);
    hLayout->addItem(hRVBoxLayout);

    setLayout(hLayout);
}

/*--------------------customSizeOp--------------------------------------*/

/*--------------------CommonPropertyView--------------------------------------*/
CommonPropertyView::CommonPropertyView(std::shared_ptr<propertyInf> inf, QWidget *parent)
    : QFrame(parent), proInf(inf)
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
        comSize->addItem(tr("Manage Customizations"), uuid.toStdString().c_str());
        comSize->setCurrentIndex(index - 1);
        prIndex = comSize->currentIndex();

    });

    connect(fColor, &QColorFrame::s_clicked, this, [&](){

        //const QColorDialog::ColorDialogOptions options = QFlag(QColorDialog::ShowAlphaChannel);
        //const QColor color = QColorDialog::getColor(Qt::white, this, "Select Color", options);
        //const QColor color = QColorDialog::getColor(proInf->color, this, "Select Color", options);
        colorDialog->setCurrentColor(proInf->color);
        colorDialog->exec();

    });

    /*
    connect(speedBar, &QTabBar::currentChanged, this, [&](int index){
        if(index == 0)
        {
            timeSpinBox->setVisible(true);
            secondSpinBox->setVisible(false);

            lSpeedTime->setVisible(true);
            lSpeedSecond->setVisible(false);
        }else
        {
            timeSpinBox->setVisible(false);
            secondSpinBox->setVisible(true);

            lSpeedTime->setVisible(false);
            lSpeedSecond->setVisible(true);
        }
    });
    */


    connect(gDelayBtn, &QButtonGroup::buttonClicked, this, [&](QAbstractButton *button){

        QRadioButton * screenBtn = (QRadioButton *)button;

        if(screenBtn == speedTimeRadioBtn)
        {
            timeSpinBox->setVisible(true);
            secondSpinBox->setVisible(false);

            lSpeedTime->setVisible(true);
            lSpeedSecond->setVisible(false);
        }else if(screenBtn == speedSecondRadioBtn)
        {
            timeSpinBox->setVisible(false);
            secondSpinBox->setVisible(true);

            lSpeedTime->setVisible(false);
            lSpeedSecond->setVisible(true);
        }


    });

    connect(comFill, &QComboBox::currentIndexChanged, this, [&](int index){

        proInf->fMode = (fillMode)comFill->currentData().toInt();
        emit s_commproFresh();
    });

    connect(gScreenrBtn, &QButtonGroup::buttonClicked, this, [&](QAbstractButton *button){

        QRadioButton * screenBtn = (QRadioButton *)button;

        if(screenBtn == hRadioBtn)
        {
           proInf->scMode = screen_horizal;
        }else if(screenBtn == vRadioBtn)
        {
           proInf->scMode = screen_vertical;
        }

        emit s_commproFresh();
    });

    connect(gOrderBtn, &QButtonGroup::buttonClicked, this, [&](QAbstractButton *button){

        QRadioButton * screenBtn = (QRadioButton *)button;

        if(screenBtn == orderRadioBtn)
        {
           proInf->oMode = order_compliant;
        }else if(screenBtn == revRadioBtn)
        {
           proInf->oMode = order_reverse;
        }

        emit s_commproFresh();
    });

    connect(timeSpinBox, &QSpinBox::valueChanged, this, [&](int value){
        proInf->delay = timeSpinBox->value();
        emit s_commproFresh();
    });

    connect(secondSpinBox, &QSpinBox::valueChanged, this, [&](int value){
        proInf->delay = 1000 / secondSpinBox->value();
        emit s_commproFresh();
    });

    connect(comQuality, &QComboBox::currentIndexChanged, this, [&](int index){
        proInf->qMode = (qualityMode)comQuality->currentData().toInt();
        emit s_commproFresh();
    });

    connect(colorDialog, &QColorDialog::currentColorChanged, this, [&](const QColor &color){

        if (color.isValid()) {
             fColor->setGifColor(color);
             proInf->color = color;

             emit s_commproFresh();
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

    const QColorDialog::ColorDialogOptions options = QFlag(QColorDialog::ShowAlphaChannel | QColorDialog::NoButtons);
    colorDialog = new QColorDialog(this);
    colorDialog->setCurrentColor(Qt::white);
    colorDialog->setOptions(options);


    //size
    comSize = new QComboBox;
    comSize->setMinimumWidth(DPI::getScaleUI(200));
    GifSizeOp::getInstance()->readData();
    custOP = std::make_unique<customSizeOp>();

    std::vector<sizeInf> lst = GifSizeOp::getInstance()->getSizeInf();
    for(const auto &u : lst)
    {
        comSize->addItem(u.name, u.uuid.toStdString().c_str());
    }

    comSize->insertSeparator(comSize->count());
    uuid = QUuid::createUuid().toByteArray().data();
    comSize->addItem(tr("Manage Customizations"), uuid.toStdString().c_str());
    comSize->setCurrentIndex(9);
    prIndex = comSize->currentIndex();
    refreashGifSize();

    comSize->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    QLabel *lSize = new QLabel;
    lSize->setText(tr("size:"));
    lSize->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lSize->setFixedWidth(DPI::getScaleUI(100));

    QHBoxLayout * sizeLay = new QHBoxLayout;
    sizeLay->setContentsMargins(0,0,0,0);
    sizeLay->setSpacing(DPI::getScaleUI(5));

    sizeLay->addWidget(lSize);
    sizeLay->addWidget(comSize);

    sizeLay->addStretch(1);

    //横屏 &竖屏幕
    QLabel *lScreen = new QLabel;
    lScreen->setText(tr("Screen:"));
    lScreen->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lScreen->setFixedWidth(DPI::getScaleUI(100));

    gScreenrBtn = new QButtonGroup(this);
    gScreenrBtn->setExclusive(true);
    hRadioBtn = new QRadioButton;
    hRadioBtn->setChecked(true);

    proInf->scMode = screen_horizal;

    hRadioBtn->setText(tr("Landscape"));
    gScreenrBtn->addButton(hRadioBtn);

    vRadioBtn = new QRadioButton;
    vRadioBtn->setText(tr("Portrait"));
    gScreenrBtn->addButton(vRadioBtn);

    QHBoxLayout * hRadLay = new QHBoxLayout;
    hRadLay->setContentsMargins(0,0,0,0);
    hRadLay->setSpacing(DPI::getScaleUI(24));
    hRadLay->addWidget(lScreen);
    hRadLay->addWidget(hRadioBtn);
    hRadLay->addWidget(vRadioBtn);

    hRadLay->addStretch(1);

    //填充方式
    QLabel *lfill = new QLabel;
    lfill->setText(tr("Filling mode:"));
    lfill->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lfill->setFixedWidth(DPI::getScaleUI(100));

    comFill = new QComboBox;
    comFill->addItem(tr("Full"), fill_full);
    comFill->addItem(tr("Adjust"), fill_adjust);
    comFill->addItem(tr("Stretch"), fill_stretch);
    comFill->setMinimumWidth(DPI::getScaleUI(200));
    comFill->setCurrentIndex(1);
    proInf->fMode = fill_adjust;

    QHBoxLayout * fillLay = new QHBoxLayout;
    fillLay->setContentsMargins(0,0,0,0);
    fillLay->setSpacing(DPI::getScaleUI(5));

    fillLay->addWidget(lfill);
    fillLay->addWidget(comFill);
    fillLay->addStretch(1);

    //颜色
    QLabel *lColor = new QLabel;
    lColor->setText(tr("Color:"));
    lColor->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lColor->setFixedWidth(DPI::getScaleUI(100));

    fColor = new QColorFrame;
    QHBoxLayout * colorLay = new QHBoxLayout;
    colorLay->setContentsMargins(0,0,0,0);
    colorLay->setSpacing(5);

    proInf->color = Qt::white;

    colorLay->addWidget(lColor);
    colorLay->addWidget(fColor);
    colorLay->addStretch(1);

    /*
    //速度
    QLabel *lSpeedBar = new QLabel;
    lSpeedBar->setText(tr("Speed:"));
    lSpeedBar->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lSpeedBar->setFixedWidth(DPI::getScaleUI(100));

    speedBar = new QTabBar(this);
    speedBar->setObjectName("speedBar");
    speedBar->addTab(tr("Routine"));
    speedBar->addTab(tr("Automatic"));

    QHBoxLayout * speedbarLay = new QHBoxLayout;
    speedbarLay->setContentsMargins(0,0,0,0);
    speedbarLay->setSpacing(5);
    speedbarLay->addWidget(lSpeedBar);
    speedbarLay->addWidget(speedBar);

    //帧延时
    lSpeedTime = new QLabel;
    lSpeedTime->setText(tr("Frame delay(ms):"));
    lSpeedTime->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lSpeedTime->setFixedWidth(DPI::getScaleUI(100));

    timeSpinBox = new QSpinBox;
    timeSpinBox->setRange(20, 10000);
    timeSpinBox->setValue(40);
    proInf->delay = timeSpinBox->value();

    QHBoxLayout * timerLay = new QHBoxLayout;
    timerLay->setContentsMargins(0,0,0,0);
    timerLay->setSpacing(5);
    timerLay->addWidget(lSpeedTime);
    timerLay->addWidget(timeSpinBox);

    lSpeedSecond= new QLabel;
    lSpeedSecond->setText(tr("Frame count(p-s):"));
    lSpeedSecond->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lSpeedSecond->setFixedWidth(DPI::getScaleUI(100));
    lSpeedSecond->setVisible(false);

    secondSpinBox = new QSpinBox;
    secondSpinBox->setRange(1, 30);
    secondSpinBox->setVisible(false);
    secondSpinBox->setValue(25);

    QHBoxLayout * secondLay = new QHBoxLayout;
    secondLay->setContentsMargins(0,0,0,0);
    secondLay->setSpacing(5);
    secondLay->addWidget(lSpeedSecond);
    secondLay->addWidget(secondSpinBox);
    */
    //速度 帧延时
    QLabel *lSpeedBar = new QLabel;
    lSpeedBar->setText(tr("Speed:"));
    lSpeedBar->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lSpeedBar->setFixedWidth(DPI::getScaleUI(100));

    gDelayBtn = new QButtonGroup(this);
    gDelayBtn->setExclusive(true);
    speedTimeRadioBtn = new QRadioButton;
    speedTimeRadioBtn->setChecked(true);

    speedTimeRadioBtn->setText(tr("Frame delay(ms):"));
    gDelayBtn->addButton(speedTimeRadioBtn);

    speedSecondRadioBtn = new QRadioButton;
    speedSecondRadioBtn->setText(tr("Frame count(p-s):"));
    gDelayBtn->addButton(speedSecondRadioBtn);

    QHBoxLayout * hDelayLay = new QHBoxLayout;
    hDelayLay->setContentsMargins(0,0,0,0);
    hDelayLay->setSpacing(DPI::getScaleUI(24));
    hDelayLay->addWidget(lSpeedBar);
    hDelayLay->addWidget(speedTimeRadioBtn);
    hDelayLay->addWidget(speedSecondRadioBtn);

    hDelayLay->addStretch(1);

    //帧延时
    lSpeedTime = new QLabel;
    lSpeedTime->setText(tr("Frame delay(ms):"));
    lSpeedTime->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lSpeedTime->setFixedWidth(DPI::getScaleUI(100));

    timeSpinBox = new QSpinBox;
    timeSpinBox->setRange(20, 10000);
    timeSpinBox->setValue(40);
    timeSpinBox->setMinimumWidth(DPI::getScaleUI(200));
    proInf->delay = timeSpinBox->value();

    QHBoxLayout * timerLay = new QHBoxLayout;
    timerLay->setContentsMargins(0,0,0,0);
    timerLay->setSpacing(5);
    timerLay->addWidget(lSpeedTime);
    timerLay->addWidget(timeSpinBox);
    timerLay->addStretch(1);

    lSpeedSecond= new QLabel;
    lSpeedSecond->setText(tr("Frame count(p-s):"));
    lSpeedSecond->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lSpeedSecond->setFixedWidth(DPI::getScaleUI(100));
    lSpeedSecond->setVisible(false);

    secondSpinBox = new QSpinBox;
    secondSpinBox->setRange(1, 30);
    secondSpinBox->setVisible(false);
    secondSpinBox->setValue(25);
    secondSpinBox->setMinimumWidth(DPI::getScaleUI(200));

    QHBoxLayout * secondLay = new QHBoxLayout;
    secondLay->setContentsMargins(0,0,0,0);
    secondLay->setSpacing(5);
    secondLay->addWidget(lSpeedSecond);
    secondLay->addWidget(secondSpinBox);
    secondLay->addStretch(1);


    QVBoxLayout * lay = new QVBoxLayout;
    lay->setContentsMargins(DPI::getScaleUI(25),DPI::getScaleUI(25),DPI::getScaleUI(25),DPI::getScaleUI(25));
    lay->setSpacing(12);
    lay->addItem(sizeLay);
    lay->addItem(hRadLay);
    lay->addItem(fillLay);
    lay->addItem(colorLay);


    QFrame *fLineO = new QFrame;
    fLineO->setStyleSheet("border:1px solid rgba(10,10,10, 30);");
    fLineO->setFixedHeight(1);
    lay->addWidget(fLineO);

    lay->addItem(hDelayLay);
    lay->addItem(timerLay);
    lay->addItem(secondLay);

    QFrame *fLineT = new QFrame;
    fLineT->setStyleSheet("border:1px solid rgba(10,10,10, 30);");
    fLineT->setFixedHeight(1);
    lay->addWidget(fLineT);

    //顺序
    QLabel *lOrder = new QLabel;
    lOrder->setText(tr("Sequence:"));
    lOrder->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lOrder->setFixedWidth(DPI::getScaleUI(100));

    gOrderBtn = new QButtonGroup(this);
    gOrderBtn->setExclusive(true);
    orderRadioBtn = new QRadioButton;
    orderRadioBtn->setText(tr("Order"));
    orderRadioBtn->setChecked(true);

    proInf->oMode = order_compliant;
    gOrderBtn->addButton(orderRadioBtn);

    revRadioBtn = new QRadioButton;
    revRadioBtn->setChecked(false);
    revRadioBtn->setText(tr("Reverse"));
    gOrderBtn->addButton(revRadioBtn);

    QHBoxLayout * hOrderLay = new QHBoxLayout;
    hOrderLay->setContentsMargins(0,0,0,0);
    hOrderLay->setSpacing(DPI::getScaleUI(24));
    hOrderLay->addWidget(lOrder);
    hOrderLay->addWidget(orderRadioBtn);
    hOrderLay->addWidget(revRadioBtn);
    hOrderLay->addStretch(1);

    lay->addItem(hOrderLay);

    //质量
    QLabel *lQuality = new QLabel;
    lQuality->setText(tr("Quality:"));
    lQuality->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lQuality->setFixedWidth(DPI::getScaleUI(100));

    comQuality = new QComboBox;
    comQuality->addItem(tr("non-optimization"), quality_none);
    comQuality->addItem(tr("Automatic optimization"), quality_auto);
    comQuality->setMinimumWidth(DPI::getScaleUI(200));
    comQuality->setCurrentIndex(0);

    proInf->qMode = quality_none;

    QHBoxLayout * QualityLay = new QHBoxLayout;
    QualityLay->setContentsMargins(0,0,0,0);
    QualityLay->setSpacing(DPI::getScaleUI(5));

    QualityLay->addWidget(lQuality);
    QualityLay->addWidget(comQuality);
    QualityLay->addStretch(1);
    lay->addItem(QualityLay);

    lay->addStretch(DPI::getScaleUI(15));

    setLayout(lay);
}

void CommonPropertyView::refreashGifSize()
{
    QString strUUid = comSize->currentData().toString();

    sizeInf inf = GifSizeOp::getInstance()->getSizeInfBU(strUUid);
    gifSize = QSize(inf.width, inf.heigth);

    proInf->width = gifSize.width();
    proInf->heigth = gifSize.height();

    emit s_commproFresh();
}



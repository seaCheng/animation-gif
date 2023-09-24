#include "QTitleBar.h"
#include "ui_titleBar.h"

#include <QApplication>
#include <QScreen>
#include <QStyle>
#include <QToolBar>


frameBtn::frameBtn(QWidget *parent) : QFrame(parent)
{
   initial();
}

void frameBtn::onRetranslateUi()
{
    if(m_lTxt != nullptr)
    {
       //m_lTxt->setText(tr("Device Switch"));

       refreashText();

    }

}

void frameBtn::initial()
{
    setObjectName("frameBtn");

    m_layout = new QHBoxLayout(this);
    m_layout->setContentsMargins(0, 2, 0, 2);
    m_layout->setSpacing(8);

    m_lPic = new QLabel(this);
    m_lPic->setObjectName("PicLabel");
    m_lPic->setFixedSize(0,0);
    m_lPic->setScaledContents(true);
    m_lPic->setPixmap(QPixmap(":/icon/switch.png"));
    m_layout->addWidget(m_lPic);

    QFont font;
    font.setPointSize(12);
#if defined (_WIN32) || defined (WIN32)
    font.setFamily("Microsoft YaHei");
#else
    font.setFamily("PingFangSC-Regular");
#endif


    m_lTxt = new QLabel(this);
    m_lTxt->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    m_lTxt->setText(tr("Device Switch"));
    m_lTxt->setObjectName("TextLabel");
    m_lTxt->setFont(font);

    m_layout->addWidget(m_lTxt);

    refreashText();

    setStyleSheet("#frameBtn{ \
    background-color:transparent; \
    border-style:inset; \
    border-width:0px; \
    border-radius: 8px; \
    border-color:rgba(0,0,0,0); \
    color:rgb(255, 255, 255); \
} \
#frameBtn:hover{  \
color:rgb(255,255,255); \
background-color: #555; \
border-radius: 8px; \
} \
#frameBtn:pressed{ \
color:rgb(255,255,255); \
border-radius: 8px; \
background-color: #666; \
} \
#PicLabel,#TextLabel{ \
color: rgb(255, 255, 255);  \
background-color:transparent;\
} \
#PicLabel:disable,#TextLabel:disable{ \
color: rgb(255, 255, 255);  \
background-color:(255, 255, 255, 0.4);\
}");

}

void frameBtn::setText(QString strText)
{
    m_lTxt->setText(strText);
    refreashText();
}

void frameBtn::setEnableWid(bool bEn)
{
    if(bEn)
    {
        m_lPic->setPixmap(QPixmap(m_strPicNormal));

    }else
    {
        m_lPic->setPixmap(QPixmap(m_strPicDis));
    }
    setEnabled(bEn);
    update();
}

void frameBtn::mouseReleaseEvent(QMouseEvent *ev)
{
    emit s_click();
    QFrame::mouseReleaseEvent(ev);
}

void frameBtn::refreashText()
{
     QFontMetrics fontMetri(m_lTxt->font());
    if(m_lTxt->text().isEmpty() == false)
    {
        int iwidth = fontMetri.horizontalAdvance((m_lTxt->text()));
        iwidth = iwidth + 4 + 8;
        setFixedSize(iwidth, 32);
        m_lTxt->setVisible(true);

        m_layout->setContentsMargins(0, 0, 4, 0);
        m_layout->setSpacing(4);
    }else
    {
        setFixedSize(0, 0);
        m_lTxt->setVisible(false);
        m_layout->setContentsMargins(0, 0, 0, 0);
        m_layout->setSpacing(0);
    }
}

void frameBtn::setContext(QString strPicNormal, QString strPicDis, QString strText)
{
    m_strPicNormal = strPicNormal;
    m_strPicDis = strPicDis;

    m_lPic->setPixmap(QPixmap(m_strPicNormal));

    m_lTxt->setText(strText);

    refreashText();
    update();
}

//////////////////////////////////////////////////////////////////////////////////
QTitleBar::QTitleBar(QWidget * pWid)
:QWidget(pWid),
         ui(new Ui::titleWid)
{
         ui->setupUi(this);

         setObjectName("QTitleBar");

         onRetranslateUi();         

         #ifdef Q_OS_MAC
         ui->minimizeButton->setVisible(false);
         ui->maximizeButton->setVisible(false);
         ui->closeButton->setVisible(false);
         #endif

         #ifdef Q_OS_WIN32
         //ui->frameCtrl->layout()->removeItem(ui->horizontalSpacerctrl);
         #endif

         #ifdef Q_OS_WIN32
         //ui->frameCtrl->layout()->addItem(ui->horizontalSpacerctrl);
         ui->frameSystem->layout()->setContentsMargins(140,0,4,0);
         #endif

         #ifdef Q_OS_MAC
         ui->frameSystem->layout()->setContentsMargins(4,0,4,0);
         #endif

         setConnect();
}

void QTitleBar::addBtn(frameBtn * btn)
{
    #ifdef Q_OS_WIN32
    ui->frameCtrl->layout()->removeItem(ui->horizontalSpacer);
    ui->frameCtrl->layout()->addWidget(btn);
    ui->frameCtrl->layout()->addItem(ui->horizontalSpacer);
    #endif

    #ifdef Q_OS_MAC
    ui->frameCtrl->layout()->addWidget(btn);
    #endif

}

void QTitleBar::setConnect()
{
    connect(ui->minimizeButton, &QPushButton::clicked, this, [=]{
        emit s_min();
    });

    connect(ui->maximizeButton, &QPushButton::clicked, this, [=]{
        emit s_max();
    });

    connect(ui->closeButton, &QPushButton::clicked, this, [=]{
        emit s_close();
    });



}

void QTitleBar::setCtrlBtnText(btnCtrl_type btnType, QString str)
{
    switch (btnType) {

    case btn_switch:
    {

        break;
    }
    case btn_help:
    {

        break;
    }
    case btn_setting:
    {
        break;
    }
    case btn_login:
    {

        break;
    }
    case btn_user:
    {

        break;
    }
    default:
    {
        break;
    }

    }
}

void QTitleBar::setSysMaxBtnMax(bool bMax)
{
    if(bMax)
    {
       ui->maximizeButton->setProperty("max", "true");
    }else
    {
       ui->maximizeButton->setProperty("max", "false");
    }

    style()->unpolish(ui->maximizeButton);
    style()->polish(ui->maximizeButton);
}

void QTitleBar::setCtrlBtnEnable(btnCtrl_type btnType, bool bEnable)
{
    switch (btnType) {

    case btn_switch:
    {
        //m_switchBtn->setEnabled(bEnable);
        break;
    }
    case btn_help:
    {
        //m_helpBtn->setEnabled(bEnable);
        break;
    }
    case btn_setting:
    {
        //m_settingBtn->setEnabled(bEnable);
        break;
    }
    case btn_login:
    {
        //m_loginBtn->setEnabled(bEnable);
        break;
    }
    case btn_user:
    {
        //m_UserTop->setEnabled(bEnable);
        break;
    }
    default:
    {
        break;
    }

    }
}

void QTitleBar::setCtrlBtnVisable(btnCtrl_type btnType, bool bShow)
{

    switch (btnType) {

    case btn_switch:
    {
        //m_switchBtn->setVisible(bShow);
        break;
    }
    case btn_help:
    {
        //m_helpBtn->setVisible(bShow);
        break;
    }
    case btn_setting:
    {
        //m_settingBtn->setVisible(bShow);
        break;
    }
    case btn_login:
    {
        //m_loginBtn->setVisible(bShow);
        break;
    }
    case btn_user:
    {
        //m_UserTop->setVisible(bShow);
        break;
    }
    default:
    {
        break;
    }

    }
}

void QTitleBar::onRetranslateUi()
{
    ui->retranslateUi(this);
    m_sreLog = tr("Log In");

    m_switch = tr("Device Switch");
    m_setting = tr("Settings");
    m_help = tr("Help");

    if(m_switchBtn)
    {
        //m_switchBtn->setToolTip(m_switch);
    }

    if(m_helpBtn)
    {
        //m_helpBtn->setToolTip(m_help);
    }

    if(m_settingBtn)
    {
        //m_settingBtn->setToolTip(m_setting);
    }

    if(m_loginBtn)
    {
        //m_loginBtn->setContext(":/icon/user.png", ":/icon/userDis.png", m_sreLog);
    }


}

void QTitleBar::addToolButton(QToolBar* toolBar)
{
    ui->frameCtrl->layout()->addWidget(toolBar);
}

QFrame * QTitleBar::getframeCtrl()
{
    return ui->frameCtrl;
}

QFrame * QTitleBar::getframeSystem()
{
    return ui->frameSystem;
}

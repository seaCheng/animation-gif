#include "QTitleBar.h"
#include "ui_titleBar.h"

#include <QApplication>
#include <QScreen>
#include <QStyle>
#include <QToolBar>


QTitleBar::QTitleBar(QWidget * pWid)
:QWidget(pWid),
         ui(new Ui::titleWid)
{
         ui->setupUi(this);

         setObjectName("QTitleBar");

         onRetranslateUi();

         /*
         ui->frameSystem->layout()->removeWidget(ui->btnUserTop);
         ui->frameSystem->layout()->removeItem(ui->horizontalSpacer);
         ui->frameSystem->layout()->removeWidget(ui->minimizeButton);
         ui->frameSystem->layout()->removeWidget(ui->maximizeButton);
         ui->frameSystem->layout()->removeWidget(ui->closeButton);

         m_switchBtn = new frameBtn(this);
         m_switchBtn->setContext(":/icon/switch.png", ":/icon/switchDisable.png", "Device switch");
         ui->frameSystem->layout()->addWidget(m_switchBtn);

         m_helpBtn = new frameBtn(this);
         m_helpBtn->setContext(":/icon/help.png", ":/icon/helpDis.png", "Help");
         ui->frameSystem->layout()->addWidget(m_helpBtn);

         m_settingBtn = new frameBtn(this);
         m_settingBtn->setContext(":/icon/setting.png", ":/icon/settingDis.png", "Setting");
         ui->frameSystem->layout()->addWidget(m_settingBtn);

         m_loginBtn = new frameBtn(this);
         m_loginBtn->setContext(":/icon/user.png", ":/icon/userDis.png", "Login");
         ui->frameSystem->layout()->addWidget(m_loginBtn);


         ui->frameSystem->layout()->addWidget(ui->btnUserTop);
         ui->frameSystem->layout()->addItem(ui->horizontalSpacer);
         ui->frameSystem->layout()->addWidget(ui->minimizeButton);
         ui->frameSystem->layout()->addWidget(ui->maximizeButton);
         ui->frameSystem->layout()->addWidget(ui->closeButton);
         */

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

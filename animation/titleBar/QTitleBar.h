#ifndef QTITLEBAR_H
#define QTITLEBAR_H

#include <QWidget>

#include "framelesswindow.h"

namespace Ui {
class titleWid;
}

class frameBtn;
class QFrame;

enum btnCtrl_type{btn_switch = 0, btn_help, btn_setting, btn_login, btn_user, btn_product};
enum btnSys_type{btn_sys_min = 0, btn_sys_max, btn_sys_close};
Q_DECLARE_METATYPE(btnCtrl_type)

class QToolBar;
class QTitleBar :public QWidget
{
    Q_OBJECT
public:
    QTitleBar(QWidget * pWid);
    void setConnect();

    QFrame * getframeCtrl();
    QFrame * getframeSystem();

    void addToolButton(QToolBar* toolBar);

    void setCtrlBtnVisable(btnCtrl_type btnType, bool bShow);
    void setCtrlBtnEnable(btnCtrl_type btnType, bool bShow);
    void setCtrlBtnText(btnCtrl_type btnType, QString);

    //设置最大化安装最大化
    void setSysMaxBtnMax(bool bMax);

    void onRetranslateUi();
signals:
    void s_min();
    void s_max();
    void s_close();
    void s_clicked(btnCtrl_type type);
private:
    Ui::titleWid *ui;

    frameBtn * m_switchBtn = nullptr;
    frameBtn * m_helpBtn = nullptr;
    frameBtn * m_settingBtn = nullptr;
    frameBtn * m_loginBtn = nullptr;
    frameBtn * m_UserTop = nullptr;

    QString m_sreLog;
    QString m_switch;
    QString m_setting;
    QString m_help;

};

#endif // QTITLEBAR_H

#include "tabbarpri.h"

#include "QLabel"
#include "QVBoxLayout"

tabBtn::tabBtn(QWidget *parent)
    :QFrame(parent)
{
    initial();
}

void tabBtn::setText(QString sText)
{
   strText = sText;
   label->setText(strText);
}

void tabBtn::initial()
{
    label = new QLabel();
    label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    frame = new QFrame();
    frame->setFixedHeight(4);
    frame->setStyleSheet("border:2px solid rgba(10,10,10, 30);");

    QVBoxLayout * lay = new QVBoxLayout(this);
    lay->setContentsMargins(2,2,2,2);
    lay->addWidget(label);
    lay->addWidget(frame);
}

void tabBtn::mousePressEvent(QMouseEvent *event)
{
    emit sigChecked();
}

void tabBtn::enterEvent(QEnterEvent *event)
{
    if(!bCheck)
    {
        checkStatus = tabStatus_hover;
        refreashStyle();
    }

}

void tabBtn::leaveEvent(QEvent *event)
{
    if(!bCheck)
    {
        checkStatus = tabStatus_normal;
        refreashStyle();
    }

}

void tabBtn::refreashStyle()
{
    switch (checkStatus) {
    case tabStatus_normal:
    {
        frame->setStyleSheet("border:2px solid rgba(10,10,10, 30);");
        frame->setVisible(false);
        break;
    }
    case tabStatus_hover:
    {
        frame->setStyleSheet("border:2px solid rgba(10,10,10, 50);");
        frame->setVisible(true);
        break;
    }
    case tabStatus_checked:
    {
        frame->setStyleSheet("border:2px solid rgba(10,10,10, 80);");
        frame->setVisible(true);
        break;
    }
    default:
        break;
    }
}

//////////////////////////////////////////////////////
TabBarPri::TabBarPri(QWidget *parent)
    : QFrame(parent)
{
     lay = new QHBoxLayout(this);
     lay->setContentsMargins(2,2,2,2);
     lay->setSpacing(2);
}

void TabBarPri::addTab(QString sText, tabStatus status)
{
    tabBtn * pBtn = new tabBtn;
    pBtn->setText(sText);
    pBtn->setStatus(status);
    pBtn->setFixedHeight(iheight);
    pBtn->setFixedWidth(iWidth);

    connect(pBtn, &tabBtn::sigChecked, this , [&](){

        int i = 0;
        for(auto u : lstTab)
        {
            if(u == (tabBtn *)sender())
            {
                u->setChecked(true);
                u->setStatus(tabStatus_checked);
                emit sigCheckedChange(i);
            }else
            {
                u->setChecked(false);
                u->setStatus(tabStatus_normal);
            }
            i++;
        }
    });

    lay->addWidget(pBtn);

    lstTab.push_back(pBtn);

    setFixedWidth(iWidth * lstTab.size() + (lstTab.size() - 1) * 2);
}

void TabBarPri::setCurrentIndex(int iIndex)
{
    if(iIndex < 0 | iIndex > lstTab.size() - 1)
    {
        return;
    }

    int i = 0;
    for(auto u : lstTab)
    {
        if(i == iIndex)
        {
            u->setChecked(true);
            u->setStatus(tabStatus_checked);
            emit sigCheckedChange(i);
        }else
        {
            u->setChecked(false);
            u->setStatus(tabStatus_normal);
        }
        i++;
    }
}

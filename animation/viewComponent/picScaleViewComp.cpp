#include "picScaleViewComp.h"

#include <QHBoxLayout>
#include<QRandomGenerator>
#include <QStyle>
#include <QVariant>
#include <QDebug>

#include "picScaleComp.h"
#include "connectableitem.h"

PicScaleViewComp::PicScaleViewComp(QWidget *parent)
    :QFrame(parent)
{
    initial();
    setConnect();
}

void PicScaleViewComp::setConnect()
{
    //connect()
}

void PicScaleViewComp::refreashState()
{
    if(m_picScaleCli != nullptr)
    {
        QString state = "false";
        m_picScaleCli->setProperty("sel", state);
        style()->unpolish(m_picScaleCli);
        style()->polish(m_picScaleCli);
    }

    PicScaleComp * picScaleCli = (PicScaleComp *)sender();
    m_picScaleCli = picScaleCli;
    QString state = "true";
    picScaleCli->setProperty("sel", state);
    style()->unpolish(picScaleCli);
    style()->polish(picScaleCli);

    //qDebug()<<"refreashState";
}

void PicScaleViewComp::eraseItem(ModelView::SessionItem * item, ModelView::TagRow row)
{
    auto it = m_itemToView.find((ConnectableItem *) item);
    if (it != m_itemToView.end()) {
        m_layout->removeWidget(m_itemToView[(ConnectableItem *) item]);
        delete it->second;
        m_itemToView.erase(it);
    }
}

void PicScaleViewComp::insertItem(ModelView::SessionItem * item, ModelView::TagRow row)
{
    ConnectableItem * pItem = (ConnectableItem *)item;
    PicScaleComp * picScale = new PicScaleComp((ConnectableItem *)item);
    connect(picScale, &PicScaleComp::s_clicked, this, &PicScaleViewComp::refreashState);
    picScale->setFixedSize(180,180);
    picScale->setPicIndexInterval(QString("%1").arg(row.row), QString("%1ms").arg(600));
    m_layout->insertWidget(row.row, picScale);

    m_itemToView[pItem] = picScale;
}

void PicScaleViewComp::initial()
{
    setObjectName("PicScaleViewComp");
    m_layout = new QHBoxLayout(this);
    m_layout->setContentsMargins(0,0,0,0);
    m_layout->setSpacing(0);

    /*
    for(int i = 0; i < 1000; i++)
    {
        PicScaleComp * picScale = new PicScaleComp();
        connect(picScale, &PicScaleComp::s_clicked, this, &PicScaleViewComp::refreashState);
        picScale->setFixedSize(180,180);
        picScale->setPicIndexInterval(QString("%1").arg(i), QString("%1ms").arg(600));

        int iIndex = QRandomGenerator::global()->bounded(11) + 1;
        picScale->setPic(QPixmap(QString(":/images/%1.bmp").arg(iIndex)));
        m_layout->addWidget(picScale);
        //m_layout->insertWidget(1 + m_layout->count() ,picScale);
    }

    QLayoutItem *child;
     while ((child = m_layout->takeAt(0)) != nullptr)
     {
         delete child->widget(); // delete the widget
         delete child;   // delete the layout item
         break;
     }
     */

    //takeAt
    m_layout->addStretch();

}


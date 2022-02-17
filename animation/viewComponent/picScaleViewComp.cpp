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
}

PicScaleComp * PicScaleViewComp::getSelItem()
{
    return m_picScaleCli;
}

void PicScaleViewComp::refreashIndex()
{
    for(auto it: m_itemToView)
    {
        it.second->setPicIndexInterval(QString("%1").arg(it.first->tagRow().row), QString("%1ms").arg(600));
    }
}

void PicScaleViewComp::eraseItem(ModelView::SessionItem * item, ModelView::TagRow row)
{

    auto it = m_itemToView.find((ConnectableItem *) item);
    if (it != m_itemToView.end()) {
        m_layout->removeWidget(m_itemToView[(ConnectableItem *) item]);

        if(m_picScaleCli == it->second)
        {
            m_picScaleCli = nullptr;
        }

        delete it->second;
        m_itemToView.erase(it);

        refreashIndex();
    }
}

void PicScaleViewComp::insertItem(ModelView::SessionItem * item, ModelView::TagRow row)
{
    ConnectableItem * pItem = (ConnectableItem *)item;
    PicScaleComp * picScale = new PicScaleComp((ConnectableItem *)item);
    connect(picScale, &PicScaleComp::s_clicked, this, &PicScaleViewComp::refreashState);
    picScale->setFixedSize(180,180);
    picScale->setPicIndexInterval(QString("%1").arg(row.row), QString("%1ms").arg(600));
    picScale->setPic(pItem->pic());
    m_layout->insertWidget(row.row, picScale);

    m_itemToView[pItem] = picScale;

    if(row.row != m_itemToView.size() - 1)
    {
        refreashIndex();
    }

}

void PicScaleViewComp::initial()
{
    setObjectName("PicScaleViewComp");
    m_layout = new QHBoxLayout(this);
    m_layout->setContentsMargins(0,0,0,0);
    m_layout->setSpacing(0);

    m_layout->addStretch();

}


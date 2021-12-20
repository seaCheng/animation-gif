#include "picScaleViewComp.h"

#include <QHBoxLayout>
#include<QRandomGenerator>

#include "picScaleComp.h"

PicScaleViewComp::PicScaleViewComp(QWidget *parent)
    :QWidget(parent)
{
    initial();
}

void PicScaleViewComp::initial()
{
    m_layout = new QHBoxLayout(this);
    m_layout->setContentsMargins(0,0,0,0);
    m_layout->setSpacing(0);

    for(int i = 0; i < 1000; i++)
    {
        PicScaleComp * picScale = new PicScaleComp();
        picScale->setFixedSize(180,180);
        picScale->setPicIndexInterval(QString("%1").arg(i), QString("%1ms").arg(600));

        int iIndex = QRandomGenerator::global()->bounded(8) + 1;
        picScale->setPic(QPixmap(QString(":/images/%1.bmp").arg(iIndex)));
        m_layout->addWidget(picScale);
    }

    m_layout->addStretch();


}

void PicScaleViewComp::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
}

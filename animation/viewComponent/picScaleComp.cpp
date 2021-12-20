#include "picScaleComp.h"
#include <QLabel>
#include <QHBoxLayout>

#include "aspectRatioPixmapLabel.h"

PicScaleComp::PicScaleComp(QWidget *parent)
    :QFrame(parent)
{
   initial();
}

void PicScaleComp::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);
}

void PicScaleComp::setPicIndexInterval(QString index, QString interval)
{
    m_labelLeft->setText(index);
    m_labelRight->setText(interval);
}

void PicScaleComp::setPic(QPixmap pic)
{
    m_lPic->setPixmapLabel(pic);
}

void PicScaleComp::initial()
{
    m_frameBottom = new QFrame();
    m_frameBottom->setFrameShape(NoFrame);
    m_frameBottom->setLineWidth(0);
    m_frameBottom->setFixedHeight(40);

    m_layout = new QVBoxLayout(this);
    m_layout->setContentsMargins(12,12,12,5);
    m_layout->setSpacing(0);

    m_labelLeft = new QLabel();
    m_labelLeft->setAlignment(Qt::AlignCenter);
    m_labelLeft->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    m_labelRight = new QLabel();
    m_labelRight->setAlignment(Qt::AlignCenter);
    m_labelRight->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    QHBoxLayout * layout = new QHBoxLayout();
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    m_frameBottom->setLayout(layout);

    layout->addWidget(m_labelLeft);
    layout->addWidget(m_labelRight);

    m_lPic = new AspectRatioPixmapLabel();
    m_lPic->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_layout->addWidget(m_lPic);
    m_layout->addWidget(m_frameBottom);
}

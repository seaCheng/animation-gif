#include "picScaleComp.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QMenu>

#include "aspectRatioPixmapLabel.h"
#include "pictureItem.h"
#include "pictureItemcontroller.h"
#include "dpi.h"

PicScaleComp::PicScaleComp(QMenu * menu,PictureItem* item, QWidget *parent)
    :QFrame(parent),
      m_item(item),
      m_controller(std::make_unique<PictureItemController>(item, this)),
      myContextMenu(menu)
{
   initial();
}

void PicScaleComp::mouseReleaseEvent(QMouseEvent *ev)
{
    QFrame::mouseReleaseEvent(ev);

    emit s_clicked();
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
    setObjectName("PicScaleComp");
    m_frameBottom = new QFrame();
    m_frameBottom->setFrameShape(NoFrame);
    m_frameBottom->setLineWidth(0);
    m_frameBottom->setFixedHeight(DPI::getScaleUI(40));

    m_layout = new QVBoxLayout(this);
    m_layout->setContentsMargins(DPI::getScaleUI(12),DPI::getScaleUI(12),DPI::getScaleUI(12),DPI::getScaleUI(5));
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

PictureItem* PicScaleComp::getPictureItem()
{
    return m_item;
}

void PicScaleComp::contextMenuEvent(QContextMenuEvent *event)
{
    emit s_clicked();
    myContextMenu->exec(event->globalPos());
}

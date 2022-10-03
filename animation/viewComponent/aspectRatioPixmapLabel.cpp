#include "aspectRatioPixmapLabel.h"
#include<QPainter>
#include<QDebug>

AspectRatioPixmapLabel::AspectRatioPixmapLabel(QWidget *parent) 
    : QLabel(parent)
{

    //setStyleSheet("font-family: MicrosoftYaHeiUI;font-size: 14px;color:#028EC0;letter-spacing: 0;line-height: 20px;");
    setScaledContents(false);
}

void AspectRatioPixmapLabel::paintEvent(QPaintEvent *env)
{
    //让图片按照Qlabel的大小进行缩放，保持宽高比。
    if (!m_pix.isNull())
    {
        QPainter painter(this);
        painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);

        m_pix = m_pix.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);


        QRect rectPic(0, 0, m_pix.size().width(), m_pix.size().height());
        if (m_pix.width() < this->width())
        {
            rectPic.setX((this->width() - m_pix.width()) / 2);
            rectPic.setY(0);
            rectPic.setWidth(m_pix.size().width());
            rectPic.setHeight(m_pix.size().height());
        }

        if (m_pix.height() < this->height())
        {
            rectPic.setX(0); rectPic.setY((this->height() - m_pix.height()) / 2);
            rectPic.setWidth(m_pix.size().width());
            rectPic.setHeight(m_pix.size().height());
        }

        painter.drawImage(rectPic, m_pix.toImage());
    }

}

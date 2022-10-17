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
    if(!isVisible())
    {
        return;
    }

    //让图片按照Qlabel的大小进行缩放，保持宽高比。
    if (!m_pix.isNull())
    {
        QPainter painter(this);
        painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
        QPixmap pi;
        pi = m_pix.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);


        QRect rectPic(0, 0, pi.size().width(), pi.size().height());
        if (pi.width() < this->width())
        {
            rectPic.setX((this->width() - pi.width()) / 2);
            rectPic.setY(0);
            rectPic.setWidth(pi.size().width());
            rectPic.setHeight(pi.size().height());
        }

        if (pi.height() < this->height())
        {
            rectPic.setX(0); rectPic.setY((this->height() - pi.height()) / 2);
            rectPic.setWidth(pi.size().width());
            rectPic.setHeight(pi.size().height());
        }

        painter.drawImage(rectPic, pi.toImage());
    }

}

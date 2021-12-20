#include "aspectRatioPixmapLabel.h"
#include<QPainter> 

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
        QSize labelsize = this->size();
        m_pix = m_pix.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QSize pixsize = m_pix.size(); //根据图片的宽高和QLabel的宽高计算绘图的矩形区域和坐标
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
        QSize pimageszie = m_pix.toImage().size();
        painter.drawImage(rectPic, m_pix.toImage());
    }

}

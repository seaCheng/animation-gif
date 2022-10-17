#ifndef ASPECTRATIOPIXMAPLABEL_H 
#define ASPECTRATIOPIXMAPLABEL_H 
#include <QLabel> 
#include<QPaintEvent> 

class AspectRatioPixmapLabel : public QLabel 
{ 
    Q_OBJECT
public: AspectRatioPixmapLabel(QWidget *parent = 0);
    void setPixmapLabel(QPixmap pixmap)//设置图片路径
    {
        m_pix = pixmap;//创建Pixmap对象
        update();//这里需要刷新下，触发重绘，paintEvent会去画图片，否则不触发重绘，不会花图片，QLabel大小变化时，也会触发重绘，自动去按Qlabel尺寸重绘图片
    }
    //void setScalPixmap(const QPixmap p);//设置变化的
protected:
    void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;//重写重绘函数

private:
    QPixmap m_pix;//保存图片Pixmap
    QString m_strPath = "";//保存图片路径
};
#endif // ASPECTRATIOPIXMAPLABEL_H

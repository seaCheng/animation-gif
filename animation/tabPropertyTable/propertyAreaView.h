#pragma once
#include <QLabel> 
#include<QPaintEvent>
#include <QTabWidget>

class CommonPropertyView;
class PropertyAreaView : public QTabWidget
{ 
    Q_OBJECT
public:
    PropertyAreaView(QWidget *parent = 0);
    void setConnect();

    void initial();

    //对外提供接口
public:
    QSize getGifSize();
signals:
    void s_sizeFresh(QSize);

protected:
    void paintEvent(QPaintEvent *e) override;
public slots:
    //void slot_selPicItem(PictureItem *);
protected:
    //void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;//重写重绘函数
private:
    CommonPropertyView * commView;

};

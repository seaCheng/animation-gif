#pragma once
#include <QLabel> 
#include<QPaintEvent>
#include <QTabWidget>

class CommonPropertyView;
enum screenMode{screen_horizal,screen_vertical};
Q_DECLARE_METATYPE(screenMode)

enum fillMode{fill_full,fill_adjust,fill_stretch};
Q_DECLARE_METATYPE(fillMode)

struct propertyInf
{
    int width = 360;
    int heigth = 240;
    screenMode scMode = screen_horizal;
    fillMode fMode = fill_adjust;
    QColor color = Qt::white;
};
Q_DECLARE_METATYPE(propertyInf)

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

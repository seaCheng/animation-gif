#pragma once
#include <QLabel> 
#include<QPaintEvent>
#include <QTabWidget>

class CommonPropertyView;
enum screenMode{screen_horizal,screen_vertical};
Q_DECLARE_METATYPE(screenMode)

enum fillMode{fill_full,fill_adjust,fill_stretch};
Q_DECLARE_METATYPE(fillMode)

enum orderMode{order_compliant,order_reverse};
Q_DECLARE_METATYPE(orderMode)

enum qualityMode{quality_none,quality_auto};
Q_DECLARE_METATYPE(qualityMode)

struct propertyInf
{
    int width = 360;
    int heigth = 240;
    screenMode scMode = screen_horizal;
    fillMode fMode = fill_adjust;
    QColor color = Qt::white;
    int delay = 20; //ms
    orderMode oMode = order_compliant;
    qualityMode qMode = quality_none;
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

    std::shared_ptr<propertyInf> getGifCommpro()
    {
        return proInf;
    }


signals:
    void s_commproFresh();
protected:
    void paintEvent(QPaintEvent *e) override;
public slots:
    //void slot_selPicItem(PictureItem *);
protected:
    //void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;//重写重绘函数
private:
    CommonPropertyView * commView;
    std::shared_ptr<propertyInf> proInf;

};

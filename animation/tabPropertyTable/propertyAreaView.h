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
signals:
    //void s_clicked(type_import eType);

protected:
    void paintEvent(QPaintEvent *e) override;
public slots:
    //void slot_selPicItem(PictureItem *);
protected:
    //void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;//重写重绘函数
private:
    CommonPropertyView * commView;

};

#pragma once
#include <QLabel> 
#include<QPaintEvent>
#include <QStackedWidget>

#include "emptyAreaView.h"
#include "graphicsViewComp.h"

class GraphicsViewComp;
class PictureItem;

class MainAreaView : public QStackedWidget
{ 
    Q_OBJECT
public:
    MainAreaView(QWidget *parent = 0);
    void setConnect();

    void setGifSize(const QSize & size);
signals:
    void s_clicked(type_import eType);

public slots:
    void slot_selPicItem(PictureItem *);
protected:
    //void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;//重写重绘函数
private:
    EmptyAreaView * emptyView = nullptr;
    GraphicsViewComp * graphicView = nullptr;
    PicGraphicsScene * pScene;
    QFrame * graWid = nullptr;
};

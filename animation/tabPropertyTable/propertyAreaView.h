#pragma once
#include <QLabel> 
#include<QPaintEvent>
#include <QTabWidget>

#include "commonPropertyView.h"
#include "WhiteBoardPropertyView.h"

class CommonPropertyView;
class WhiteBoardPropertyView;


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
        return commproInf;
    }

    std::shared_ptr<whiteBoardProInf> getWhiteBoardInf()
    {
        return whBoardProInf;
    }


signals:
    void s_whiteBoardProFresh();
    void s_commproFresh();
    void s_sceneItemInsert(DiagramType);

    void s_saveToCurrentPicture();
    void s_saveToAllPictures();
    void s_clearGraphicsItems();
protected:
    void paintEvent(QPaintEvent *e) override;
public slots:
    //void slot_selPicItem(PictureItem *);
protected:
    //void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;//重写重绘函数
private:
    CommonPropertyView * commView;
    WhiteBoardPropertyView * whiteBoardView;
    std::shared_ptr<propertyInf> commproInf;

    std::shared_ptr<whiteBoardProInf> whBoardProInf;

};

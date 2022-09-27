#pragma once
#include <QLabel> 
#include<QPaintEvent>
#include <QStackedWidget>

#include "emptyAreaView.h"
#include "graphicsViewComp.h"
#include "qdialog.h"

class GraphicsViewComp;
class PictureItem;
class ScaleButtonView;

class GraphicFrame :public QFrame
{
    Q_OBJECT
public:
    GraphicFrame(QWidget *parent = 0);
    void setConnect();

signals:
    void s_scaleFreash(qreal);

public slots:

protected:
    void showEvent(QShowEvent *event) override;
    void resizeEvent(QResizeEvent *) override;
private:
    ScaleButtonView * scaleView = nullptr;
};

class MainAreaView : public QStackedWidget
{ 
    Q_OBJECT
public:
    MainAreaView(QWidget *parent = 0);
    void setConnect();

    void setGifCommpro(std::shared_ptr<propertyInf> inf);
    void setWhiteBoardPro(std::shared_ptr<whiteBoardProInf> inf);
    void start_insertSceneItem(DiagramType type);

    void createActions();

    void saveToCurrentPictire();

    void clearsSceneItems();
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
    GraphicFrame * graWid = nullptr;
    PictureItem * currentItem = nullptr;

    QMenu *itemMenu;
    QAction *deleteAction;
    QAction *toFrontAction;
    QAction *sendBackAction;
    QAction *resetRotaAction;
};

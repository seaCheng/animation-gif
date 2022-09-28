#pragma once
#include <QGraphicsView>
#include <QGraphicsScene>

#include <memory>

#include <QObject>
#include <QOpenGLWidget>

#include <QImage>

#include "propertyAreaView.h"
#include "whiteBoardPropertyView.h"

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
class QMenu;
class QPointF;
class QGraphicsLineItem;
class QFont;
class QGraphicsTextItem;
class QColor;
QT_END_NAMESPACE

class PictureItem;
class PicGraphicsScene;
class DiagramItem;
class DiagramTextItem;

class SGraffiti;

class GraphicsViewComp :public QGraphicsView
{
    Q_OBJECT
public:

    GraphicsViewComp(QGraphicsScene *scene, QWidget *parent = nullptr);
    void setPicItem(PictureItem * pItem);

    void setGifCommpro(std::shared_ptr<propertyInf> inf);
    void refreashSize();
protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:

    std::shared_ptr<propertyInf> proInf;
    PictureItem * pPicItem = nullptr;
    PicGraphicsScene * pScene = nullptr;
};

enum InsertMode { InsertItem, InsertLine, InsertText,InsertDrawLine, InsertPic,MoveItem,DeleteItem };
Q_DECLARE_METATYPE(InsertMode);

class PicGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:


    PicGraphicsScene(QMenu * menu, QWidget * p);
    void setPicItem(PictureItem * pItem);

    void setMode(InsertMode mode);

    void setItemType(DiagramType type);

    void setGifCommpro(std::shared_ptr<propertyInf> inf);
    void setWhiteBoardPro(std::shared_ptr<whiteBoardProInf> inf, refreashProType proType);

signals:
    void itemInserted(DiagramItem *item);
    void textInserted(QGraphicsTextItem *item);
    void itemSelected(QGraphicsItem *item);

    void s_modeRef(InsertMode);

public slots:
    void editorLostFocus(DiagramTextItem *item);

protected:
    void drawBackground(QPainter *painter, const QRectF &rect) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
private:
    PictureItem * mpItem = nullptr;

    QPixmap pic;
    std::shared_ptr<propertyInf> proInf;
    std::shared_ptr<whiteBoardProInf> whiteBoardInf;
    InsertMode iMode = MoveItem;
    DiagramType dType = Diagram_Conditional;

    QMenu *myItemMenu;

    bool leftButtonDown;
    QPointF startPoint;
    QGraphicsLineItem *line = nullptr;

    SGraffiti *m_currentShape = nullptr;

    DiagramItem *item = nullptr;
    QFont myFont;
    DiagramTextItem *textItem = nullptr;
    QColor myTextColor;
    QColor myItemColor;
    QColor myLineColor;

};

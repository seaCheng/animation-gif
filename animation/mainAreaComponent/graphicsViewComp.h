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

};


class PicGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:

    enum InsertMode { InsertItem, InsertLine, InsertText, MoveItem };
    PicGraphicsScene(QWidget * p);
    void setPicItem(PictureItem * pItem);

    void setMode(InsertMode mode);

    void setItemType(DiagramType type);

    void setGifCommpro(std::shared_ptr<propertyInf> inf);

signals:
    void itemInserted(DiagramItem *item);
    void textInserted(QGraphicsTextItem *item);
    void itemSelected(QGraphicsItem *item);

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
    InsertMode iMode = InsertItem;
    DiagramType dType = Diagram_Conditional;

    QMenu *myItemMenu;

    bool leftButtonDown;
    QPointF startPoint;
    QGraphicsLineItem *line;
    QFont myFont;
    DiagramTextItem *textItem;
    QColor myTextColor;
    QColor myItemColor;
    QColor myLineColor;

};

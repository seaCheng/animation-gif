
#ifndef DIAGRAMITEM_H
#define DIAGRAMITEM_H

#include <QGraphicsPixmapItem>
#include <QList>

#include "whiteBoardPropertyView.h"

#include "uiCanvasItemBase.h"

QT_BEGIN_NAMESPACE
class QPixmap;
class QGraphicsSceneContextMenuEvent;
class QMenu;
class QPolygonF;
QT_END_NAMESPACE

class Arrow;

//! [0]
class DiagramItem : public UICanvasItemBase
{
public:
    enum { Type = UserType + 15 };
    //enum DiagramType { Step, Conditional, StartEnd, Io };

    DiagramItem(DiagramType diagramType, QMenu *contextMenu, QGraphicsItem *parent = nullptr);

    void removeArrow(Arrow *arrow);
    void removeArrows();
    DiagramType diagramType() const { return myDiagramType; }
    QPolygonF polygon() const { return myPolygon; }
    void addArrow(Arrow *arrow);
    QPixmap image() const;
    int type() const override { return Type; }

protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    virtual QRectF getCustomRect(void) const override;
    virtual void sizeRefreash() override;
    // 自定义元素绘制
    virtual void customPaint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    DiagramType myDiagramType;
    QPolygonF myPolygon;
    QMenu *myContextMenu;
    QList<Arrow *> arrows;

    QPainterPath path;
};
//! [0]

#endif // DIAGRAMITEM_H

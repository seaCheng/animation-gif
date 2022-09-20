
#ifndef DIAGRAMITEM_H
#define DIAGRAMITEM_H

#include <QGraphicsPixmapItem>
#include <QList>
#include <QPen>

#include "whiteBoardPropertyView.h"

#include "uiCanvasItemBase.h"

QT_BEGIN_NAMESPACE
class QPixmap;
class QGraphicsSceneContextMenuEvent;
class QMenu;
class QPolygonF;
QT_END_NAMESPACE

class Arrow;

enum ToolType {
    tt_Line = 1,
    tt_Graffiti,
    tt_Rectangle,
    tt_Oval,
    tt_Triangle
};

class Shape : public UICanvasItemBase
{
public:
    Shape(QMenu * menu,int type):UICanvasItemBase(menu), m_type(type)
      , m_strokeWidth(1.0f)
      , m_strokeColor(Qt::black)
      , m_fillColor(Qt::transparent)
      , m_creatorId(-1), m_globalId(-1)
      , m_localId(generateLocalId())
    {}

    virtual ~Shape(){}

    virtual void setStartPoint(const QPointF &pos) = 0;
    virtual void setEndPoint(const QPointF &pos) = 0;
    virtual void setStrokeWidth(float w) { m_strokeWidth = w; }
    virtual void setStrokeColor(const QColor &clr){ m_strokeColor = clr; }
    virtual void setFillColor(const QColor &clr){ m_fillColor = clr; }
    virtual bool isValid(){ return true; }
    virtual void serialize(QJsonObject &obj) = 0;

    static int generateLocalId();

    void setCreator(int id){ m_creatorId = id;}
    int creator(){ return m_creatorId; }
    void setGlobalId(int id) { m_globalId = id; }
    int globalId(){ return m_globalId; }
    void setLocalId(int id){ m_localId = id; }
    int localId(){ return m_localId; }

protected:
    int m_type;
    float m_strokeWidth;
    QColor m_strokeColor;
    QColor m_fillColor;
    static int m_idBase;
    int m_creatorId;
    int m_globalId;
    int m_localId;
};

class SGraffiti : public Shape
{
public:

    enum { Type = UserType + 5 };
    SGraffiti(QMenu * menu);

    QRectF getCustomRect() const override;
    //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    // 自定义元素绘制
    virtual void customPaint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void setStartPoint(const QPointF &pos) override;
    void setEndPoint(const QPointF &pos) override;
    void setStrokeWidth(float w) override;
    void setStrokeColor(const QColor &clr) override;
    bool isValid() override;
    void serialize(QJsonObject &obj) override;
    void setPath(QPainterPath &path);
    int type() const override { return Type; }

protected:
    QPointF m_startPosScene;
    QPointF m_endPosScene;
    QRectF m_rcBounding;
    QPen m_pen;
    QPainterPath m_path;
    QPointF m_topLeftInScene;
};

//! [0]
class DiagramItem : public UICanvasItemBase
{
public:
    enum { Type = UserType + 15 };

    DiagramItem(DiagramType diagramType, QMenu *contextMenu, QGraphicsItem *parent = nullptr);

    void setPic(QPixmap pic)
    {
        pix = pic;
        update();
    }
    void removeArrow(Arrow *arrow);
    void removeArrows();
    DiagramType diagramType() const { return myDiagramType; }
    QPolygonF polygon() const { return myPolygon; }
    void addArrow(Arrow *arrow);
    QPixmap image() const;
    int type() const override { return Type; }

    virtual void sizeRefreash() override;

protected:

    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    virtual QRectF getCustomRect(void) const override;

    // 自定义元素绘制
    virtual void customPaint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    DiagramType myDiagramType;
    QPolygonF myPolygon;
    QList<Arrow *> arrows;

    QPainterPath path;
    QPixmap pix;
};
//! [0]

#endif // DIAGRAMITEM_H

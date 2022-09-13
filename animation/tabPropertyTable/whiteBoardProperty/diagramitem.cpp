

#include "diagramitem.h"
#include "arrow.h"

#include <QGraphicsScene>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <QPainter>

// SGraffiti
SGraffiti::SGraffiti() : Shape(tt_Graffiti), m_rcBounding(0, 0, 0, 0)
{}

void SGraffiti::setStartPoint(const QPointF &pos)
{
    setPos(pos);
    m_startPosScene = pos;
    m_path.moveTo(pos);
}

void SGraffiti::setEndPoint(const QPointF &pos)
{
    m_path.lineTo(pos);
    m_rcBounding = m_path.boundingRect();
    m_topLeftInScene = m_rcBounding.topLeft();
    setPos(m_topLeftInScene);
    m_rcBounding.moveTo(0, 0);
}

void SGraffiti::setPath(QPainterPath &path)
{
    m_path = path;
    m_rcBounding = m_path.boundingRect();
    m_topLeftInScene = m_rcBounding.topLeft();
    setPos(m_topLeftInScene);
    m_rcBounding.moveTo(0, 0);
}

void SGraffiti::setStrokeWidth(float w)
{
    m_strokeWidth = w;
    m_pen.setWidthF(w);
}

void SGraffiti::setStrokeColor(const QColor &clr)
{
    m_strokeColor = clr;
    m_pen.setColor(clr);
}

bool SGraffiti::isValid()
{
    return !m_path.isEmpty();
}

void SGraffiti::serialize(QJsonObject &obj)
{
    //
}

QRectF SGraffiti::boundingRect() const
{
    return m_rcBounding;
}

void SGraffiti::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();
    painter->setPen(m_pen);
    QPainterPath path = m_path.translated(-m_topLeftInScene);
    painter->drawPath(path);
    painter->restore();
}


/*-----------------SLine--------------------*/
int Shape::m_idBase = 0;
int Shape::generateLocalId()
{
    return ++m_idBase;
}

// SLine

SLine::SLine() : Shape(tt_Line), m_rcBounding(0, 0, 0, 0)
{}

void SLine::setStartPoint(const QPointF &pos)
{
    setPos(pos);
    m_startPosScene = pos;
}

void SLine::setEndPoint(const QPointF &pos)
{
    m_endPosScene = pos;
    qreal endX = m_endPosScene.x();
    qreal endY = m_endPosScene.y();
    qreal startX = m_startPosScene.x();
    qreal startY = m_startPosScene.y();

    m_rcBounding.setWidth(qAbs(endX - startX));
    m_rcBounding.setHeight(qAbs(endY - startY));

    QPointF startPoint;
    QPointF endPoint;

    if(endX < startX)
    {
        startX = endX;
        startPoint.setX(m_rcBounding.width());
        endPoint.setX(0);
    }
    else
    {
        startPoint.setX(0);
        endPoint.setX(m_rcBounding.width());
    }

    if(endY < startY)
    {
        startY = endY;
        startPoint.setY(m_rcBounding.height());
        endPoint.setY(0);
    }
    else
    {
        startPoint.setY(0);
        endPoint.setY(m_rcBounding.height());
    }

    m_line.setPoints(startPoint, endPoint);
    setPos(startX, startY);
}

void SLine::setStrokeWidth(float w)
{
    m_strokeWidth = w;
    m_pen.setWidthF(w);
}

void SLine::setStrokeColor(const QColor &clr)
{
    m_strokeColor = clr;
    m_pen.setColor(clr);
}

bool SLine::isValid()
{
    return !m_line.isNull();
}

void SLine::serialize(QJsonObject &obj)
{

}

QRectF SLine::boundingRect() const
{
    return m_rcBounding;
}

void SLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();
    painter->setPen(m_pen);
    painter->drawLine(m_line);
    painter->restore();
}


/*----------------------------DiagramItem-------------------------------------*/
DiagramItem::DiagramItem(DiagramType diagramType, QMenu *contextMenu,
                         QGraphicsItem *parent)
    : UICanvasItemBase(parent), myDiagramType(diagramType)
    , myContextMenu(contextMenu)
{
    m_size = QSize(1,1);
    //sizeRefreash();
}

void DiagramItem::removeArrow(Arrow *arrow)
{
    arrows.removeAll(arrow);
}

void DiagramItem::removeArrows()
{
    // need a copy here since removeArrow() will
    // modify the arrows container
    const auto arrowsCopy = arrows;
    for (Arrow *arrow : arrowsCopy) {
        arrow->startItem()->removeArrow(arrow);
        arrow->endItem()->removeArrow(arrow);
        scene()->removeItem(arrow);
        delete arrow;
    }
}

void DiagramItem::addArrow(Arrow *arrow)
{
    arrows.append(arrow);
}

QPixmap DiagramItem::image() const
{
    QPixmap pixmap(250, 250);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::black, 8));
    painter.translate(125, 125);
    painter.drawPolyline(myPolygon);

    return pixmap;
}

void DiagramItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
    myContextMenu->exec(event->screenPos());
}

QVariant DiagramItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
        for (Arrow *arrow : qAsConst(arrows))
            arrow->updatePosition();
    }

    return value;
}

void DiagramItem::sizeRefreash()
{
    myPolygon.clear();
    switch (myDiagramType) {
        case Diagram_StartEnd:
            path.moveTo(200, 50);
            path.arcTo(150, 0, 50, 50, 0, 90);
            path.arcTo(50, 0, 50, 50, 90, 90);
            path.arcTo(50, 50, 50, 50, 180, 90);
            path.arcTo(150, 50, 50, 50, 270, 90);
            path.lineTo(200, 25);
            myPolygon = path.toFillPolygon();

            break;
        case Diagram_Conditional:
            myPolygon << QPointF(0, -m_size.height()/2) << QPointF(m_size.width()/2, 0)
                      << QPointF(0, m_size.height()/2) << QPointF(-m_size.width()/2, 0)
                      << QPointF(0, -m_size.height()/2);
            break;
        case Diagram_Step:
            myPolygon << QPointF(-m_size.width()/2, -m_size.height()/2) << QPointF(m_size.width()/2, -m_size.height() / 2)
                      << QPointF(m_size.width()/2, m_size.height()/2) << QPointF(-m_size.width()/2, m_size.height()/2)
                      << QPointF(-m_size.width()/2, -m_size.height()/2);
            break;
        case Diagram_Triangle:
         myPolygon << QPointF(0, -m_size.height()/2) << QPointF(m_size.width()/2, m_size.height()/2)
                  << QPointF(-m_size.width()/2, m_size.height()/2)
                  << QPointF(0, -m_size.height()/2);
        break;
        case Diagram_Io:
            myPolygon << QPointF(-m_size.width()/2, -m_size.height()/2)
                      << QPointF(0.80 * m_size.width() / 2,  -m_size.height()/2)
                      << QPointF(m_size.width()/2,  m_size.height()/2)
                      << QPointF(-0.80 * m_size.width()/2, m_size.height()/2)
                      << QPointF(-m_size.width()/2, -m_size.height()/2);

            break;
        default:
            break;
    }
}

void DiagramItem::customPaint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();

    QPen pen;
    pen.setColor(QColor(79, 106, 25));
    pen.setWidth(2);
    painter->setPen(pen);
    painter->setBrush(QColor(122, 163, 39));

    if(Diagram_Oval == myDiagramType)
    {
        QRectF rec(-m_size.width()/2,-m_size.height()/2,m_size.width(), m_size.height());
        painter->drawEllipse(rec);
    }else
    {
        painter->drawPolygon(myPolygon);
    }


    painter->restore();
}

QRectF DiagramItem::getCustomRect(void) const
{
    if(Diagram_Oval == myDiagramType)
    {
        return QRectF(-m_size.width()/2,-m_size.height()/2,m_size.width(), m_size.height());
    }else
    {
        return myPolygon.boundingRect();
    }

}



#include "diagramitem.h"
#include "arrow.h"

#include <QGraphicsScene>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <QPainter>

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
            myPolygon << QPointF(m_size.width()/2, 0) << QPointF(m_size.width(), m_size.height()/2)
                      << QPointF(m_size.width()/2, m_size.height()) << QPointF(0, m_size.height()/2)
                      << QPointF(m_size.width()/2, 0);
            break;
        case Diagram_Step:
            myPolygon << QPointF(0, 0) << QPointF(m_size.width(), 0)
                      << QPointF(m_size.width(), m_size.height()) << QPointF(0, m_size.height())
                      << QPointF(0,0);
            break;
        case Diagram_Triangle:
         myPolygon << QPointF(m_size.width()/2, 0) << QPointF(0, m_size.height())
                  << QPointF(m_size.width(), m_size.height())
                  << QPointF(m_size.width()/2, 0);
        break;
        case Diagram_Io:
            myPolygon << QPointF(0, 0)
                      << QPointF(0.80 * m_size.width(), 0)
                      << QPointF(m_size.width(),  m_size.height())
                      << QPointF(0.20 * m_size.width(), m_size.height())
                      << QPointF(0 , 0);

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
        QRectF rec(0,0,m_size.width(), m_size.height());
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
        return QRectF(0,0,m_size.width(), m_size.height());
    }else
    {
        return myPolygon.boundingRect();
    }

}

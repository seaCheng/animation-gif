
#include "arrow.h"
#include "diagramitem.h"
#include "dpi.h"

#include <QPainter>
#include <QPen>
#include <QtMath>

//! [0]
Arrow::Arrow(DiagramItem *startItem, DiagramItem *endItem, QGraphicsItem *parent)
    : QGraphicsLineItem(parent), myStartItem(startItem), myEndItem(endItem)
{
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setPen(QPen(myColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
}
//! [0]

//! [1]
QRectF Arrow::boundingRect() const
{
    qreal extra = (pen().width() + DPI::getScaleUI(20)) / 2.0;

    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                      line().p2().y() - line().p1().y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}
//! [1]

//! [2]
QPainterPath Arrow::shape() const
{
    QPainterPath path = QGraphicsLineItem::shape();
    path.addPolygon(arrowHead);
    return path;
}
//! [2]

//! [3]
void Arrow::updatePosition()
{
    QLineF line(mapFromItem(myStartItem, 0, 0), mapFromItem(myEndItem, 0, 0));
    setLine(line);
}
//! [3]

//! [4]
void Arrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
                  QWidget *)
{
    if (myStartItem->collidesWithItem(myEndItem))
        return;

    QPen myPen = pen();
    myPen.setColor(arrorInformation.arrowColor);
    myPen.setWidth(arrorInformation.penWidth);
    myPen.setStyle(arrorInformation.penStyle);
    qreal arrowSize = DPI::getScaleUI(20) + arrorInformation.penWidth;
    painter->setPen(myPen);
    painter->setBrush(arrorInformation.arrowColor);
//! [4] //! [5]

    QLineF centerLine(myStartItem->pos(), myEndItem->pos());

    QPolygonF startPolygon = myStartItem->polygon();
    QPointF pS1 = startPolygon.first() + myStartItem->pos();
    QPointF intersectPointStart;
    for (int i = 1; i < startPolygon.count(); ++i)
    {
        QPointF pS2 = startPolygon.at(i) + myStartItem->pos();
        QLineF polyLine = QLineF(pS1, pS2);
        QLineF::IntersectionType intersectionTypeStart =
            polyLine.intersects(centerLine, &intersectPointStart);
        if (intersectionTypeStart == QLineF::BoundedIntersection)
            break;
        pS1 = pS2;
    }

    QPolygonF endPolygon = myEndItem->polygon();
    QPointF p1 = endPolygon.first() + myEndItem->pos();
    QPointF intersectPointEnd;
    for (int i = 1; i < endPolygon.count(); ++i)
    {
        QPointF p2 = endPolygon.at(i) + myEndItem->pos();
        QLineF polyLine = QLineF(p1, p2);
        QLineF::IntersectionType intersectionType =
            polyLine.intersects(centerLine, &intersectPointEnd);
        if (intersectionType == QLineF::BoundedIntersection)
            break;
        p1 = p2;
    }

    setLine(QLineF(intersectPointEnd, intersectPointStart));
//! [5] //! [6]

    double angle = std::atan2(-line().dy(), line().dx());

    QPointF arrowP1 = line().p1() + QPointF(sin(angle + M_PI / 3) * arrowSize,
                                    cos(angle + M_PI / 3) * arrowSize);
    QPointF arrowP2 = line().p1() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                    cos(angle + M_PI - M_PI / 3) * arrowSize);

    arrowHead.clear();
    arrowHead << line().p1() << arrowP1 << arrowP2;
//! [6] //! [7]
    painter->drawLine(line());
    painter->drawPolygon(arrowHead);
    if (isSelected()) {
        painter->setPen(QPen(arrorInformation.arrowColor, 1, Qt::DashLine));
        QLineF myLine = line();
        myLine.translate(0, 4.0);
        painter->drawLine(myLine);
        myLine.translate(0,-8.0);
        painter->drawLine(myLine);
    }
}
//! [7]

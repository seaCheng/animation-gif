
#ifndef ARROW_H
#define ARROW_H

#include <QGraphicsLineItem>

#include "WhiteBoardPropertyView.h"

class DiagramItem;

//! [0]
class Arrow : public QGraphicsLineItem
{

public:
    enum { Type = UserType + 4 };

    Arrow(DiagramItem *startItem, DiagramItem *endItem,
          QGraphicsItem *parent = nullptr);

    int type() const override { return Type; }
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void setColor(const QColor &color) { myColor = color; }
    DiagramItem *startItem() const { return myStartItem; }
    DiagramItem *endItem() const { return myEndItem; }

    void updatePosition();

    void setArrowInf(arrowInf arrorInf)
    {
        arrorInformation = arrorInf;
        update();
    }

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;

private:
    DiagramItem *myStartItem;
    DiagramItem *myEndItem;
    QPolygonF arrowHead;
    QColor myColor = Qt::black;

    arrowInf arrorInformation;
};
//! [0]

#endif // ARROW_H

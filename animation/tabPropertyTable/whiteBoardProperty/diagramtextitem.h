
#ifndef DIAGRAMTEXTITEM_H
#define DIAGRAMTEXTITEM_H

#include <QGraphicsTextItem>
#include <QTextDocument>
#include <QPen>

#include "qgraphicseffect.h"
#include "uiCanvasItemBase.h"
#include "whiteBoardPropertyView.h"

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE


class QGraphicsDropShadowEffect;
//! [0]
class DiagramTextItem : public QGraphicsTextItem
{
    Q_OBJECT

public:
    enum { Type = UserType + 3 };

    DiagramTextItem(QMenu * menu,QGraphicsItem *parent = nullptr);

    int type() const override { return Type; }

signals:
    void lostFocus(QGraphicsTextItem *item);
    void selectedChange(QGraphicsItem *item);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void focusOutEvent(QFocusEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;


    QMenu *myContextMenu;
};

class DiagramColorTextItem : public QGraphicsTextItem
{
    Q_OBJECT

public:
    enum { Type = UserType + 13 };

    DiagramColorTextItem(QMenu * menu,QGraphicsItem *parent = nullptr);

    int type() const override { return Type; }

    void setPathInf(pathInf pathIn)
    {
        pathinformation = pathIn;

    }

signals:
    void lostFocus(QGraphicsTextItem *item);
    void selectedChange(QGraphicsItem *item);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void focusOutEvent(QFocusEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QMenu *myContextMenu;

    int iCounter = 0;

    QPointF m_startPosScene;
    QPointF m_endPosScene;
    QRectF m_rcBounding;
    QPen m_pen;
    QPainterPath m_path;
    QPainterPath Textpath;
    QPointF m_topLeftInScene;

    QString strText;

    pathInf pathinformation;
    QGraphicsDropShadowEffect* shadowEffect;
};
//! [0]

#endif // DIAGRAMTEXTITEM_H

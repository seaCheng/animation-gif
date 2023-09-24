
#include "diagramtextitem.h"
#include "graphicsViewComp.h"

#include <QMenu>

#include <QGraphicsSceneContextMenuEvent>
#include <QGraphicsDropShadowEffect>

#include <QTextLayout>
#include <QRandomGenerator>
#include <QBuffer>
#include <QStyleOptionGraphicsItem>


//! [0]
DiagramTextItem::DiagramTextItem(QMenu * menu,QGraphicsItem *parent)
    : QGraphicsTextItem(parent),myContextMenu(menu)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);

    setObjectName("DiagramTextItem");
}
//! [0]

//! [1]
QVariant DiagramTextItem::itemChange(GraphicsItemChange change,
                     const QVariant &value)
{
    if (change == QGraphicsItem::ItemSelectedHasChanged)
        emit selectedChange(this);
    return value;
}
//! [1]

//! [2]
void DiagramTextItem::focusOutEvent(QFocusEvent *event)
{
    setTextInteractionFlags(Qt::NoTextInteraction);
    emit lostFocus((QGraphicsTextItem *)this);
    QGraphicsTextItem::focusOutEvent(event);
}
//! [2]

//! [5]
void DiagramTextItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if (textInteractionFlags() == Qt::NoTextInteraction)
    {
        setTextInteractionFlags(Qt::TextEditorInteraction);
    }
    QGraphicsTextItem::mouseDoubleClickEvent(event);
}
//! [5]

void DiagramTextItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
    myContextMenu->exec(event->screenPos());
}



///////////////////////////////////////////////////////////
//! [0]
DiagramColorTextItem::DiagramColorTextItem(QMenu * menu,QGraphicsItem *parent)
    : QGraphicsTextItem(parent),myContextMenu(menu)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);

    setObjectName("DiagramTextItem");
}
//! [0]

//! [1]
QVariant DiagramColorTextItem::itemChange(GraphicsItemChange change,
                     const QVariant &value)
{
    if (change == QGraphicsItem::ItemSelectedHasChanged)
        emit selectedChange(this);
    return value;
}
//! [1]

//! [2]
void DiagramColorTextItem::focusOutEvent(QFocusEvent *event)
{
    setTextInteractionFlags(Qt::NoTextInteraction);
    emit lostFocus((QGraphicsTextItem *)this);
    QGraphicsTextItem::focusOutEvent(event);
}
//! [2]

//! [5]
void DiagramColorTextItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if (textInteractionFlags() == Qt::NoTextInteraction)
    {
        iCounter = 0;
        setTextInteractionFlags(Qt::TextEditorInteraction);
    }
    QGraphicsTextItem::mouseDoubleClickEvent(event);
}
//! [5]

void DiagramColorTextItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
    myContextMenu->exec(event->screenPos());
}

void DiagramColorTextItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    QStyleOptionGraphicsItem optionx(*option );


    Textpath.clear();

    pathinformation.text = toPlainText();
    int fontWidth = pathinformation.penPathWidth > pathinformation.penPathcontourWidth ?  \
                    pathinformation.penPathWidth : pathinformation.penPathcontourWidth;
    qreal lineHeight = QFontMetricsF(pathinformation.textFont).height() + fontWidth;

    QByteArray content = pathinformation.text.toUtf8();
    Textpath.addText(fontWidth, lineHeight, pathinformation.textFont, content);
    painter->save();

    QPainterPath path;
    path = Textpath;

    QPainterPathStroker stroker;
    stroker.setCapStyle(pathinformation.capStyle);  // 端点风格
    stroker.setJoinStyle(pathinformation.joinStyle);  // 连接样式
    stroker.setDashPattern(pathinformation.penStyle);  // 虚线图案
    stroker.setWidth(pathinformation.penPathWidth);  // 宽度

    // 生成一个新路径（可填充区域），表示原始路径 path 的轮廓
    QPainterPath outlinePath = stroker.createStroke(path);

    QPen pen = painter->pen();
    pen.setColor(pathinformation.pathContourcolor);
    pen.setWidth(pathinformation.penPathcontourWidth);

    setFont(pathinformation.textFont);
    // 用指定的画笔 pen 绘制 outlinePath
    painter->setPen(pen);
    painter->drawPath(outlinePath);

    // 用指定的画刷 brush 填充路径 outlinePath
    painter->fillPath(outlinePath, QBrush(pathinformation.pathColor));

    QRectF rec = outlinePath.boundingRect();
    if(optionx.state & QStyle::State_Selected)
    {
        painter->save();
        QPen pen;
        pen.setWidth(1);
        pen.setColor(QColor(255,0,0));
        pen.setStyle(Qt::DashLine);
        painter->setPen(pen);


        if(rec.width() < 20)
        {
            rec.setWidth(20);
        }

        if(rec.height() < 20)
        {
            rec.setHeight(25);
        }

        rec.adjust(-8, -8, 8, 8);
        painter->drawRect(rec);
        painter->restore();

        if(textInteractionFlags().testAnyFlag(Qt::TextEditorInteraction) && hasFocus())
        {
            QTextCursor cursor(textCursor());
            cursor.movePosition(QTextCursor::End);

            setTextCursor(cursor);

            iCounter++;
            QPen pen = painter->pen();
            pen.setColor(Qt::black);
            pen.setWidth(1);
            painter->setPen(pen);

            int iTotal = 120;
            if(iCounter < iTotal)
            {
                painter->drawLine(rec.right(),rec.top() + 4,
                                  rec.right(),rec.height() - 8);
            }else if(iCounter >= iTotal * 2)
            {
                iCounter = 0;
            }
        }
    }

    painter->restore();
}


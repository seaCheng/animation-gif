#include "diagramitem.h"
#include "arrow.h"

#include <QGraphicsScene>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <QPainter>
#include <QRegion>
#include <QBuffer>

// SGraffiti
SGraffiti::SGraffiti(QMenu * menu) : Shape(menu,tt_Graffiti), m_rcBounding(0, 0, 0, 0)
{
    setResizeAble(false);
    shadowEffect = new QGraphicsDropShadowEffect(this);
        shadowEffect->setOffset(0, 0);
        shadowEffect->setColor(Qt::black);
        shadowEffect->setBlurRadius(10);
    setGraphicsEffect(shadowEffect);
}

void SGraffiti::setStartPoint(const QPointF &pos)
{
    setPos(pos);
    m_startPosScene = pos;
    m_path.moveTo(pos);

}

void SGraffiti::setText(QString str)
{
    strText = str;

    /*
    if(pathinformation.bHandWriting == false)
    {
        Textpath.clear();

        int fontWidth = pathinformation.penPathWidth > pathinformation.penPathcontourWidth ?  \
                        pathinformation.penPathWidth : pathinformation.penPathcontourWidth;
        qreal lineHeight = QFontMetricsF(pathinformation.textFont).height() + fontWidth;
        int lineCount = 0;
        QByteArray content = pathinformation.text.toUtf8();
        QBuffer buff(&content);
        buff.open(QBuffer::ReadOnly);
        while(!buff.atEnd())
        {
            QByteArray line = buff.readLine();
            Textpath.addText(0, 0 + lineCount * lineHeight, pathinformation.textFont, line);
            lineCount++;
        }

        m_rcBounding = Textpath.boundingRect();
        int pathwidth = 2*(pathinformation.penPathWidth + pathinformation.penPathcontourWidth);
        m_rcBounding.adjust(-pathwidth, -pathwidth, pathwidth, pathwidth);
        m_topLeftInScene = m_rcBounding.topLeft();
    }
    */
    update();
}

void SGraffiti::setEndPoint(const QPointF &pos)
{
    m_path.lineTo(pos);
    m_rcBounding = m_path.boundingRect();
    m_rcBounding.adjust(-10, -10,10, 10);
    m_topLeftInScene = m_rcBounding.topLeft();
    m_rcBounding.moveTo(0, 0);
    setPos(m_topLeftInScene);

    update();
}

void SGraffiti::customPaint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();
    painter->setPen(m_pen);

    QPainterPath path;
    path = m_path.translated(-m_topLeftInScene);

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

    // 用指定的画笔 pen 绘制 outlinePath
    painter->setPen(pen);
    painter->drawPath(outlinePath);

    // 用指定的画刷 brush 填充路径 outlinePath
    painter->fillPath(outlinePath, QBrush(pathinformation.pathColor));
    painter->restore();
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

QRectF SGraffiti::getCustomRect(void) const
{
    return m_rcBounding;

}

/*-----------------SLine--------------------*/
int Shape::m_idBase = 0;
int Shape::generateLocalId()
{
    return ++m_idBase;
}

/*----------------------------DiagramItem-------------------------------------*/
DiagramItem::DiagramItem(DiagramType diagramType, QMenu *contextMenu,
                         QGraphicsItem *parent)
    : UICanvasItemBase(contextMenu,parent), myDiagramType(diagramType)
{
    m_size = QSize(1,1);
}

void DiagramItem::removeArrow(Arrow *arrow)
{
    arrows.removeAll(arrow);
}

void DiagramItem::removeArrows()
{
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
    path.clear();
    switch (myDiagramType)
    {
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
        case Diagram_Oval:
        {

            path.addEllipse(getCustomRect());
            myPolygon = path.toFillPolygon();
            break;
        }
        case Diagram_Pic:
            myPolygon = QPolygonF(getCustomRect());
        default:
            break;
    }
}

void DiagramItem::customPaint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();

    QPen pen;
    pen.setColor(itemInformation.itemBoardcolor);
    pen.setWidth(itemInformation.penBoardWidth);
    pen.setStyle(itemInformation.penStyle);
    painter->setPen(pen);
    painter->setBrush(itemInformation.itemColor);

    if(Diagram_Oval == myDiagramType)
    {
        QRectF rec(-m_size.width()/2,-m_size.height()/2,m_size.width(), m_size.height());
        painter->drawEllipse(rec);
    }else if(Diagram_Pic == myDiagramType)
    {
        qreal pixelRatio = painter->device()->devicePixelRatioF();
        QPixmap tpic = pix.scaled(m_size.width()*pixelRatio, m_size.height()*pixelRatio, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        painter->drawPixmap(getCustomRect() ,tpic, QRect());
    }
    else
    {
        painter->drawPolygon(myPolygon);
    }


    painter->restore();
}

QRectF DiagramItem::getCustomRect(void) const
{
    if(Diagram_Oval == myDiagramType || Diagram_Pic == myDiagramType)
    {
        return QRectF(-m_size.width()/2,-m_size.height()/2,m_size.width(), m_size.height());
    }else
    {
        return myPolygon.boundingRect();
    }

}

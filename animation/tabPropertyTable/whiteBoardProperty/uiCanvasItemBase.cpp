#include "uiCanvasItemBase.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVector2D>
#include <QVector3D>
#include <QtMath>


#define PI 3.14159265358979

QImage UICanvasItemBase::m_closeIcon;
QImage UICanvasItemBase::m_resizeIcon;
QImage UICanvasItemBase::m_rotateIcon;

UICanvasItemBase::UICanvasItemBase(QGraphicsItem* parentItem)
    :QGraphicsItem(parentItem)
    ,m_cPenColor(255, 0, 0)
    ,m_cBrushColor(200, 100, 100)

{
    this->setFlag(QGraphicsItem::ItemIsSelectable, true);
    this->setFlag(QGraphicsItem::ItemIsMovable, true);
    this->setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);

    setAcceptHoverEvents(true);
    initIcon();
}

UICanvasItemBase::~UICanvasItemBase()
{

}

void UICanvasItemBase::setItemResizeable(bool resizeable)
{
    m_isResizeable = resizeable;
}

void UICanvasItemBase::setItemResizeRatio(bool resizeRation, qreal rationValue)
{
    m_isRatioScale = resizeRation;
    m_ratioValue = rationValue;
}

QRectF UICanvasItemBase::boundingRect() const
{
    QRectF rectF = getCustomRect();
    if (!this->isSelected())
        return rectF;

    rectF.adjust(-m_nInterval, -m_nInterval, m_nInterval, m_nInterval);
    rectF.adjust(-m_nEllipseWidth, -m_nEllipseWidth, m_nEllipseWidth, m_nEllipseWidth);

    return rectF;
}

void UICanvasItemBase::refreashCursor(QPointF pos, QRectF outLintRect)
{
    if (!this->isSelected())
        return;

    if (lengthPos(pos, outLintRect.topRight()) <= 5)
    {
        setCursor(Qt::SizeBDiagCursor);

    }else if (lengthPos(pos, outLintRect.bottomLeft()) <= 5)
    {
        setCursor(Qt::SizeBDiagCursor);

    }else if (lengthPos(pos, outLintRect.bottomRight()) <= 5)
    {
        setCursor(Qt::SizeFDiagCursor);

    }else if (lengthPos(pos, outLintRect.topLeft()) <= 5)
    {
        setCursor(Qt::SizeFDiagCursor);

    }else if (lengthPos(pos, pTopMiddle) <= 5)
    {
        setCursor(Qt::UpArrowCursor);

    }else if (lengthPos(pos, pRightMiddle) <= 5)
    {
        setCursor(Qt::SizeHorCursor);

    }else if (lengthPos(pos, pLeftMiddle) <= 5)
    {
        setCursor(Qt::SizeHorCursor);

    }else if (lengthPos(pos, pBottomMiddle) <= 5)
    {
        setCursor(Qt::SizeVerCursor);

    }
    else
    {
        setCursor(Qt::ArrowCursor);
    }
}

void UICanvasItemBase::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{

    QRectF itemRect = this->getCustomRect();
    QRectF outLintRect = itemRect.adjusted(-m_nInterval, -m_nInterval, m_nInterval, m_nInterval);

    // 获取当前模式
    QPointF pos = event->pos();

    refreashCursor(pos, outLintRect);

    QGraphicsItem::hoverEnterEvent(event);
}

void UICanvasItemBase::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QRectF itemRect = this->getCustomRect();
    QRectF outLintRect = itemRect.adjusted(-m_nInterval, -m_nInterval, m_nInterval, m_nInterval);

    // 获取当前模式
    QPointF pos = event->pos();

    refreashCursor(pos, outLintRect);
    QGraphicsItem::hoverLeaveEvent(event);

}

void UICanvasItemBase::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter->setRenderHint(QPainter::TextAntialiasing, true);

    // 自定义绘制
    customPaint(painter, option, widget);
    

    if (!this->isSelected())
        return;


    painter->save();
    // 设置画笔
    QPen pen;
    pen.setWidth(m_nPenWidth);
    pen.setColor(m_cPenColor);
    pen.setStyle(Qt::DashLine);
    painter->setPen(pen);

    QRectF itemRect = this->getCustomRect();

    // 绘制轮廓线
    QRectF outLintRect = itemRect.adjusted(-m_nInterval, -m_nInterval, m_nInterval, m_nInterval);
    painter->drawRect(outLintRect);

    pen.setWidth(m_nPenWidth);
    pen.setColor(Qt::gray);
    pen.setStyle(Qt::SolidLine);
    painter->setPen(pen);

    painter->setBrush(Qt::white);

    QRectF recCen(0,0,10,10);

    // 绘制控制点

    recCen.moveCenter(outLintRect.topLeft());
    painter->drawRect(recCen);

    pTopMiddle = outLintRect.topLeft();
    pTopMiddle.setX(pTopMiddle.x() + outLintRect.width()/ 2);
    recCen.moveCenter(pTopMiddle);
    painter->drawRect(recCen);

    recCen.moveCenter(outLintRect.topRight());
    painter->drawRect(recCen);

    pRightMiddle = outLintRect.topRight();
    pRightMiddle.setY(pRightMiddle.y() + outLintRect.height()/ 2);
    recCen.moveCenter(pRightMiddle);
    painter->drawRect(recCen);


    recCen.moveCenter(outLintRect.bottomLeft());
    painter->drawRect(recCen);

    pLeftMiddle = outLintRect.topLeft();
    pLeftMiddle.setY(pLeftMiddle.y() + outLintRect.height()/ 2);
    recCen.moveCenter(pLeftMiddle);
    painter->drawRect(recCen);

    recCen.moveCenter(outLintRect.bottomRight());
    painter->drawRect(recCen);

    pBottomMiddle = outLintRect.bottomLeft();
    pBottomMiddle.setX(pBottomMiddle.x() + outLintRect.width()/ 2);
    recCen.moveCenter(pBottomMiddle);
    painter->drawRect(recCen);

    painter->restore();
}

QPainterPath UICanvasItemBase::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());

    return path;
}

double UICanvasItemBase::lengthPos(const QPointF &p1, const QPointF &p2)
{
    //平方和
    return qSqrt(qPow(p1.x() - p2.x(), 2.0) + qPow(p1.y() - p2.y(), 2.0));
}

void UICanvasItemBase::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_transform = this->transform();

    QRectF itemRect = this->getCustomRect();
    QRectF outLintRect = itemRect.adjusted(-m_nInterval, -m_nInterval, m_nInterval, m_nInterval);

    // 获取当前模式
    QPointF pos = event->pos();
    QPointF scenePos = event->scenePos();
    if (lengthPos(pos, outLintRect.topRight()) <= m_nEllipseWidth)
    {
        setCursor(Qt::SizeBDiagCursor);
        m_itemOper = t_resize;
    }else if (lengthPos(pos, outLintRect.bottomLeft()) <= m_nEllipseWidth)
    {
        setCursor(Qt::SizeBDiagCursor);
        m_itemOper = t_resize;
    }else if (lengthPos(pos, outLintRect.bottomRight()) <= m_nEllipseWidth)
    {
        setCursor(Qt::SizeFDiagCursor);
        m_itemOper = t_resize;
    }else if (lengthPos(pos, outLintRect.topLeft()) <= m_nEllipseWidth)
    {
        setCursor(Qt::SizeFDiagCursor);
        m_itemOper = t_resize;
    }else if (lengthPos(pos, pTopMiddle) <= m_nEllipseWidth)
    {
        setCursor(Qt::UpArrowCursor);
        m_itemOper = t_resize;
    }else if (lengthPos(pos, pRightMiddle) <= m_nEllipseWidth)
    {
        setCursor(Qt::SizeHorCursor);
        m_itemOper = t_resize;
    }else if (lengthPos(pos, pLeftMiddle) <= m_nEllipseWidth)
    {
        setCursor(Qt::SizeHorCursor);
        m_itemOper = t_resize;
    }else if (lengthPos(pos, pBottomMiddle) <= m_nEllipseWidth)
    {
        setCursor(Qt::SizeVerCursor);
        m_itemOper = t_resize;
    }
    else if(itemRect.contains(pos))
    {
       setCursor(Qt::SizeAllCursor);
       m_itemOper = t_move;
    }else
    {
       setCursor(Qt::ArrowCursor);
    }

    // 保存当前的一些信息
    m_pos = pos;
    m_pressedPos = scenePos;
    m_startPos = this->pos();
    return QGraphicsItem::mousePressEvent(event);
}

void UICanvasItemBase::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    // 获取场景坐标和本地坐标
    QPointF scenePos = event->scenePos();
    QPointF pos = event->pos();
    QPointF lPos = event->lastPos();

    if (m_itemOper == t_move)
    {
        // 处理移动
        mouseMoveMoveOperator(scenePos, pos);
    }
    else if (m_itemOper == t_resize)
    {
        // 处理更改大小
        mouseMoveResizeOperator(scenePos, pos, lPos);
    }
    else if (m_itemOper == t_rotate)
    {
        // 处理旋转
        mouseMoveRotateOperator(scenePos, pos);
    }

}

void UICanvasItemBase::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_itemOper = t_none;
    return QGraphicsItem::mouseReleaseEvent(event);
}

QVariant UICanvasItemBase::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange  &&  scene()) // 控件发生移动
        {
            QPointF newPos = value.toPointF(); //即将要移动的位置
            QRectF rect(0, 0, scene()->width(), scene()->height()); // 你要限制的区域
            if (!rect.contains(newPos)) // 是否在区域内
            {
                newPos.setX(qMin(rect.right(), qMax(newPos.x(), rect.left())));
                newPos.setY(qMin(rect.bottom(), qMax(newPos.y(), rect.top())));
                return newPos;
            }else
            {
                prepareGeometryChange();
            }
        }

    return QGraphicsItem::itemChange(change, value);
}

void UICanvasItemBase::mouseMoveMoveOperator(const QPointF& scenePos, const QPointF& loacalPos)
{
    setCursor(Qt::SizeAllCursor);
    qreal xInterval = scenePos.x() - m_pressedPos.x();
    qreal yInterval = scenePos.y() - m_pressedPos.y();

    this->setPos(m_startPos + QPointF(xInterval, yInterval));
    this->update();
}

void UICanvasItemBase::mouseMoveResizeOperator(const QPointF& scenePos, const QPointF& loacalPos, const QPointF& lPos)
{
    if (!m_isResizeable)
        return;

    qreal ratio = m_ratioValue;
    qreal itemWidth = abs(loacalPos.x()) - abs(lPos.x());
    qreal itemHeight = abs(loacalPos.y()) - abs(lPos.y());
    if (m_isRatioScale)
    {
           //itemWidth = itemHeight * 1.0 / ratio;
           //itemHeight = itemWidth * 1.0 / ratio;

    }

    itemWidth = m_size.width() + itemWidth;
    itemHeight = m_size.height() + itemHeight;

    // 设置图片的最小大小为10
    if (itemWidth < 10 || itemHeight < 10)
        return;

    m_size = QSize(itemWidth, itemHeight);
    this->update();
}

void UICanvasItemBase::mouseMoveRotateOperator(const QPointF& scenePos, const QPointF& loacalPos)
{
    // 获取并设置为单位向量
    QVector2D startVec(m_pos.x() - 0, m_pos.y() - 0);
    startVec.normalize();
    QVector2D endVec(loacalPos.x() - 0, loacalPos.y() - 0);
    endVec.normalize();

    // 单位向量点乘，计算角度
    qreal dotValue = QVector2D::dotProduct(startVec, endVec);
    if (dotValue > 1.0)
        dotValue = 1.0;
    else if (dotValue < -1.0)
        dotValue = -1.0;

    dotValue = qAcos(dotValue);
    if (isnan(dotValue))
        dotValue = 0.0;

    // 获取角度
    qreal angle = dotValue * 1.0 *180/PI;

    // 向量叉乘获取方向
    QVector3D crossValue = QVector3D::crossProduct(QVector3D(startVec, 1.0),QVector3D(endVec, 1.0));
    if (crossValue.z() < 0)
        angle = -angle;
    m_rotate += angle;

    // 设置变化矩阵
    m_transform.rotate(m_rotate);
    this->setTransform(m_transform);

    m_pos = loacalPos;
    this->update();
}

void UICanvasItemBase::customPaint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawEllipse(getCustomRect());
}

QRectF UICanvasItemBase::getCustomRect(void) const
{
    QPointF centerPos(0, 0);
    return QRectF(centerPos.x() - m_size.width() / 2, centerPos.y() - m_size.height() / 2, \
                  m_size.width(), m_size.height());
}

void UICanvasItemBase::initIcon(void)
{
    if (m_closeIcon.isNull())
        m_closeIcon.load(":images/icon_close.png");
    if (m_resizeIcon.isNull())
        m_resizeIcon.load(":images/icon_stretch.png");
    if (m_rotateIcon.isNull())
        m_rotateIcon.load(":images/icon_rotate.png");

    m_closePixmap = QPixmap::fromImage(m_closeIcon);
    m_resizePixmap = QPixmap::fromImage(m_resizeIcon);
    m_rotatePixmap = QPixmap::fromImage(m_rotateIcon);
}


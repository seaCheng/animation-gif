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

void UICanvasItemBase::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter->setRenderHint(QPainter::TextAntialiasing, true);

    // 自定义绘制
    customPaint(painter, option, widget);
    

    if (!this->isSelected())
        return;


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

    painter->setPen(Qt::NoPen);
    painter->setBrush(m_cBrushColor);

    // 绘制控制点
    painter->drawEllipse(outLintRect.topRight(), m_nEllipseWidth, m_nEllipseWidth);
    if (!m_closePixmap.isNull())
        painter->drawPixmap(QRect(outLintRect.topRight().x() - m_nEllipseWidth / 2, \
                                  outLintRect.topRight().y() - m_nEllipseWidth / 2, \
                                  m_nEllipseWidth, m_nEllipseWidth), m_closePixmap);

    painter->drawEllipse(outLintRect.bottomLeft(), m_nEllipseWidth, m_nEllipseWidth);
    if (!m_rotatePixmap.isNull())
        painter->drawPixmap(QRect(outLintRect.bottomLeft().x() - m_nEllipseWidth / 2, \
                                  outLintRect.bottomLeft().y() - m_nEllipseWidth / 2, \
                                  m_nEllipseWidth, m_nEllipseWidth), m_rotatePixmap);

    painter->drawEllipse(outLintRect.bottomRight(), m_nEllipseWidth, m_nEllipseWidth);
    if (!m_resizePixmap.isNull())
        painter->drawPixmap(QRect(outLintRect.bottomRight().x() - m_nEllipseWidth / 2, \
                                  outLintRect.bottomRight().y() - m_nEllipseWidth / 2, \
                                  m_nEllipseWidth, m_nEllipseWidth), m_resizePixmap);
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
    if (itemRect.contains(pos))
        m_itemOper = t_move;
    else if (lengthPos(pos, outLintRect.topRight()) <= m_nEllipseWidth)
        emit onClickedCopyItem();
    else if (lengthPos(pos, outLintRect.bottomLeft()) <= m_nEllipseWidth)
        m_itemOper = t_rotate;
    else if (lengthPos(pos, outLintRect.bottomRight()) <= m_nEllipseWidth)
        m_itemOper = t_resize;

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

    if (m_itemOper == t_move)
    {
        // 处理移动
        mouseMoveMoveOperator(scenePos, pos);
    }
    else if (m_itemOper == t_resize)
    {
        // 处理更改大小
        mouseMoveResizeOperator(scenePos, pos);
    }
    else if (m_itemOper == t_rotate)
    {
        // 处理旋转
        mouseMoveRotateOperator(scenePos, pos);
    }

    //return QGraphicsItem::mouseMoveEvent(event);
}

void UICanvasItemBase::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_itemOper = t_none;
    return QGraphicsItem::mouseReleaseEvent(event);
}

QVariant UICanvasItemBase::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemSelectedChange)
        prepareGeometryChange();

    return QGraphicsItem::itemChange(change, value);
}

void UICanvasItemBase::mouseMoveMoveOperator(const QPointF& scenePos, const QPointF& loacalPos)
{
    qreal xInterval = scenePos.x() - m_pressedPos.x();
    qreal yInterval = scenePos.y() - m_pressedPos.y();

    this->setPos(m_startPos + QPointF(xInterval, yInterval));
    this->update();
}

void UICanvasItemBase::mouseMoveResizeOperator(const QPointF& scenePos, const QPointF& loacalPos)
{
    if (!m_isResizeable)
        return;

    qreal ratio = m_ratioValue;
    qreal itemWidth = abs(loacalPos.x()) * 2 - m_nInterval - m_nEllipseWidth;
    qreal itemHeight = abs(loacalPos.y()) * 2 - m_nInterval - m_nEllipseWidth;
    if (m_isRatioScale)
        itemHeight = itemWidth * 1.0 / ratio;

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
    qreal angle = dotValue * 1.0 / (PI / 180);

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


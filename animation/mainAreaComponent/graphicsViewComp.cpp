#include "graphicsViewComp.h"
#include "diagramitem.h"
#include "diagramtextitem.h"
#include "arrow.h"

#include "uiCanvasItemBase.h"

#include "pictureItem.h"
#include <QGraphicsScene>
#include <QPushButton>
#include <QGraphicsWidget>
#include <QGraphicsLinearLayout>
#include <QTextEdit>
#include <QToolButton>
#include <QOpenGLWidget>
#include <QDebug>
#include <QMenu>

#include <QGraphicsSceneMouseEvent>

/*--------------------------GraphicsViewComp-----------------------------*/
GraphicsViewComp::GraphicsViewComp(QGraphicsScene *scene, QWidget *parent)
    :QGraphicsView(scene, parent)
{
    pScene = (PicGraphicsScene *)scene;
    connect(pScene, &PicGraphicsScene::s_modeRef, this, [=](InsertMode mode)
    {
        if(MoveItem == mode)
        {
           setDragMode(QGraphicsView::RubberBandDrag);
        }else
        {
           setDragMode(QGraphicsView::NoDrag);
        }
    });
    setStyleSheet("padding: 0px; border: 1px;");
    viewport()->setContentsMargins(0,0,0,0);
    setViewportUpdateMode(FullViewportUpdate);
    setDragMode(QGraphicsView::RubberBandDrag);
}

void GraphicsViewComp::setGifCommpro(std::shared_ptr<propertyInf> inf)
{
    proInf = inf;
    PicGraphicsScene * pScene = (PicGraphicsScene *)scene();
    if(!pScene)
    {
        return;
    }
    pScene->setGifCommpro(inf);

    refreashSize();
}

void GraphicsViewComp::refreashSize()
{

    QWidget * wid = parentWidget();
    if(wid != nullptr && pPicItem != nullptr)
    {
        PicGraphicsScene * pScene = (PicGraphicsScene *)scene();
        if(!pScene)
        {
            return;
        }

        int iSceneHeigth;
        int iSceneWidth;
        if(proInf->scMode == screen_horizal)
        {
            iSceneWidth = proInf->width;
            iSceneHeigth = proInf->heigth;
        }else
        {
            iSceneWidth = proInf->heigth;
            iSceneHeigth = proInf->width;
        }
        qreal iViewheigth = wid->height() - 40;
        qreal iViewwidth = ((qreal)iSceneWidth * iViewheigth / iSceneHeigth);
        if(iSceneWidth > iViewwidth)
        {

            setFixedSize(iViewwidth,iViewheigth);
            pScene->setSceneRect(0,0,iSceneWidth,iSceneHeigth);
        }else
        {

            setFixedSize(iSceneWidth,iSceneHeigth);
            pScene->setSceneRect(0,0,iSceneWidth,iSceneHeigth);
        }
        pScene->update();
        update();
    }
}

void GraphicsViewComp::paintEvent(QPaintEvent *event)
{
    QGraphicsView::paintEvent(event);
}


void GraphicsViewComp::resizeEvent(QResizeEvent *event)
{

    QGraphicsView::resizeEvent(event);
    refreashSize();
}

void GraphicsViewComp::setPicItem(PictureItem * pItem)
{

    pPicItem = pItem;

    PicGraphicsScene * pScene = (PicGraphicsScene *)scene();
    if(pScene)
    {
        pScene->setPicItem(pItem);

    }

    refreashSize();
}


////////////////////////////////PicGraphicsScene ///////////////////////////////////
PicGraphicsScene::PicGraphicsScene(QWidget * p)
    :QGraphicsScene(p)
{
    myItemMenu = new QMenu;
    dType = Diagram_Step;
    line = nullptr;
    textItem = nullptr;
    myItemColor = Qt::white;
    myTextColor = Qt::black;
    myLineColor = Qt::black;

    setBackgroundBrush(Qt::white);

}

void PicGraphicsScene::setGifCommpro(std::shared_ptr<propertyInf> inf)
{
    proInf = inf;
}

void PicGraphicsScene::setPicItem(PictureItem * pItem)
{
    mpItem = pItem;
    if(pItem != nullptr)
    {
        pic = mpItem->pic();

    }else
    {
        pic = QPixmap();
    }
}

void PicGraphicsScene::setMode(InsertMode mode)
{
    iMode = mode;

    emit s_modeRef(iMode);
}

void PicGraphicsScene::setItemType(DiagramType type)
{
    dType = type;
}

void PicGraphicsScene::editorLostFocus(DiagramTextItem *item)
{
    QTextCursor cursor = item->textCursor();
    cursor.clearSelection();
    item->setTextCursor(cursor);

    if (item->toPlainText().isEmpty()) {
        removeItem(item);
        item->deleteLater();
    }
}

void PicGraphicsScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    QGraphicsScene::drawBackground(painter, rect);

    if(views().count()==0)
           return;

    if(mpItem == nullptr)
          return;

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    qreal pixelRatio = painter->device()->devicePixelRatioF();
    QRectF sizeRec = sceneRect();
    //绘制指定图片作为背景

    Qt::AspectRatioMode asMode = (Qt::AspectRatioMode)(int)proInf->fMode;
    QPixmap tpic = pic.scaled(sizeRec.width(), sizeRec.height(), asMode, Qt::SmoothTransformation);
    QImage desImage(sizeRec.width(), sizeRec.height(), QImage::Format_ARGB32);
    desImage.fill(proInf->color);

    QRect rectPic(0, 0, sizeRec.width(), sizeRec.height());
    if (tpic.width() < sizeRec.width())
    {
        rectPic.setX((sizeRec.width() - tpic.width()) / 2);
        rectPic.setY(0);
        rectPic.setWidth(tpic.width());
        rectPic.setHeight(tpic.height());
    }

    if (tpic.height() < sizeRec.height())
    {
        rectPic.setX(0); rectPic.setY((sizeRec.height() - tpic.height()) / 2);
        rectPic.setWidth(tpic.width());
        rectPic.setHeight(tpic.height());
    }

    QPixmap tpicRato = pic.scaled(sizeRec.width() * pixelRatio, sizeRec.height() * pixelRatio, asMode, Qt::SmoothTransformation);
    painter->drawImage(sizeRec,desImage);
    painter->drawPixmap(rectPic, tpicRato, QRect());

    painter->restore();
}

void PicGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton)
        return;

    switch (iMode) {
        case InsertItem:
            item = new DiagramItem(dType, myItemMenu);
            addItem(item);
            item->setPos(mouseEvent->scenePos());
            item->setSelected(false);

            break;
//! [6] //! [7]
        case InsertLine:
            line = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(),
                                        mouseEvent->scenePos()));
            line->setPen(QPen(myLineColor, 2));
            addItem(line);
            break;
//! [7] //! [8]
        case InsertText:
            textItem = new DiagramTextItem();
            textItem->setFont(myFont);
            textItem->setTextInteractionFlags(Qt::TextEditorInteraction);
            textItem->setZValue(1000.0);
            connect(textItem, &DiagramTextItem::lostFocus,
                    this, &PicGraphicsScene::editorLostFocus);
            connect(textItem, &DiagramTextItem::selectedChange,
                    this, &PicGraphicsScene::itemSelected);
            addItem(textItem);
            textItem->setDefaultTextColor(myTextColor);
            textItem->setPos(mouseEvent->scenePos());

            break;
         default:
         {

             break;
         }

    }

    QGraphicsScene::mousePressEvent(mouseEvent);


}

void PicGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(mouseEvent->isAccepted())
    {
        return;
    }

    if (iMode == InsertLine && line != nullptr) {
        QLineF newLine(line->line().p1(), mouseEvent->scenePos());
        line->setLine(newLine);

    }else if(iMode == InsertItem && item != nullptr)
    {
        QSize size;
        size.setWidth(abs(mouseEvent->scenePos().x() - item->pos().x() ));
        size.setHeight(abs(mouseEvent->scenePos().y() - item->pos().y() ));

        if(size.width() < 15)
        {
           size.setWidth(15);
        }

        if(size.height() < 15)
        {
           size.setHeight(15);
        }

        item->setRectSize(size);
        item->sizeRefreash();

        item->update();

    }
    else if (iMode == MoveItem) {
        QGraphicsScene::mouseMoveEvent(mouseEvent);
    }
}

void PicGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (line != nullptr && iMode == InsertLine)
    {
        QList<QGraphicsItem *> startItems = items(line->line().p1());
        if (startItems.count() && startItems.first() == line)
            startItems.removeFirst();
        QList<QGraphicsItem *> endItems = items(line->line().p2());
        if (endItems.count() && endItems.first() == line)
            endItems.removeFirst();

        removeItem(line);
        delete line;
//! [11] //! [12]

        if (startItems.count() > 0 && endItems.count() > 0 &&
            startItems.first()->type() == DiagramItem::Type &&
            endItems.first()->type() == DiagramItem::Type &&
            startItems.first() != endItems.first()) {
            DiagramItem *startItem = qgraphicsitem_cast<DiagramItem *>(startItems.first());
            DiagramItem *endItem = qgraphicsitem_cast<DiagramItem *>(endItems.first());
            Arrow *arrow = new Arrow(startItem, endItem);
            arrow->setColor(myLineColor);
            startItem->addArrow(arrow);
            endItem->addArrow(arrow);
            arrow->setZValue(-1000.0);
            addItem(arrow);
            arrow->updatePosition();
        }


    }else if(item != nullptr && iMode == InsertItem)
    {
        item->setSelected(true);
    }

//! [12] //! [13]
    line = nullptr;
    item = nullptr;
    setMode(MoveItem);

    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

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
#include <QFileDialog>

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
    setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
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
PicGraphicsScene::PicGraphicsScene(QMenu * menu, QWidget * p)
    :QGraphicsScene(p)
{
    myItemMenu = menu;
    dType = Diagram_Step;
    line = nullptr;
    textItem = nullptr;
    myItemColor = Qt::white;
    myTextColor = Qt::black;
    myLineColor = Qt::black;

    setBackgroundBrush(QColor(255,255,255,0));

}

void PicGraphicsScene::setGifCommpro(std::shared_ptr<propertyInf> inf)
{
    proInf = inf;
}

void PicGraphicsScene::setWhiteBoardPro(std::shared_ptr<whiteBoardProInf> inf, refreashProType proType)
{
    whiteBoardInf = inf;
    QList<QGraphicsItem *> lstselectedItems = this->selectedItems();
    for (QGraphicsItem *item : qAsConst(lstselectedItems))
    {

        if (item->type() == DiagramTextItem::Type && proType == pro_text)
        {
            DiagramTextItem * textItem = (DiagramTextItem *)item;
            textItem->setFont(whiteBoardInf->font);
            textItem->setDefaultTextColor(whiteBoardInf->textColor);


        }else if(item->type() == SGraffiti::Type && proType == pro_pen)
        {
            SGraffiti * sgra = (SGraffiti *)item;
            if(whiteBoardInf->pathInfmation.bHandWriting == sgra->getHandWriteState())
            {
                sgra->setPathInf(whiteBoardInf->pathInfmation);
            }

        }else if(item->type() == DiagramItem::Type && proType == pro_item)
        {
             DiagramItem * digItem = (DiagramItem *)item;
             digItem->setItemInf(whiteBoardInf->itemInfmation);
        }else if(item->type() == Arrow::Type && proType == pro_arrow)
        {
             Arrow * arrItem = (Arrow *)item;
             arrItem->setArrowInf(whiteBoardInf->arrowInformation);
        }
    }
    update();
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
    if(views().count()==0)
           return;

    if(mpItem == nullptr)
          return;

    painter->save();
    painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
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
    if(asMode == Qt::KeepAspectRatio)
    {
        painter->drawImage(sizeRec,desImage);
    }else
    {
        QImage tImage(sizeRec.width(), sizeRec.height(), QImage::Format_ARGB32);
        tImage.fill(QColor(255,255,255,0));
        painter->drawImage(sizeRec,tImage);
    }

    if(pic.isNull() == false)
    {
        painter->drawPixmap(rectPic, tpicRato, QRect());
    }

    painter->restore();
}

void PicGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton)
        return;

    auto au = selectedItems();
    for(auto u : au)
    {
        if(u->sceneBoundingRect().contains(mouseEvent->scenePos()))
        {
            if(DeleteItem == iMode)
            {
                QList<QGraphicsItem *> lstselectedItems = this->selectedItems();
                for (QGraphicsItem *item : qAsConst(lstselectedItems)) {
                    if (item->type() == Arrow::Type) {
                        removeItem(item);
                        Arrow *arrow = qgraphicsitem_cast<Arrow *>(item);
                        arrow->startItem()->removeArrow(arrow);
                        arrow->endItem()->removeArrow(arrow);
                        delete item;
                    }
                }

                lstselectedItems = selectedItems();
                for (QGraphicsItem *item : qAsConst(lstselectedItems)) {
                     if (item->type() == DiagramItem::Type)
                         qgraphicsitem_cast<DiagramItem *>(item)->removeArrows();
                     removeItem(item);
                     delete item;
                 }
                return;
            }else
            {
               return  QGraphicsScene::mousePressEvent(mouseEvent);
            }

        }
    }

    switch (iMode) {
        case InsertItem:
            item = new DiagramItem(dType, myItemMenu);
            item->setItemInf(whiteBoardInf->itemInfmation);
            addItem(item);
            item->setPos(mouseEvent->scenePos());
            item->setSelected(false);

            break;

    case InsertPic:
        item = new DiagramItem(dType, myItemMenu);
        addItem(item);
        item->setPos(mouseEvent->scenePos());
        item->setSelected(false);

        break;

        case InsertLine:
            line = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(),
                                        mouseEvent->scenePos()));
            line->setPen(QPen(whiteBoardInf->arrowInformation.arrowColor, whiteBoardInf->arrowInformation.penWidth));
            addItem(line);
            QGraphicsScene::mousePressEvent(mouseEvent);
            break;
    case InsertDrawLine:
        m_currentShape = new SGraffiti(myItemMenu);
        m_currentShape->setPathInf(whiteBoardInf->pathInfmation);
        m_currentShape->setStartPoint(mouseEvent->scenePos());
        if(whiteBoardInf->pathInfmation.bHandWriting == false)
        {
            m_currentShape->setSelected(true);
        }
        addItem(m_currentShape);

        break;

        case InsertText:
            textItem = new DiagramTextItem(myItemMenu);
            textItem->setFont(whiteBoardInf->font);
            textItem->setDefaultTextColor(whiteBoardInf->textColor);
            textItem->setTextInteractionFlags(Qt::TextEditorInteraction);
            textItem->setZValue(1000.0);
            connect(textItem, &DiagramTextItem::lostFocus,
                    this, &PicGraphicsScene::editorLostFocus);
            connect(textItem, &DiagramTextItem::selectedChange,
                    this, &PicGraphicsScene::itemSelected);
            addItem(textItem);
            textItem->setPos(mouseEvent->scenePos());
            textItem->setSelected(true);

            QGraphicsScene::mousePressEvent(mouseEvent);
            break;
    case DeleteItem:
        QGraphicsScene::mousePressEvent(mouseEvent);

        break;
         default:
         {
             QGraphicsScene::mousePressEvent(mouseEvent);
             break;
         }
    }
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

    }else if(iMode == InsertDrawLine && m_currentShape != nullptr)
    {
        if(whiteBoardInf->pathInfmation.bHandWriting)
        {
            m_currentShape->setEndPoint(mouseEvent->scenePos());
            update();
        }else
        {
            QGraphicsScene::mouseMoveEvent(mouseEvent);
        }

    }
    else if((iMode == InsertItem || iMode == InsertPic ) && item != nullptr)
    {
        qreal itemWidthMove = mouseEvent->scenePos().x() - mouseEvent->lastScenePos().x();
        qreal itemHeigthMove = mouseEvent->scenePos().y() - mouseEvent->lastScenePos().y();
        QSize size;
        size.setWidth(item->getRectSize().width() + itemWidthMove);
        size.setHeight(item->getRectSize().height() + itemHeigthMove);

        QPointF pi = item->pos();
        pi.setX(pi.x() + itemWidthMove / 2);
        pi.setY(pi.y() + itemHeigthMove / 2);
        item->setPos(pi);
        item->setRectSize(size);
        item->sizeRefreash();
        item->setSelected(false);
        item->update();

    }
    else /*if (iMode == MoveItem)*/ {
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
            startItems.first() != endItems.first())
        {
            DiagramItem *startItem = qgraphicsitem_cast<DiagramItem *>(startItems.first());
            DiagramItem *endItem = qgraphicsitem_cast<DiagramItem *>(endItems.first());
            Arrow *arrow = new Arrow(startItem, endItem);
            //arrow->setColor(myLineColor);
            arrow->setArrowInf(whiteBoardInf->arrowInformation);
            startItem->addArrow(arrow);
            endItem->addArrow(arrow);
            arrow->setZValue(-1000.0);
            addItem(arrow);
            arrow->updatePosition();
        }


    }else if(item != nullptr && (iMode == InsertItem))
    {
        QSize size = item->getRectSize();
        if(size.width() < 35)
        {
           size.setWidth(35);
        }

        if(size.height() < 35)
        {
           size.setHeight(35);
        }
        item->setRectSize(size);
        item->sizeRefreash();

        item->setSelected(true);
    }else if(item != nullptr && iMode == InsertPic)
    {
        item->setSelected(true);
        QSize size = item->getRectSize();
        if(size.width() < 35)
        {
           size.setWidth(35);
        }

        if(size.height() < 35)
        {
           size.setHeight(35);
        }
        item->setRectSize(size);
        item->sizeRefreash();

        QFileDialog::Options options =  QFileDialog::ReadOnly;

        QString fileName = QFileDialog::getOpenFileName(nullptr, tr("Open File"),
                                                        QDir::homePath(),
                                                        "Images (*.bmp *.jpg *.png *.ico)", nullptr, options);

        if(fileName.isEmpty())
        {
            removeItem(item);
            delete item;
            item = nullptr;
        }else
        {
            item->setPic(QPixmap(fileName));
        }


    }
    else if(m_currentShape != nullptr && iMode == InsertDrawLine && whiteBoardInf->pathInfmation.bHandWriting)
    {
        if(m_currentShape->sceneBoundingRect().width() < 15 &&
                m_currentShape->sceneBoundingRect().height() < 15)
        {
            removeItem(m_currentShape);
            delete m_currentShape;
            m_currentShape = nullptr;
        }

    }

    line = nullptr;
    item = nullptr;
    m_currentShape = nullptr;

    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

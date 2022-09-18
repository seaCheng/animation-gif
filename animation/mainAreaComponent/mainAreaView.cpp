#include "mainAreaView.h"
#include "emptyAreaView.h"
#include "graphicsViewComp.h"
#include "sacleButtonView.h"
#include "diagramitem.h"
#include "arrow.h"
#include "diagramtextitem.h"

#include<QPainter>
#include<QDebug>
#include<QHBoxLayout>
#include <QGraphicsItem>
#include <QAction>
#include <QMenu>

GraphicFrame::GraphicFrame(QWidget *parent)
    :QFrame(parent)
{
    scaleView = new ScaleButtonView(this);
    setConnect();

}

void GraphicFrame::setConnect()
{
    connect(scaleView, &ScaleButtonView::s_scaleFreash, this, &GraphicFrame::s_scaleFreash);
}

void GraphicFrame::showEvent(QShowEvent *event)
{
    if(isVisible())
    {
       scaleView->setGeometry(width() - 52, height() - 140, 50, 130);
    }
}

void GraphicFrame::resizeEvent(QResizeEvent *)
{
    scaleView->setGeometry(width() - 52, height() - 140, 50, 130);
}

/*----------GraphicFrame------------------*/

/*----------MainAreaView------------------*/
MainAreaView::MainAreaView(QWidget *parent)
    : QStackedWidget(parent)
{
    createActions();

    emptyView = new EmptyAreaView;
    addWidget(emptyView);

    graWid = new GraphicFrame;
    graWid->setFrameShape(QFrame::Panel);
    graWid->setFrameShadow(QFrame::Sunken);
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setContentsMargins(1,1,1,1);
    graWid->setLayout(layout);
    pScene = new PicGraphicsScene(itemMenu, graWid);
    graphicView = new GraphicsViewComp(pScene);
    layout->addWidget(graphicView);
    addWidget(graWid);

    setCurrentWidget(emptyView);
    setConnect();
}

void MainAreaView::createActions()
{
    toFrontAction = new QAction(QIcon(":/images/bringtofront.png"),
                                tr("Bring to &Front"), this);
    toFrontAction->setShortcut(tr("Ctrl+F"));
    toFrontAction->setStatusTip(tr("Bring item to front"));
    connect(toFrontAction, &QAction::triggered, this, [=](){

        if (pScene->selectedItems().isEmpty())
            return;

        QGraphicsItem *selectedItem = pScene->selectedItems().first();
        const QList<QGraphicsItem *> overlapItems = selectedItem->collidingItems();

        qreal zValue = 0;
        for (const QGraphicsItem *item : overlapItems) {
            if (item->zValue() >= zValue && (item->type() == DiagramItem::Type ||
                                             item->type() == DiagramTextItem::Type ||
                                             item->type() == SGraffiti::Type))
                zValue = item->zValue() + 0.1;
        }
        selectedItem->setZValue(zValue);

    });

    sendBackAction = new QAction(QIcon(":/images/sendtoback.png"), tr("Send to &Back"), this);
    sendBackAction->setShortcut(tr("Ctrl+T"));
    sendBackAction->setStatusTip(tr("Send item to back"));
    connect(sendBackAction, &QAction::triggered, this, [=](){
        if (pScene->selectedItems().isEmpty())
            return;

        QGraphicsItem *selectedItem = pScene->selectedItems().first();
        const QList<QGraphicsItem *> overlapItems = selectedItem->collidingItems();

        qreal zValue = 0;
        for (const QGraphicsItem *item : overlapItems) {
            if (item->zValue() <= zValue && (item->type() == DiagramItem::Type ||
                                             item->type() == DiagramTextItem::Type ||
                                             item->type() == SGraffiti::Type))
                zValue = item->zValue() - 0.1;
        }
        selectedItem->setZValue(zValue);
    });

    deleteAction = new QAction(QIcon(":/images/delete.png"), tr("&Delete"), this);
    deleteAction->setShortcut(tr("Delete"));
    deleteAction->setStatusTip(tr("Delete item from diagram"));
    connect(deleteAction, &QAction::triggered, this, [=](){

        QList<QGraphicsItem *> selectedItems = pScene->selectedItems();
        for (QGraphicsItem *item : qAsConst(selectedItems)) {
            if (item->type() == Arrow::Type) {
                pScene->removeItem(item);
                Arrow *arrow = qgraphicsitem_cast<Arrow *>(item);
                arrow->startItem()->removeArrow(arrow);
                arrow->endItem()->removeArrow(arrow);
                delete item;
            }
        }

        selectedItems = pScene->selectedItems();
        for (QGraphicsItem *item : qAsConst(selectedItems)) {
             if (item->type() == DiagramItem::Type)
                 qgraphicsitem_cast<DiagramItem *>(item)->removeArrows();
             pScene->removeItem(item);
             delete item;
         }
    });


    resetRotaAction = new QAction(QIcon(":/images/icon_rotate.png"), tr("&reset rotation"), this);
    resetRotaAction->setShortcut(tr("reset rotation"));
    resetRotaAction->setStatusTip(tr("reset rotation"));
    connect(resetRotaAction, &QAction::triggered, this, [=](){

        QList<QGraphicsItem *> selectedItems = pScene->selectedItems();

        for (QGraphicsItem *item : qAsConst(selectedItems)) {

            QTransform transform;
            transform.reset();
            item->setTransform(transform);
         }
    });

    itemMenu = new QMenu(this);
    itemMenu->addAction(deleteAction);
    itemMenu->addSeparator();
    itemMenu->addAction(toFrontAction);
    itemMenu->addAction(sendBackAction);
    itemMenu->addSeparator();
    itemMenu->addAction(resetRotaAction);
}

void MainAreaView::setConnect()
{
    connect(emptyView, &EmptyAreaView::s_clicked, this, &MainAreaView::s_clicked);
    connect(graWid, &GraphicFrame::s_scaleFreash, this, [&](qreal lValue){

        double newScale = lValue;
        QTransform oldMatrix = graphicView->transform();
        graphicView->resetTransform();
        graphicView->translate(oldMatrix.dx(), oldMatrix.dy());
        graphicView->scale(newScale, newScale);

        for(const auto &u : graphicView->scene()->items())
        {
                    QGraphicsItem * item = (QGraphicsItem *)u;


                    item->setSelected(false);
                    item->clearFocus();
                    if(DiagramTextItem::Type == item->type())
                    {
                       DiagramTextItem * textItem = (DiagramTextItem *)item;
                       textItem->setTextInteractionFlags(Qt::NoTextInteraction);
                       textItem->clearFocus();
                       textItem->setSelected(false);
                       qDebug()<<"clear focus....";
                    }

        }

        QImage image(graphicView->size(),QImage::Format_ARGB32);
                 QPainter painter(&image);
                 graphicView->scene()->render(&painter);   //关键函数
                 image.save("test.png");


    });
}

void MainAreaView::setGifCommpro(std::shared_ptr<propertyInf> inf)
{
    graphicView->setGifCommpro(inf);

}

//DiagramType { Diagram_Text, Diagram_Step, Diagram_Conditional, Diagram_StartEnd, Diagram_Io }
void MainAreaView::start_insertSceneItem(DiagramType type)
{
    switch(type)
    {
       case Diagram_Text:
       {
          pScene->setMode(InsertText);
          break;
       }
       case Diagram_Step:
       case Diagram_Triangle:
       case Diagram_Oval:
       case Diagram_Conditional:
       case Diagram_Io:
      {
         pScene->setMode(InsertItem);
         break;
      }
      case Diagram_StartEnd:
      {
         pScene->setMode(InsertLine);
         break;
      }
      case Diagram_Sel:
      {
       pScene->setMode(MoveItem);
       break;
      }
      case Diagram_Pen:
      {
        pScene->setMode(InsertDrawLine);
        break;
      }
      case Diagram_Del:
      {
        pScene->setMode(DeleteItem);
        break;
      }
      case Diagram_Pic:
      {
        pScene->setMode(InsertPic);
        break;
      }

    default:
      {
        break;
      }
    }

    pScene->setItemType(type);
}

void MainAreaView::slot_selPicItem(PictureItem * pItem)
{
    if(pItem == nullptr)
    {
        graphicView->setPicItem(pItem);
        setCurrentWidget(emptyView);
    }else
    {
        graphicView->setPicItem(pItem);
        setCurrentWidget(graWid);
    }

}

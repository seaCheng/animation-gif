#include "mainAreaView.h"
#include "emptyAreaView.h"
#include "graphicsViewComp.h"
#include "sacleButtonView.h"

#include<QPainter>
#include<QDebug>
#include<QHBoxLayout>
#include <QGraphicsItem>

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

    emptyView = new EmptyAreaView;
    addWidget(emptyView);

    graWid = new GraphicFrame;
    graWid->setFrameShape(QFrame::Panel);
    graWid->setFrameShadow(QFrame::Sunken);
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setContentsMargins(1,1,1,1);
    graWid->setLayout(layout);
    pScene = new PicGraphicsScene(graWid);
    graphicView = new GraphicsViewComp(pScene);
    layout->addWidget(graphicView);
    addWidget(graWid);

    setCurrentWidget(emptyView);

    setConnect();
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

                    //QGraphicsTextItem * item = (QGraphicsTextItem *)u;
                    //u->setSelected(false);
                    //item->setTextInteractionFlags(Qt::NoTextInteraction);//恢复不能编辑状态;
                    //item->setRotation(item->rotation() + 20);
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

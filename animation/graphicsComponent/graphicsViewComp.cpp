#include "graphicsViewComp.h"
#include <QGraphicsScene>
#include <QPushButton>
#include <QGraphicsWidget>
#include <QGraphicsLinearLayout>
#include <QTextEdit>
#include <QToolButton>

GraphicsViewComp::GraphicsViewComp(QWidget *parent)
    :QGraphicsView(parent)
{
    qRegisterMetaType<type_import>("type_import");

    QGraphicsScene * scene = new QGraphicsScene();
    QToolButton *toolPicWid =  new QToolButton();
    connect(toolPicWid, &QToolButton::clicked, this, [=](){
        emit s_clicked(import_pic);
    });
    toolPicWid->setObjectName("toolPicWid");
    toolPicWid->setText(tr("pic add"));
    toolPicWid->setFixedSize(185,185);

    QToolButton *toolGifWid =  new QToolButton();
    connect(toolGifWid, &QToolButton::clicked, this, [=](){
        emit s_clicked(import_gif);
    });

    toolGifWid->setObjectName("toolGifWid");
    toolGifWid->setText(tr("gif load"));
    toolGifWid->setFixedSize(185,185);

    QGraphicsWidget * toolBtnPic = (QGraphicsWidget *)scene->addWidget(toolPicWid);
    QGraphicsWidget * toolBtnGif = (QGraphicsWidget *)scene->addWidget(toolGifWid);

    QGraphicsLinearLayout *layout = new QGraphicsLinearLayout;
    layout->setContentsMargins(10,10,10,10);
    layout->setSpacing(10);
    layout->addItem(toolBtnPic);
    layout->addItem(toolBtnGif);
    layout->addStretch();


    m_GraWid = new QGraphicsWidget;
    QPalette pa = m_GraWid->palette();
    pa.setBrush(QPalette::Background, Qt::red);
    m_GraWid->setPalette(pa);
    m_GraWid->setLayout(layout);

    m_GraWid->setGeometry(10, 10, 50, 50);
    scene->addItem(m_GraWid);

    setScene(scene);

}

void GraphicsViewComp::paintEvent(QPaintEvent *event)
{
    m_GraWid->setGeometry(10, 10, 50, 50);
    QGraphicsView::paintEvent(event);
}

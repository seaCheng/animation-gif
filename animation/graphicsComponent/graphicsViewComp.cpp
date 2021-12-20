#include "graphicsViewComp.h"
#include <QGraphicsScene>
#include <QPushButton>
#include <QGraphicsWidget>
#include <QGraphicsLinearLayout>
#include <QTextEdit>

GraphicsViewComp::GraphicsViewComp(QWidget *parent)
    :QGraphicsView(parent)
{
    //
    QGraphicsScene * scene = new QGraphicsScene();
    QGraphicsWidget *textEdit = (QGraphicsWidget *)scene->addWidget(new QTextEdit);
    QGraphicsWidget *pushButton = (QGraphicsWidget *)scene->addWidget(new QTextEdit);

    QGraphicsLinearLayout *layout = new QGraphicsLinearLayout;
    layout->setContentsMargins(10,10,10,10);
    layout->setSpacing(10);
    layout->addItem(textEdit);
    layout->addItem(pushButton);
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

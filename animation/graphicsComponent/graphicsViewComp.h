#pragma once
#include <QGraphicsView>
class GraphicsViewComp :public QGraphicsView
{
    Q_OBJECT
public:

    GraphicsViewComp(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
private:

    QGraphicsWidget * m_GraWid = nullptr;
};

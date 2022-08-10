#pragma once
#include <QGraphicsView>
#include <QGraphicsScene>

#include <memory>

class PictureItem;
class PicGraphicsScene;
class GraphicsViewComp :public QGraphicsView
{
    Q_OBJECT
public:

    GraphicsViewComp(QWidget *parent = nullptr);
    void setPicItem(PictureItem * pItem);
protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
private:
    PicGraphicsScene * mscene = nullptr;
    PictureItem * pPicItem = nullptr;
};


class PicGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    PicGraphicsScene();
    void setPicItem(PictureItem * pItem)
    {
        mpItem = pItem;
    }
protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
private:
    PictureItem * mpItem = nullptr;
};

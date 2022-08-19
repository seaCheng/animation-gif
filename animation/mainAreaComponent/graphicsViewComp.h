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

    GraphicsViewComp(QGraphicsScene *scene, QWidget *parent = nullptr);
    void setPicItem(PictureItem * pItem);

    void setGifSize(const QSize & size);
    void refreashSize();
protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
private:
    //PicGraphicsScene * mscene = nullptr;
    std::shared_ptr<PicGraphicsScene> pScene;
    PictureItem * pPicItem = nullptr;

    QSize sizeInf;
};


class PicGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    PicGraphicsScene(QWidget * p);
    void setPicItem(PictureItem * pItem);

protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
private:
    PictureItem * mpItem = nullptr;

    QPixmap pic;

};

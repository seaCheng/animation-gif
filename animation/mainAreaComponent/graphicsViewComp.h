#pragma once
#include <QGraphicsView>
#include <QGraphicsScene>

#include <memory>

#include <QObject>
#include <QOpenGLWidget>

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

#include <QImage>


class PictureItem;
class PicGraphicsScene;

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit MyGLWidget(QWidget *parent = 0);

signals:

public slots:
    void initializeGL() Q_DECL_OVERRIDE;
    void resizeGL(int w, int h) Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    void setImage(const QImage &image);
    void initTextures();
    void initShaders();
private:
    QVector<QVector3D> vertices;
    QVector<QVector2D> texCoords;
    QOpenGLShaderProgram program;
    QOpenGLTexture *texture;
    QMatrix4x4 projection;

};


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

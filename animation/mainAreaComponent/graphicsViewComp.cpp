#include "graphicsViewComp.h"
#include "pictureItem.h"
#include <QGraphicsScene>
#include <QPushButton>
#include <QGraphicsWidget>
#include <QGraphicsLinearLayout>
#include <QTextEdit>
#include <QToolButton>
#include <QOpenGLWidget>
#include <QDebug>

#include <QGraphicsOpacityEffect>

MyGLWidget::MyGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{

}

void MyGLWidget::initTextures()
{
    // 加载 Avengers.jpg 图片
    texture = new QOpenGLTexture(QOpenGLTexture::Target2D);
    texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
    //重复使用纹理坐标
    //纹理坐标(1.1, 1.2)与(0.1, 0.2)相同
    texture->setWrapMode(QOpenGLTexture::Repeat);
    //设置纹理大小
    texture->setSize(this->width(), this->height());
    //分配储存空间
    texture->allocateStorage();
}

void MyGLWidget::initShaders()
{
    //纹理坐标
    texCoords.append(QVector2D(0, 1)); //左上
    texCoords.append(QVector2D(1, 1)); //右上
    texCoords.append(QVector2D(0, 0)); //左下
    texCoords.append(QVector2D(1, 0)); //右下
    //顶点坐标
    vertices.append(QVector3D(-1, -1, 1));//左下
    vertices.append(QVector3D(1, -1, 1)); //右下
    vertices.append(QVector3D(-1, 1, 1)); //左上
    vertices.append(QVector3D(1, 1, 1));  //右上
    QOpenGLShader *vshader = new QOpenGLShader(QOpenGLShader::Vertex, this);
    const char *vsrc =
            "attribute vec4 vertex;\n"
            "attribute vec2 texCoord;\n"
            "varying vec2 texc;\n"
            "void main(void)\n"
            "{\n"
            "    gl_Position = vertex;\n"
            "    texc = texCoord;\n"
            "}\n";
    vshader->compileSourceCode(vsrc);//编译顶点着色器代码

    QOpenGLShader *fshader = new QOpenGLShader(QOpenGLShader::Fragment, this);
    const char *fsrc =
            "uniform sampler2D texture;\n"
            "varying vec2 texc;\n"
            "void main(void)\n"
            "{\n"
            "    gl_FragColor = texture2D(texture,texc);\n"
            "}\n";
    fshader->compileSourceCode(fsrc); //编译纹理着色器代码

    program.addShader(vshader);//添加顶点着色器
    program.addShader(fshader);//添加纹理碎片着色器
    program.bindAttributeLocation("vertex", 0);//绑定顶点属性位置
    program.bindAttributeLocation("texCoord", 1);//绑定纹理属性位置
    // 链接着色器管道
    if (!program.link())
        close();
    // 绑定着色器管道
    if (!program.bind())
        close();
}

void MyGLWidget::initializeGL()
{
    initializeOpenGLFunctions(); //初始化OPenGL功能函数
    glClearColor(0, 0, 0, 0);    //设置背景为黑色
    glEnable(GL_TEXTURE_2D);     //设置纹理2D功能可用
    initTextures();              //初始化纹理设置
    initShaders();               //初始化shaders
}

void MyGLWidget::resizeGL(int w, int h)
{
    // 计算窗口横纵比
    qreal aspect = qreal(w) / qreal(h ? h : 1);
    // 设置近平面值 3.0, 远平面值 7.0, 视场45度
    const qreal zNear = 3.0, zFar = 7.0, fov = 45.0;
    // 重设投影
    projection.setToIdentity();
    // 设置透视投影
    projection.perspective(fov, static_cast<float>(aspect), zNear, zFar);
}

void MyGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清除屏幕缓存和深度缓冲
    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, -5.0);                   //矩阵变换
    program.enableAttributeArray(0);
    program.enableAttributeArray(1);
    program.setAttributeArray(0, vertices.constData());
    program.setAttributeArray(1, texCoords.constData());
    program.setUniformValue("texture", 0); //将当前上下文中位置的统一变量设置为value
    texture->bind();  //绑定纹理
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);//绘制纹理
    texture->release(); //释放绑定的纹理
    texture->destroy(); //消耗底层的纹理对象
    texture->create();
}

void MyGLWidget::setImage(const QImage &image)
{
    texture->setData(image); //设置纹理图像
    //设置纹理细节
    texture->setLevelofDetailBias(-1);//值越小，图像越清晰
    update();
}

/*--------------------------GraphicsViewComp-----------------------------*/
GraphicsViewComp::GraphicsViewComp(QGraphicsScene *scene, QWidget *parent)
    :QGraphicsView(scene, parent)
{
    QOpenGLWidget *widget =new QOpenGLWidget();
    setViewport(widget);
    viewport()->setContentsMargins(0,0,0,0);
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

            setFixedSize(iSceneWidth+2,iSceneHeigth+2);
            pScene->setSceneRect(0,0,iSceneWidth,iSceneHeigth);
        }
        pScene->update();
        update();
    }
}

void GraphicsViewComp::paintEvent(QPaintEvent *event)
{
    QGraphicsView::paintEvent(event);
    refreashSize();
}


void GraphicsViewComp::resizeEvent(QResizeEvent *event)
{
    refreashSize();
    QGraphicsView::resizeEvent(event);
}


void GraphicsViewComp::setPicItem(PictureItem * pItem)
{

    pPicItem = pItem;

    PicGraphicsScene * pScene = (PicGraphicsScene *)scene();
    if(pScene)
    {
        pScene->setPicItem(pItem);
        pScene->update();
    }
    update();
}


////////////////////////////////PicGraphicsScene ///////////////////////////////////
PicGraphicsScene::PicGraphicsScene(QWidget * p)
    :QGraphicsScene(p)
{
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
    //qDebug()<<"asMode:"<<(int)asMode;
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


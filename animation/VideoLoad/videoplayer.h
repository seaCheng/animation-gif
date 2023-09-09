
#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QMediaPlayer>
#include <QDialog>
#include <QVideoSink>
#include <QImage>

QT_BEGIN_NAMESPACE
class QAbstractButton;
class QSlider;
class QLabel;
class QUrl;
class QToolButton;
class QComboBox;
class AspectRatioPixmapLabel;
QT_END_NAMESPACE

#include <QSlider>


//自定义滑块类  实现类似安卓滑动条功能， 任意点击跳转 及 任意拖选
//滑动条为垂直时候， 请设置滑块handle为滑动条宽度的一半 否则可能出现点击不太准现象
//滑动条为水平时候， 请设置滑块handle为滑动条高度的一半
class CSlider : public QSlider {
    Q_OBJECT
public:
    //handleLen  0 为默认， 垂直slider:handle的高度 / 2， 水平slider: handle的宽度 / 2， 若设置了则以此值计算slider值偏移量
    CSlider(QWidget *parent = nullptr, uint16_t handleLen = 0);
    ~CSlider();
    //设置值 , bool bNotify 是否需要信号通知
    void SetSliderValue(int val, bool bNotify = false);

protected:
    //鼠标按下
    virtual void mousePressEvent(QMouseEvent * event);
    //鼠标拖动
    virtual void mouseMoveEvent(QMouseEvent * event);
    //鼠标松开
    virtual void mouseReleaseEvent(QMouseEvent * event);

private:
    //鼠标位置转换成滑动条的值
    int32_t MousePostionToSliderVal(const QPoint & pos);
//signals:

private:
    uint16_t m_handleLen; //滑块宽度
};


typedef enum {
    MODE_NONE,
    MODE_MOVE,
    MODE_RESIZE_LEFT,
    MODE_RESIZE_RIGHT,
} ZOOM_CHANGE_MODE;

class TimerThumbnailsItem : public  QWidget
{
    Q_OBJECT

public:
    TimerThumbnailsItem(QWidget *parent = nullptr);

    Q_INVOKABLE void updateZoom(int zoomStart, int zoomStop);
    //修改自原updateZoom，适配联动播放需求
    Q_INVOKABLE void updateDuration(qint64 startTime, qint64 endTime);
    //查看某个选区，小于minWidth参数则放大，配合标记拆分
    Q_INVOKABLE void viewSelection(qint64 startTime, qint64 endTime, int minWidth);
    //定位到某个时间点，配合时间联动
    Q_INVOKABLE void viewIndex(qint64 indexTime);
    Q_INVOKABLE qint64 zoomStartIndex();
    Q_INVOKABLE qint64 zoomStopIndex();
    Q_INVOKABLE qint64 totalIndex();
    Q_INVOKABLE  void thumbnailsRelatedMove(qreal posScale,ZOOM_CHANGE_MODE mode);
    Q_INVOKABLE  void thumbnailsRelatedPressed(qint64 startIndex,qint64 stopIndex);
    Q_INVOKABLE void setHandleBgColor(int r,int g,int b);
    Q_INVOKABLE void setHandleLRBgColor(int r,int g,int b);
    Q_INVOKABLE void setBgBorderColor(int r,int g,int b);

    QString transfer(qint64 indexTime);
    void setPos(qint64 ms)
    {
        m_indexPos = ms;
        update();
    }

    void setPlayStatus(bool bPlay)
    {
        m_play = bPlay;
        update();
    }
    Q_INVOKABLE virtual qint64 calcLineSampleIndexFromPosition(const QPoint &pos, bool isSelecting = false, bool isEnd = false);
    qint64 calcLinePos(qint64 indexTime);
protected:
    void mousePressEvent(QMouseEvent *evt) override;
    void mouseReleaseEvent(QMouseEvent *evt) override;
    void mouseMoveEvent(QMouseEvent *evt) override;

    void paintEvent(QPaintEvent *event) override;
    //void paint(QPainter *painter) override;

    ZOOM_CHANGE_MODE getHandShapeRect(const QPoint &pos, QRect &_rect);

    QRectF lightRect();

    int timeToX(qint64 ms);

    QRectF mainRect() const
    {
        QRectF mainRect = this->rect();
        return mainRect;
    }



signals:
    void sigTimeSectionChange();

private:
    void _mouseMove(const QPoint &pos);

protected:

    //起始时间毫秒
    qint64 m_startFrameIndex;
    qint64 m_stopFrameIndex;

    qint64 m_zoomStartIndex;
    qint64 m_zoomStopIndex;

    qint64 m_referenceZoomStartIndex;
    qint64 m_referenceZoomStopIndex;

    QPoint m_referencePos;

    qint64 m_indexPos = 0;
    bool m_play = false;

    bool m_zoomShown = true;
    bool m_lightRect;

    QColor m_handleBgColor = QColor(204,204,204);
    QColor m_handleLRBgColor = QColor(170,170,170);
    QColor m_bgBorderColor = QColor("#404040");  //背景底色边框


    ZOOM_CHANGE_MODE m_zoomChangeMode;

};

class VideoPlayer : public QDialog
{
    Q_OBJECT
public:
    VideoPlayer(QWidget *parent = nullptr);
    ~VideoPlayer();

    void setUrl(const QUrl &url);

    void reset();
    void initial();
signals:
    void s_insertImage(const QImage& img);
public slots:
    void openFile();
    void play();
    void stop();

protected:
    void showEvent(QShowEvent *event);
private slots:
    void mediaStateChanged(QMediaPlayer::PlaybackState state);
    void positionChanged(qint64 position);
    void durationChanged(qint64 duration);
    void setPosition(int position);
    void handleError();

private:
    QMediaPlayer* m_mediaPlayer;
    QAbstractButton *m_playButton;
    //QSlider *m_positionSlider;
    TimerThumbnailsItem * m_positionSlider;
    QLabel *m_errorLabel;

    QLabel * totalTime;
    QLabel * startTime;
    QLabel * endTime;
    QToolButton * importBtn;
    QToolButton * importStopBtn;
    QVideoSink m_videoSink;
    QComboBox * frameRateCombo;
    AspectRatioPixmapLabel * picLabel;
    bool bAdd = false;
};

#endif


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

class VideoPlayer : public QDialog
{
    Q_OBJECT
public:
    VideoPlayer(QWidget *parent = nullptr);
    ~VideoPlayer();

    void setUrl(const QUrl &url);

    void reset();
signals:
    void s_insertImage(const QImage& img);
public slots:
    void openFile();
    void play();
    void stop();

private slots:
    void mediaStateChanged(QMediaPlayer::PlaybackState state);
    void positionChanged(qint64 position);
    void durationChanged(qint64 duration);
    void setPosition(int position);
    void handleError();

private:
    QMediaPlayer* m_mediaPlayer;
    QAbstractButton *m_playButton;
    QSlider *m_positionSlider;
    QLabel *m_errorLabel;
    QToolButton * importBtn;
    QToolButton * importStopBtn;
    QVideoSink m_videoSink;
    QComboBox * frameRateCombo;
    AspectRatioPixmapLabel * picLabel;
    bool bAdd = false;
};

#endif

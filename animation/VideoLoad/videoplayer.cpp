﻿
#include "videoplayer.h"
#include "aspectRatioPixmapLabel.h"

#include <QtWidgets>
#include <QVideoWidget>
#include <QVideoFrame>

#include <QSlider>
#include <QLabel>
#include <QStyle>

CSlider::CSlider(QWidget * parent, uint16_t handleLen)
    : QSlider(parent), m_handleLen(handleLen) {
}

CSlider::~CSlider() {

}
//设置值 , bool bNotify 是否需要信号通知值滑块移动了
void CSlider::SetSliderValue(int val, bool bNotify) {
    setSliderPosition(val);
    if (bNotify)
        emit sliderMoved(val);
}
static bool bIsMove = false;
void CSlider::mousePressEvent(QMouseEvent * event) {
    if (event->button() != Qt::LeftButton)
        return;
    setSliderDown(true);
    bIsMove = true;
    int32_t pos = MousePostionToSliderVal(event->pos());
    if (pos != sliderPosition()) {
        setSliderPosition(pos);
        emit sliderMoved(pos);
    }
}


void CSlider::mouseMoveEvent(QMouseEvent * event) {
    //bIsMove = true;
    if(bIsMove)
    {
        int32_t pos = MousePostionToSliderVal(event->pos());
        if (pos != sliderPosition()) {
            setSliderPosition(pos);
            emit sliderMoved(pos);
        }
    }

}

void CSlider::mouseReleaseEvent(QMouseEvent * event) {
    setSliderDown(false);
    if (!isEnabled() || event->button() != Qt::LeftButton) {
        bIsMove = false;
        return;
    }

    if (bIsMove) {
        QSlider::mouseReleaseEvent(event);
        bIsMove = false;
    } else {
        int32_t pos = MousePostionToSliderVal(event->pos());
        if (pos != sliderPosition()) {
            setSliderPosition(pos);
            emit sliderMoved(pos);
        }
    }
}

//鼠标位置转换成滑动条的值
int32_t CSlider::MousePostionToSliderVal(const QPoint & pos) {
    int32_t duration = maximum() - minimum();
    int32_t sliderPos = 0;
    qreal mousePos = 0;
    uint16_t hanleLen = 0;
    if (Qt::Vertical == orientation()) {
        //设置了handle高度  则以m_handleLen为准， 如无设置 则以宽度一半为handleLen
        hanleLen = m_handleLen ? m_handleLen : width() / 2.0;
        mousePos = (qreal)(pos.y() - hanleLen / 2);
        if (0 > mousePos)
            mousePos = 0;
        else if (mousePos > height() - hanleLen)
            mousePos = (qreal)(height() - hanleLen);
        sliderPos = maximum() - duration * (mousePos / (height() - hanleLen));
    } else {
        //设置了handle宽度  则以m_handleLen为准， 如无设置 则以高度度一半为handleLen
        hanleLen = m_handleLen ? m_handleLen : height() / 2.0;
        mousePos = (qreal)(pos.x() - hanleLen / 2);
        if (0 > mousePos)
            mousePos = 0;
        else if (mousePos > width() - hanleLen)
            mousePos = (qreal)(width() - hanleLen);
        sliderPos = minimum() + duration * (mousePos / (width() - hanleLen));
    }
    return sliderPos;
}

VideoPlayer::VideoPlayer(QWidget *parent)
    : QDialog(parent)
{
    qRegisterMetaType<QImage>("QImage");

    m_mediaPlayer = new QMediaPlayer(this);
    picLabel = new AspectRatioPixmapLabel;
    m_mediaPlayer->setVideoSink(&m_videoSink);

    connect(&m_videoSink, &QVideoSink::videoFrameChanged, this, [&](const QVideoFrame &frame){

        QImage img = frame.toImage();
        if(img.isNull() == false)
        {
            if(bAdd)
            {
                emit s_insertImage(img);
            }

            picLabel->setPixmapLabel(QPixmap::fromImage(img));

        }else
        {
            qDebug()<<"img is null";
        }
    });

    m_playButton = new QPushButton;
    m_playButton->setEnabled(false);
    m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));

    connect(m_playButton, &QAbstractButton::clicked,
            this, &VideoPlayer::play);

    m_positionSlider = new CSlider();
    m_positionSlider->setObjectName("CSlider");
    m_positionSlider->setOrientation(Qt::Horizontal);
    m_positionSlider->setRange(0, 0);

    connect(m_positionSlider, &QAbstractSlider::sliderMoved,
            this, &VideoPlayer::setPosition);

    m_errorLabel = new QLabel;
    m_errorLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);

    QBoxLayout *controlLayout = new QHBoxLayout;
    controlLayout->setContentsMargins(0, 0, 0, 0);
    controlLayout->addWidget(m_playButton);
    controlLayout->addWidget(m_positionSlider);

    QBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(picLabel);
    layout->addLayout(controlLayout);
    layout->addWidget(m_errorLabel);

    setLayout(layout);

    connect(m_mediaPlayer, &QMediaPlayer::playbackStateChanged,
            this, &VideoPlayer::mediaStateChanged);
    connect(m_mediaPlayer, &QMediaPlayer::positionChanged, this, [&](qint64 position){

    });
    connect(m_mediaPlayer, &QMediaPlayer::durationChanged, this, &VideoPlayer::durationChanged);
    connect(m_mediaPlayer, &QMediaPlayer::errorChanged,
            this, &VideoPlayer::handleError);
}

VideoPlayer::~VideoPlayer()
{
}

void VideoPlayer::openFile()
{
    QFileDialog fileDialog(this);
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setWindowTitle(tr("Open Movie"));
    fileDialog.setDirectory(QStandardPaths::standardLocations(QStandardPaths::MoviesLocation).value(0, QDir::homePath()));
    if (fileDialog.exec() == QDialog::Accepted)
        setUrl(fileDialog.selectedUrls().constFirst());
}

void VideoPlayer::setUrl(const QUrl &url)
{
    m_errorLabel->setText(QString());
    setWindowFilePath(url.isLocalFile() ? url.toLocalFile() : QString());
    m_mediaPlayer->setSource(url);
    m_playButton->setEnabled(true);
}

void VideoPlayer::stop()
{
    m_mediaPlayer->stop();
}

void VideoPlayer::play()
{
    switch (m_mediaPlayer->playbackState()) {
    case QMediaPlayer::PlayingState:
        m_mediaPlayer->pause();
        break;
    default:
        m_mediaPlayer->play();
        break;
    }
}

void VideoPlayer::mediaStateChanged(QMediaPlayer::PlaybackState state)
{
    switch(state) {
    case QMediaPlayer::PlayingState:
        m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        break;
    default:
        m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        break;
    }
}

void VideoPlayer::positionChanged(qint64 position)
{
    m_positionSlider->setValue(position);
}

void VideoPlayer::durationChanged(qint64 duration)
{
    m_positionSlider->setRange(0, duration);
}

void VideoPlayer::setPosition(int position)
{
    m_mediaPlayer->setPosition(position);
    bAdd = false;
    m_mediaPlayer->play();
    m_mediaPlayer->pause();
    bAdd = true;
}

void VideoPlayer::handleError()
{
    if (m_mediaPlayer->error() == QMediaPlayer::NoError)
        return;

    m_playButton->setEnabled(false);
    const QString errorString = m_mediaPlayer->errorString();
    QString message = "Error: ";
    if (errorString.isEmpty())
        message += " #" + QString::number(int(m_mediaPlayer->error()));
    else
        message += errorString;
    m_errorLabel->setText(message);
}
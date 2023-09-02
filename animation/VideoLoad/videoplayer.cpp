
#include "videoplayer.h"

#include "dpi.h"

#include "aspectRatioPixmapLabel.h"

#include <QtWidgets>
#include <QVideoWidget>
#include <QVideoFrame>

#include <QCursor>
#include <QDateTime>
#include <QMouseEvent>

#include <QSlider>
#include <QLabel>
#include <QStyle>
#include <QComboBox>
#include <QRandomGenerator>

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
////////////////////////////////////////////////////////////////////////////////////////

#define MINI_RESIZE_FRAME_COUNT 24

TimerThumbnailsItem::TimerThumbnailsItem(QWidget *parent) :
    QWidget(parent),
    m_zoomStartIndex(0),
    m_zoomStopIndex(0),
    m_referenceZoomStartIndex(0),
    m_referenceZoomStopIndex(0),
    m_zoomShown(true),
    m_lightRect(false)
{

    m_zoomShown = true;
    //setAcceptHoverEvents(true);
     m_startFrameIndex = 0;
     m_stopFrameIndex = 4 * 60 * 1000 - 1;

     m_zoomStartIndex = 2 * 60 * 1000 - 1;
     m_zoomStopIndex = 2.5 * 60 * 1000 - 1;
}

void TimerThumbnailsItem::updateZoom(int zoomStart, int zoomStop)
{
    m_zoomStartIndex = zoomStart;
    m_zoomStopIndex = zoomStop;
    this->update();
}

void TimerThumbnailsItem::updateDuration(qint64 startTime, qint64 endTime)
{
    m_startFrameIndex = startTime;
    m_stopFrameIndex = endTime;
    update();
}

void TimerThumbnailsItem::viewSelection(qint64 startTime, qint64 endTime, int minWidth)
{
    //
}

void TimerThumbnailsItem::viewIndex(qint64 indexTime)
{
    //
}

qint64 TimerThumbnailsItem::zoomStartIndex()
{
    return m_zoomStartIndex;
}

qint64 TimerThumbnailsItem::zoomStopIndex()
{
    return m_zoomStopIndex;
}

void TimerThumbnailsItem::mousePressEvent(QMouseEvent *evt)
{

    m_referencePos = evt->pos();
    m_referenceZoomStartIndex = m_zoomStartIndex;
    m_referenceZoomStopIndex = m_zoomStopIndex;

    QRect arrowChangeRect;

    ZOOM_CHANGE_MODE mode = this->getHandShapeRect(evt->pos(), arrowChangeRect);
    //if(m_pressed)
    {
        m_zoomChangeMode = mode;
    }

    switch (mode) {
    case MODE_MOVE:
        this->setCursor(Qt::ClosedHandCursor);
        break;
    case MODE_RESIZE_LEFT:
        this->setCursor(Qt::SizeHorCursor);
        break;
    case MODE_RESIZE_RIGHT:
        this->setCursor(Qt::SizeHorCursor);
        break;
    case MODE_NONE:
    {
        this->setCursor(Qt::ArrowCursor);
        qint64 _zoomStartIndex = 0;
                qint64 _zoomStopIndex = 0;
                qint64 _lineSampleIndex = calcLineSampleIndexFromPosition(evt->pos());
                if (m_zoomStartIndex == m_startFrameIndex && m_zoomStopIndex == m_stopFrameIndex) {
                    break;
                }

                //qDebug()<<"_lineSampleIndex111"<<_lineSampleIndex;
                int zoomCount = (m_zoomStopIndex - m_zoomStartIndex + 1);
                if (_lineSampleIndex < m_zoomStartIndex) {
                            if (m_zoomStartIndex - zoomCount < m_startFrameIndex) {
                                _zoomStartIndex = m_startFrameIndex;
                                _zoomStopIndex = m_zoomStopIndex - (m_zoomStartIndex + 1);
                            } else {
                                _zoomStartIndex = m_zoomStartIndex - zoomCount;
                                _zoomStopIndex = m_zoomStopIndex - zoomCount;
                            }
                        } else if (_lineSampleIndex > m_zoomStopIndex) {
                            if (m_zoomStopIndex + zoomCount > m_stopFrameIndex) {
                                _zoomStartIndex = m_zoomStartIndex + (m_stopFrameIndex - m_zoomStopIndex);
                                _zoomStopIndex = m_stopFrameIndex;
                            } else {
                                _zoomStartIndex = m_zoomStartIndex + zoomCount;
                                _zoomStopIndex = m_zoomStopIndex + zoomCount;
                            }
                        }else {
                            _zoomStopIndex = m_zoomStopIndex;
                        }
                m_zoomStartIndex = _zoomStartIndex;
                m_zoomStopIndex = _zoomStopIndex;
                emit sigTimeSectionChange();

                update();

                break;
    }

    default:
        m_zoomChangeMode = MODE_NONE;
        break;
    }
}

void TimerThumbnailsItem::mouseReleaseEvent(QMouseEvent *evt)
{

    QRect arrowChangeRect;

    ZOOM_CHANGE_MODE mode = this->getHandShapeRect(evt->pos(), arrowChangeRect);

    switch (mode) {
    case MODE_MOVE:
        this->setCursor(Qt::OpenHandCursor);
        break;
    case MODE_RESIZE_LEFT:
        this->setCursor(Qt::SizeHorCursor);
        break;
    case MODE_RESIZE_RIGHT:
        this->setCursor(Qt::SizeHorCursor);
        break;
    case MODE_NONE:
        this->setCursor(Qt::ArrowCursor);
        break;
    default:
        this->setCursor(Qt::ArrowCursor);
        break;
    }
}

qint64 TimerThumbnailsItem::calcLinePos(qint64 indexTime)
{
    int realWidth = mainRect().width();
    qint64 dIndex = round(indexTime * realWidth /  m_stopFrameIndex);
    return dIndex;
}

void TimerThumbnailsItem::mouseMoveEvent(QMouseEvent *evt)
{
    QWidget::mouseMoveEvent(evt);
    this->_mouseMove(evt->pos());
}

void TimerThumbnailsItem::paintEvent(QPaintEvent *paint)
{
    QWidget::paintEvent(paint);

    //绘制缩略图背景边框
    QPainter painter(this);
    painter.setPen(m_bgBorderColor);
    painter.setBrush(Qt::SolidPattern);
    painter.drawRect(this->mainRect());

    //qDebug()<<"mainRect:"<<mainRect();

    QPen pen = painter.pen();

    qreal realWidth = this->mainRect().width();

    qreal startX = 0;
    qreal stopX = 0 + realWidth;
    //划区域
    if (m_zoomShown && m_zoomStopIndex - m_zoomStartIndex > 0 && m_zoomStopIndex != 0)
    {

        startX =  realWidth * (qreal(m_zoomStartIndex + 1) / m_stopFrameIndex);
                stopX =   realWidth * (qreal(m_zoomStopIndex + 1) / m_stopFrameIndex);

        QColor penColor = m_handleBgColor;
        if (m_lightRect) {
            penColor.setRgb(54,146,240);
        }

        pen.setColor(penColor);
        pen.setWidth(2);
        if(stopX - startX < 3.33)//最小宽度不要太小
        {
           stopX = startX + 3.33;
        }
        QRectF zoomRect(QPoint(startX, 1), QPoint(stopX, this->height() - 1));

        QLinearGradient gradient(zoomRect.topRight(), zoomRect.bottomRight());
        gradient.setColorAt(0, QColor(255, 255, 255, 80));
        gradient.setColorAt(1, QColor(255, 255, 255, 15));

        QBrush brush(gradient);

        painter.save();

        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(pen);
        painter.setBrush(brush);
        painter.drawRoundedRect(zoomRect, 4, 4);

        penColor.setAlpha(255);
        painter.setPen(m_handleLRBgColor);
        painter.setBrush(m_handleLRBgColor);

        qreal offset = 3;
        QRectF lRect(startX - offset - 1, 3, offset * 2, this->height() - 6);
        QRectF rRect(stopX - offset - 1, 3, offset * 2, this->height() - 6);

        QRectF lrRect = lRect.intersected(rRect);
        if (lrRect.isNull()) {

            painter.drawRoundedRect(lRect, 3, 3);

            painter.drawRoundedRect(rRect, 3, 3);

            painter.setRenderHint(QPainter::Antialiasing, false);
            QColor c(49, 49, 49);
            pen.setWidth(1);
            pen.setColor(c);
            painter.setBrush(c);
            painter.setPen(pen);

            painter.drawLine(lRect.x() + 1, lRect.y() + 3, lRect.x() + 1, lRect.bottom() - 4);
            painter.drawLine(lRect.x() + 4, lRect.y() + 3, lRect.x() + 4, lRect.bottom() - 4);

            painter.drawLine(rRect.x() + 1, rRect.y() + 3, rRect.x() + 1, rRect.bottom() - 4);
            painter.drawLine(rRect.x() + 4, rRect.y() + 3, rRect.x() + 4, rRect.bottom() - 4);

        }

        if(m_play)
        {
            pen.setColor(Qt::red);
            pen.setWidth(1);
            painter.setPen(pen);
            qreal linePosX = calcLinePos(m_indexPos);
            painter.drawLine(linePosX, 0, linePosX, this->height());

        }

        painter.restore();
    }


}

ZOOM_CHANGE_MODE TimerThumbnailsItem::getHandShapeRect(const QPoint &pos,QRect &_rect)
{
    qreal realWidth = this->mainRect().width();
    qreal startX = 0;
    qreal stopX = 0 + realWidth;

    //划区域
        if (m_zoomShown && m_zoomStopIndex - m_zoomStartIndex > 0 && m_zoomStopIndex != 0) {
            startX =  realWidth * (qreal(m_zoomStartIndex + 1) / m_stopFrameIndex);
                    stopX =  realWidth * (qreal(m_zoomStopIndex + 1) / m_stopFrameIndex);
        }
    qreal zoomWidth = 1 + m_zoomStopIndex - m_zoomStartIndex;

    QRect startRect, stopRect, moveRect;

    qreal offset = 4;
    startRect = QRect(startX - offset, 0, offset * 2, this->height());
    stopRect = QRect(stopX - offset, 0, offset * 2, this->height());
    moveRect = QRect(startX + offset, 0, stopX - startX - offset * 2, this->height());

    QRect lrRect = startRect.intersected(stopRect);
    if (!lrRect.isNull() || floor(stopX) == floor(startX)) {

        int leftWidth = 20;
        int midWidth = 20;
        int rgithWidth = 20;

        startRect = QRect(startX - leftWidth - midWidth / 2, 0, leftWidth, this->height());
        stopRect = QRect(stopX + midWidth / 2, 0, rgithWidth, this->height());

        moveRect = QRect(startX - midWidth / 2, 0, midWidth, this->height());
    }

//    qDebug() << "startRect" << startRect << "moveRect" << moveRect << "stopRect" << stopRect << "startX" << startX << floor(startX) << "stopX" << stopX << floor(stopX);

    ZOOM_CHANGE_MODE mode = MODE_NONE;

    if (startRect.contains(pos)) {
        startRect = moveRect;
        mode = MODE_RESIZE_LEFT;
    } else if (stopRect.contains(pos)) {
        stopRect = moveRect;
        mode = MODE_RESIZE_RIGHT;
    } else if (moveRect.contains(pos)) {
        _rect = moveRect;
        mode = MODE_MOVE;
    } else {
        mode = MODE_NONE;
    }

    //qDebug()<<"getHandShapeRect11:"<<mode;
    if ((mode == MODE_MOVE && (zoomWidth == 0 || zoomWidth >= m_stopFrameIndex - 1))) {
            return ZOOM_CHANGE_MODE::MODE_NONE;
        }

    return mode;
}

QRectF TimerThumbnailsItem::lightRect()
{
    qreal startX = 0;
    qreal stopX = 0 + mainRect().width();

    QRectF r(QPoint(startX - 3, 0), QPoint(stopX + 3, this->height()));

    return r;
}

QString TimerThumbnailsItem::transfer(qint64 indexTime)
{
    return QDateTime::fromMSecsSinceEpoch(indexTime, Qt::OffsetFromUTC).toString("hh:mm:ss.zzz");
}

int TimerThumbnailsItem::timeToX(qint64 ms)
{
    return 0;
}

void TimerThumbnailsItem::_mouseMove(const QPoint &pos)
{
    qreal realWidth = this->mainRect().width();

    QRect arrowChangeRect;
    QPoint mousePos = pos;

    ZOOM_CHANGE_MODE mode = this->getHandShapeRect(mousePos, arrowChangeRect);
    qreal zoomWidth = 1 + m_zoomStopIndex - m_zoomStartIndex;
    if (m_zoomChangeMode == MODE_MOVE && (zoomWidth == 0)) {
            return;
        }

    //qDebug() << mode;
    if (m_zoomChangeMode != MODE_NONE || (m_zoomChangeMode == MODE_NONE && mode != MODE_NONE) || lightRect().contains(pos)) {
        if (!m_lightRect) {
            m_lightRect = true;
            update();
        }
    } else {
        if (m_lightRect) {
//            qDebug() << "m_lightRect:" << m_lightRect;
            m_lightRect = false;
            update();
        }
    }

    if (m_zoomChangeMode == MODE_NONE)
    {
        switch (mode) {
        case MODE_MOVE:
            this->setCursor(Qt::OpenHandCursor);
            break;
        case MODE_RESIZE_LEFT:
            this->setCursor(Qt::SizeHorCursor);
            break;
        case MODE_RESIZE_RIGHT:
            this->setCursor(Qt::SizeHorCursor);
            break;
        case MODE_NONE:
            this->setCursor(Qt::ArrowCursor);
            break;
        default:
            m_zoomChangeMode = MODE_NONE;
            break;
        }
        return;
    }

    QPoint dPos = pos - m_referencePos;
    qreal dxLast = dPos.x() / realWidth;

    qint64 dIndex = round(dxLast * m_stopFrameIndex);

    if (m_zoomChangeMode == MODE_MOVE) {

            if (dIndex > 0 && dIndex + m_referenceZoomStopIndex > m_stopFrameIndex - 1) {
                dIndex = dIndex - (dIndex + m_referenceZoomStopIndex - (m_stopFrameIndex - 1));
            } else if (dIndex < 0 && dIndex + m_referenceZoomStartIndex < 0) {
                dIndex = dIndex + (0 - (dIndex + m_referenceZoomStartIndex));
            }
            m_zoomStartIndex = m_referenceZoomStartIndex + dIndex;
            m_zoomStopIndex = m_referenceZoomStopIndex + dIndex;

        } else if (m_zoomChangeMode == MODE_RESIZE_LEFT) {
            auto latestIndex = m_referenceZoomStartIndex + dIndex;
            if (latestIndex < 0) {
                latestIndex = 0;
            } else if (latestIndex > m_zoomStopIndex - 25) {
                latestIndex = m_zoomStopIndex - 25;
            }
            m_zoomStartIndex = latestIndex;

        } else if (m_zoomChangeMode == MODE_RESIZE_RIGHT) {
            auto latestIndex = m_referenceZoomStopIndex + dIndex;
            if (latestIndex < m_zoomStartIndex + 25) {
                latestIndex = m_zoomStartIndex + 25;
            } else if (latestIndex > m_stopFrameIndex - 1) {
                latestIndex = m_stopFrameIndex - 1;
            }
            m_zoomStopIndex = latestIndex;
        }

    emit sigTimeSectionChange();

    this->update();
}

void TimerThumbnailsItem::thumbnailsRelatedPressed(qint64 startIndex,qint64 stopIndex)
{
    m_referenceZoomStartIndex = startIndex;
    m_referenceZoomStopIndex = stopIndex;
    update();
}

void TimerThumbnailsItem::setHandleBgColor(int r, int g, int b)
{
    m_handleBgColor.setRgb(r,g,b);
    update();
}

void TimerThumbnailsItem::setHandleLRBgColor(int r, int g, int b)
{
    m_handleLRBgColor.setRgb(r,g,b);
    update();
}

void TimerThumbnailsItem::setBgBorderColor(int r, int g, int b)
{
    m_bgBorderColor.setRgb(r,g,b);
    update();
}

void TimerThumbnailsItem::thumbnailsRelatedMove(qreal posScale,ZOOM_CHANGE_MODE mode)
{
       // qDebug()<<"KKKKKKKK"<<mode<<posScale;
}

//FIXME:这里很重要，修改将返回值修改为结构体，返回该像素点所对应的起始和结束index
qint64 TimerThumbnailsItem::calcLineSampleIndexFromPosition(const QPoint &pos, bool isSelecting, bool isEnd)
{
    int realWidth = mainRect().width();
    qint64 dIndex = round(pos.x() * m_stopFrameIndex / realWidth);
    return dIndex;
}


////////////////////////////////////////////////////////////////////////////////////////
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
                int iIndex = QRandomGenerator::global()->bounded(1, 25);
                if(iIndex <= frameRateCombo->currentText().toInt())
                {
                     emit s_insertImage(img);
                }

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

    importBtn = new QToolButton();
    importBtn->setText(tr("Import"));
    connect(m_playButton, &QAbstractButton::clicked,
            this, &VideoPlayer::play);

    importStopBtn = new QToolButton();
    importStopBtn->setText(tr("Stop"));
    connect(importStopBtn, &QAbstractButton::clicked,
            this, [&]()
    {
        m_positionSlider->setEnabled(true);
        m_playButton->setEnabled(true);
        importBtn->setEnabled(true);
        frameRateCombo->setEnabled(true);
        bAdd = false;
        m_mediaPlayer->pause();
        m_positionSlider->setPlayStatus(false);
    });

    /*
    m_positionSlider = new CSlider();
    m_positionSlider->setObjectName("CSlider");
    m_positionSlider->setOrientation(Qt::Horizontal);
    m_positionSlider->setRange(0, 0);
    */
    m_positionSlider = new TimerThumbnailsItem();
    //m_positionSlider->setObjectName("CSlider");
    m_positionSlider->updateDuration(0, 0);
    m_positionSlider->setFixedHeight(25);
    m_positionSlider->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);


    /*
    connect(m_positionSlider, &QAbstractSlider::sliderMoved,
            this, [&](int position){

         m_positionSlider->blockSignals(true);
         setPosition(position);
         m_positionSlider->blockSignals(false);
    });
    */
    connect(m_positionSlider, &TimerThumbnailsItem::sigTimeSectionChange,
            [this](){

         setPosition(m_positionSlider->zoomStartIndex());

    });

    m_errorLabel = new QLabel;
    m_errorLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);

    QBoxLayout *controlLayout = new QHBoxLayout;
    controlLayout->setContentsMargins(20, 0, 20, 0);
    controlLayout->addWidget(m_playButton);
    controlLayout->addWidget(m_positionSlider);


    QLabel * lFrameRate = new QLabel;
    lFrameRate->setText(tr("Frame rate"));
    lFrameRate->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lFrameRate->setFixedWidth(DPI::getScaleUI(100));

    frameRateCombo = new QComboBox;
    frameRateCombo->setFixedWidth(DPI::getScaleUI(200));
    frameRateCombo->setEditable(false);
    for (int i = 1; i < 26; i++)
        frameRateCombo->addItem(QString().setNum(i));

    frameRateCombo->setCurrentIndex(9);

    QBoxLayout *controlImportLayout = new QHBoxLayout;
    controlImportLayout->setContentsMargins(0, 0, 0, 0);
    controlImportLayout->setSpacing(5);
    controlImportLayout->addStretch(1);
    controlImportLayout->addWidget(lFrameRate);
    controlImportLayout->addWidget(frameRateCombo);
    controlImportLayout->addWidget(importBtn);
    controlImportLayout->addWidget(importStopBtn);
    controlImportLayout->addStretch(1);

    connect(importBtn, &QToolButton::clicked,
            this, [&](){
        m_positionSlider->setEnabled(false);
        m_playButton->setEnabled(false);
        importBtn->setEnabled(false);
        frameRateCombo->setEnabled(false);
        bAdd = true;

        m_mediaPlayer->blockSignals(true);
        m_mediaPlayer->setPosition(m_positionSlider->zoomStartIndex());
        m_mediaPlayer->blockSignals(false);

        m_mediaPlayer->play();

        m_positionSlider->setPlayStatus(true);

    });

    QBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(picLabel);
    layout->addLayout(controlLayout);
    layout->addLayout(controlImportLayout);
    layout->addWidget(m_errorLabel);

    setLayout(layout);

    connect(m_mediaPlayer, &QMediaPlayer::playbackStateChanged,
            this, &VideoPlayer::mediaStateChanged);
    connect(m_mediaPlayer, &QMediaPlayer::positionChanged, this, [&](qint64 position)
    {
         m_positionSlider->setPos(position);
         if(position >= m_positionSlider->zoomStopIndex())
         {
             m_mediaPlayer->pause();
             m_positionSlider->setPlayStatus(false);
         }

    });
    connect(m_mediaPlayer, &QMediaPlayer::durationChanged, this, &VideoPlayer::durationChanged);
    connect(m_mediaPlayer, &QMediaPlayer::errorChanged,
            this, &VideoPlayer::handleError);
}

VideoPlayer::~VideoPlayer()
{
}

void VideoPlayer::reset()
{
    /*
    m_mediaPlayer->stop();
    m_positionSlider->setPlayStatus(false);
    m_mediaPlayer->setPosition(0);
    picLabel->setPixmapLabel(QPixmap());
    m_positionSlider->setEnabled(true);
    m_playButton->setEnabled(true);
    importBtn->setEnabled(true);
    m_positionSlider->setPos(0);
    m_mediaPlayer->setPlaybackRate(1.0);
    bAdd = false;
    */
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
    m_positionSlider->setPlayStatus(false);
}

void VideoPlayer::play()
{
    switch (m_mediaPlayer->playbackState()) {
    case QMediaPlayer::PlayingState:
        m_mediaPlayer->pause();
        m_positionSlider->setPlayStatus(false);
        break;
    default:
        m_mediaPlayer->blockSignals(true);
        m_mediaPlayer->setPosition(m_positionSlider->zoomStartIndex());
        m_mediaPlayer->blockSignals(false);
        m_mediaPlayer->play();
        m_positionSlider->setPlayStatus(true);
        break;
    }
}

void VideoPlayer::mediaStateChanged(QMediaPlayer::PlaybackState state)
{
    switch(state) {
    case QMediaPlayer::PlayingState:
        m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));

        break;
    case QMediaPlayer::PausedState:
    case QMediaPlayer::StoppedState:
        if(bAdd)
        {
            m_positionSlider->setEnabled(true);
            m_playButton->setEnabled(true);
            importBtn->setEnabled(true);
            frameRateCombo->setEnabled(true);
            bAdd = false;
        }
        m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        break;
    default:
        m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        break;
    }
}

void VideoPlayer::positionChanged(qint64 position)
{
    m_positionSlider->setPos(position);
}

void VideoPlayer::durationChanged(qint64 duration)
{
    m_positionSlider->updateDuration(0, duration);
    if(duration > 2000)
    {
        m_positionSlider->updateZoom(1000, duration-1000);
    }else
    {
        m_positionSlider->updateZoom(0, duration);
    }

}

void VideoPlayer::setPosition(int position)
{
    m_mediaPlayer->blockSignals(true);
    m_mediaPlayer->setPosition(position);
    m_mediaPlayer->blockSignals(false);
    bAdd = false;
    m_mediaPlayer->play();
    m_mediaPlayer->pause();
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

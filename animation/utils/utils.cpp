#include "utils.h"
#include <QString>
#include <QFileInfo>
#include <QFile>
#include <QJsonDocument>
#include <QCryptographicHash>
#include <QtDebug>
#include <QScreen>
#include <QWidget>
#include <QApplication>

QMutex Utils::mutex;
Utils* Utils::m_utils = NULL;

Utils::Utils(QObject *parent) : QObject(parent)
{
}

Utils *Utils::getInstance()
{
    if (!m_utils) {
        QMutexLocker locker(&mutex);
        if (!m_utils) {
            m_utils = new Utils();
        }
    }
    return m_utils;
}

QString Utils::createUuid() {
    QUuid uuid = QUuid::createUuid();
    QString rs = uuid.toString().toUpper();
    rs.replace("{", "");
    rs.replace("}", "");
    rs.replace("-", "");
    return rs;
}
QString Utils::timestamp()
{
    return QString("%1").arg(QDateTime::currentMSecsSinceEpoch());
}

QString Utils::canonicalFilePath(const QString filePath)
{
    QString tmp = filePath;
    if (tmp.startsWith("file:///")) {
        if (tmp.length()>10 && tmp.at(9) == ':' && tmp.at(10) == '/') {
            tmp = tmp.replace("file:///", "");
        } else {
            tmp = tmp.replace("file://", "");
        }
    }
    return tmp;
}

unsigned long Utils::fileSize(const QString filePath)
{
    QFileInfo fileInfo(canonicalFilePath(filePath));
    return fileInfo.size();
}

QString Utils::fileName(const QString filePath)
{
  return  QFileInfo(filePath).fileName();
}

QString Utils::currentDateTime()
{
  return QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz");
}

QString Utils::currentDateTimesecond()
{
  return QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
}

bool Utils::jsonValidity(const QString json)
{
  QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8());
  return !doc.isNull();
}

QString Utils::toDateTimeFromMSecs(qint64 msecs)
{
   QDateTime dateTime;
   dateTime.setMSecsSinceEpoch(msecs);
   return dateTime.toString("yyyy.MM.dd");
}

QString Utils::toTimesFromMSecs(qint64 msecs)
{
    QDateTime dateTime;
    dateTime.setMSecsSinceEpoch(msecs);
    return dateTime.toString("hh:mm:ss");
}

QString Utils::timingFull(int secs)
{
    QTime time(secs/3600, secs%3600/60, secs%60);
    return time.toString("hh:mm:ss");
}

QString Utils::getFileMd5(QString filePath)
{
    QFile localFile(filePath);

        if (!localFile.open(QFile::ReadOnly))
        {
            qDebug() << "file open error.";
            return 0;
        }

        QCryptographicHash ch(QCryptographicHash::Md5);

        quint64 totalBytes = 0;
        quint64 bytesWritten = 0;
        quint64 bytesToWrite = 0;
        quint64 loadSize = 1024 * 4;
        QByteArray buf;

        totalBytes = localFile.size();
        bytesToWrite = totalBytes;

        while (1)
        {
            if(bytesToWrite > 0)
            {
                buf = localFile.read(qMin(bytesToWrite, loadSize));
                ch.addData(buf);
                bytesWritten += buf.length();
                bytesToWrite -= buf.length();
                buf.resize(0);
            }
            else
            {
                break;
            }

            if(bytesWritten == totalBytes)
            {
                break;
            }
        }

        localFile.close();
        QByteArray md5 = ch.result();
        return md5.toHex().data();
}

int Utils::autoW(int beforeW)
{
    QScreen* screen = 0;
    QList<QScreen*> screens = QApplication::screens();
    if (screens.size() > 0)
    {
        screen = screens[0];
    }
    else
    {
        return beforeW;
    }
    QRect mm = screen->availableGeometry();
    int ScreenW = mm.width();
    int ScreenH = mm.height();
    float dpi = screen->logicalDotsPerInch();
    float rate = dpi / 96.0;
    if (rate < 1.1) {
        rate = rate;
    } else if (rate < 1.4) {
        rate = 1.25;
    } else if (rate < 1.6) {
        rate = 1.5;
    } else if (rate < 1.8) {
        rate = 1.75;
    } else {
        rate = 2.0;
    }
    int afterW = 0;
    float r1 = (ScreenW)/1380.0;
    //float r1 = (ScreenW)/1920.0;
    if(rate > 1.0)
    {
        if (ScreenW >= 1380)
        {
            afterW = beforeW;
        }
        else
        {
            afterW = (float)beforeW*r1;
        }
    }
    else
    {
        if (ScreenW >= 1380)
        {
            afterW = (float)beforeW*rate;
        }
        else
        {
            afterW = (float)beforeW*rate*r1;
        }
    }
    return afterW > 1 ? afterW:1;
}

int Utils::autoH(int beforeH)
{
    QScreen* screen = 0;
    QList<QScreen*> screens = QApplication::screens();
    if (screens.size() > 0)
    {
        screen = screens[0];
    }
    else
    {
        return beforeH;
    }
    QRect mm=screen->availableGeometry();
    int ScreenW = mm.width();
    int ScreenH = mm.height();
    float dpi = screen->logicalDotsPerInch();
    float rate = dpi / 96.0;
    if (rate < 1.1) {
        rate = rate;
    } else if (rate < 1.4) {
        rate = 1.25;
    } else if (rate < 1.6) {
        rate = 1.5;
    } else if (rate < 1.8) {
        rate = 1.75;
    } else {
        rate = 2.0;
    }
    int afterH = 0;
    float r1 = (ScreenH)/820.0;
    //float r1 = (ScreenH)/1030;
    if (rate > 1.0)
    {
        if (ScreenH >= 820)
        {
            afterH = beforeH;
        }
        else
        {
            afterH = (float)beforeH*r1;
        }
    }
    else
    {
        if (ScreenH >= 820)
        {
            afterH = (float)beforeH*rate;
        }
        else
        {
            afterH = (float)beforeH*rate*r1;
        }
    }

    return afterH > 1? afterH:1;
}

int Utils::autoF(int beforeF)
{
    int r1 = autoW(beforeF);
    int r2 = autoH(beforeF);
    int f = r1 < r2 ? r2 : r1;
    return f < 8 ? 8 : f;
}

void Utils::MoveToCenterP(QWidget * pWid, QWidget *pPWid)
{
    if(pWid == nullptr || pPWid == nullptr)
    {
        return;
    }

    QPoint globalPos = pPWid->mapToGlobal(QPoint(0,0));//父窗口绝对坐标
    int x =  (pPWid->width() - pWid->width()) / 2;//x坐标
    int y = (pPWid->height() - pWid->height()) / 2;//y坐标
    pWid->move(x, y + 50);//

}

void Utils::MoveToCenterNP(QWidget * pWid, QWidget *pPWid)
{
    if(pWid == nullptr || pPWid == nullptr)
    {
        return;
    }

    QPoint globalPos = pPWid->mapToGlobal(QPoint(0,0));//父窗口绝对坐标
    int x =  (pPWid->width() - pWid->width()) / 2;//x坐标
    int y = (pPWid->height() - pWid->height()) / 2;//y坐标

    globalPos.setX(x + globalPos.x());
    globalPos.setY(y + globalPos.y());

    pWid->move(globalPos);//

}

void Utils::MoveToCenter(QWidget * pWid)
{
     //
}

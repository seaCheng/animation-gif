#ifndef UTILS_H
#define UTILS_H

#include <QObject>
#include <QMutex>
#include <QThread>
#include <QMutexLocker>
#include <QDateTime>
#include <QUuid>
#include <QByteArray>
#include <QCryptographicHash>
#include <QFile>


class Utils : public QObject
{
    Q_OBJECT
public:
    static Utils* getInstance();
    Q_INVOKABLE QString createUuid();
    Q_INVOKABLE QString timestamp();
    Q_INVOKABLE QString canonicalFilePath(const QString filePath);
    Q_INVOKABLE unsigned long fileSize(const QString filePath);
    Q_INVOKABLE QString fileName(const QString filePath);
    Q_INVOKABLE QString currentDateTime();
    Q_INVOKABLE QString currentDateTimesecond();
    Q_INVOKABLE bool jsonValidity(const QString json);


    Q_INVOKABLE QString toDateTimeFromMSecs(qint64 msecs);
    Q_INVOKABLE QString toTimesFromMSecs(qint64 msecs);

    Q_INVOKABLE QString timingFull(int secs);

    //获取文件 md5
    Q_INVOKABLE QString getFileMd5(QString filePath);

    //得到自动适应屏幕分辨率和缩放系统
    Q_INVOKABLE int autoW(int beforeW);
    Q_INVOKABLE int autoH(int beforeH);
    //font pix size
    Q_INVOKABLE int autoF(int beforeF);
signals:
    void log(const QString& txt);

private:
    explicit Utils(QObject *parent = 0);
    static QMutex mutex;
    static Utils *m_utils;
};

#endif // UTILS_H

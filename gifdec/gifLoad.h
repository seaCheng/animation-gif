#ifndef HHH_gifload_HHH
#define HHH_gifload_HHH

#include <QObject>
#include <QMutex>


class GifLoad : public QObject
{
    Q_OBJECT
public:

    static GifLoad * instace()
    {
        static GifLoad g_gifLoad;
        return &g_gifLoad;
    }

    ~GifLoad();

    void initial();
    void setconnect();


signals:

private slots:

private:
    GifLoad(QObject *parent = nullptr);
    QThread  * m_subThread = nullptr;
};

#endif // TASKSUBMITLOG_H

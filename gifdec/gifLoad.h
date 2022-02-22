#ifndef HHH_gifload_HHH
#define HHH_gifload_HHH

#include <QObject>
#include <QMutex>
#include <vector>
#include <QPixmap>


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

    void startGifLoad(QString file);
    void slot_GifLoad(QString file);

    std::vector<QPixmap> getPixmaps()
    {
        return m_lstPixmap;
    }

signals:
    void s_GifLoad(QString file);
    void s_FinGifLoad();
private slots:

private:
    GifLoad(QObject *parent = nullptr);
    QThread  * m_subThread = nullptr;

    std::vector<QPixmap> m_lstPixmap;
};

#endif // TASKSUBMITLOG_H

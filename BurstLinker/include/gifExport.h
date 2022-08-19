#ifndef HHH_gifexport_HHH
#define HHH_gifexport_HHH

#include <QObject>
#include <QMutex>
#include <vector>
#include <QPixmap>


class GifExport : public QObject
{
    Q_OBJECT
public:

    static GifExport * instace()
    {
        static GifExport g_gifExport;
        return &g_gifExport;
    }

    ~GifExport();

    void initial();
    void setconnect();

    void setGifSize(const QSize &size)
    {
        iWidth = size.width();
        iHeigth = size.height();
    }

    void setGifSize(const int & width, const int & height)
    {
        iWidth = width;
        iHeigth = height;
    }

    void setGifPictures(const std::vector<QPixmap> & Pixmaps)
    {
        lstPixmap = Pixmaps;
    }
    void startGifExport(QString file);
    void slot_GifExport(QString file);
    void slot_GifExportMagick(QString file);


signals:
    void s_GifExport(QString file);
    void s_FinGifExport();
private slots:

private:
    GifExport(QObject *parent = nullptr);
    QThread  * m_subThread = nullptr;

    QString strFileName;
    std::vector<QPixmap> lstPixmap;
    int iWidth;
    int iHeigth;

};

#endif // TASKSUBMITLOG_H

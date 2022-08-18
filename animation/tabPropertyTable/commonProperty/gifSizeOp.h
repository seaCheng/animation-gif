#pragma once

#include <QObject>
#include <vector>

struct sizeInf
{
    QString uuid;
    QString name;
    int width = 360;
    int heigth = 240;
    bool bCustom = false;

    bool operator==(const sizeInf & inf)
    {
        return uuid == inf.uuid;
    }


    bool operator == (const QString &strUUid)
    {
        return (this->uuid == strUUid);
    }

};
class GifSizeOp : public QObject
{ 
    Q_OBJECT
public:


    static GifSizeOp * getInstance()
    {
        static GifSizeOp g_sGifSizeOp;
        return &g_sGifSizeOp;
    }
    void setConnect();

    void initial();

    void readData();
    void saveData();

    void initJosnData(QString file);

    void addSizeInf(const sizeInf & sInf);
    sizeInf getSizeInfBU(const QString & strUUid);
    void removeSize(const QString & strUUid);

    void setdata(int iwidth, int iheigth, const QString &struuid);
    void setName(const QString &name, const QString &struuid);

    std::vector<sizeInf> getSizeInf()
    {
        return lstsizeInf;
    }
signals:

    void s_insertItem(QString name, QString uuid);
protected:
    GifSizeOp(QObject *parent = 0);
public slots:

protected:

private:

    std::vector<sizeInf> lstsizeInf;
    int index = 0;
};

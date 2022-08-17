#pragma once

#include <QObject>
#include <vector>

struct sizeInf
{
    QString uuid;
    QString name;
    int width;
    int heigth;

    bool operator==(const sizeInf & inf)
    {
        return uuid == inf.uuid;
    }

};
class GifSizeOp : public QObject
{ 
    Q_OBJECT
public:
    GifSizeOp(QObject *parent = 0);
    void setConnect();

    void initial();

    void readData();

    void initJosnData(QString file);

    std::vector<sizeInf> getSizeInf()
    {
        return lstsizeInf;
    }
signals:
    //void s_clicked(type_import eType);
    void s_insertItem(QString name, QString uuid);
protected:

public slots:
    //void slot_selPicItem(PictureItem *);
protected:
    //void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;//重写重绘函数
private:

    std::vector<sizeInf> lstsizeInf;
    int index = 0;
};

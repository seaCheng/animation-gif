#pragma once

#include <QObject>
#include <map>

struct sizeInf
{
    QString name;
    int width;
    int heigth;

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

    std::map<std::string, sizeInf> getSizeInf()
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

    std::map<std::string, sizeInf> lstsizeInf;
    int index = 0;
};

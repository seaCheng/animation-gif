#include "gifSizeOp.h"
#include "QtCore/qjsonobject.h"
#include<QDebug>
#include <QCoreApplication>
#include <QDir>
#include <QUuid>
#include <QJsonArray>
#include <QJsonDocument>


GifSizeOp::GifSizeOp(QObject *parent)
    : QObject(parent)
{
    //initial();
    setConnect();
}

void GifSizeOp::setConnect()
{

}


void GifSizeOp::initJosnData(QString filePath)
{
    QJsonArray arry;
    QJsonObject object0
    {
        {"uuid", QUuid::createUuid().toByteArray().data()},
        {"name", QStringLiteral("88 * 31 pixel")},
        {"width", 88},
        {"heigth", 31}
    };

    arry.append(object0);

    QJsonObject object1
    {
        {"uuid", QUuid::createUuid().toByteArray().data()},
        {"name", QStringLiteral("230 * 33 pixel")},
        {"width", 230},
        {"heigth", 33}
    };

    arry.append(object1);

    QJsonObject object2
    {
        {"uuid", QUuid::createUuid().toByteArray().data()},
        {"name", QStringLiteral("234 * 60 pixel")},
        {"width", 234},
        {"heigth", 60}
    };

    arry.append(object2);

    QJsonObject object3
    {
        {"uuid", QUuid::createUuid().toByteArray().data()},
        {"name", QStringLiteral("336 * 280 pixel")},
        {"width", 336},
        {"heigth", 280}
    };

    arry.append(object3);

    QJsonObject object4
    {
        {"uuid", QUuid::createUuid().toByteArray().data()},
        {"name", QStringLiteral("468 * 60 pixel")},
        {"width", 468},
        {"heigth", 60}
    };

    arry.append(object4);

    QJsonObject object5
    {
        {"uuid", QUuid::createUuid().toByteArray().data()},
        {"name", QStringLiteral("(1:1) 60 * 60 pixel")},
        {"width", 60},
        {"heigth", 60}
    };

    arry.append(object5);

    QJsonObject object6
    {
        {"uuid", QUuid::createUuid().toByteArray().data()},
        {"name", QStringLiteral("(1:1) 75 * 75 pixel")},
        {"width", 75},
        {"heigth", 75}
    };

    arry.append(object6);

    QJsonObject object7
    {
        {"uuid", QUuid::createUuid().toByteArray().data()},
        {"name", QStringLiteral("(1:1) 120 * 120 pixel")},
        {"width", 120},
        {"heigth", 120}
    };

    arry.append(object7);

    QJsonObject object8
    {
        {"uuid", QUuid::createUuid().toByteArray().data()},
        {"name", QStringLiteral("(1:2) 120 * 240 pixel")},
        {"width", 120},
        {"heigth", 240}
    };

    arry.append(object8);

    QJsonObject object9
    {
        {"uuid", QUuid::createUuid().toByteArray().data()},
        {"name", QStringLiteral("(3:2) 360 * 240 pixel")},
        {"width", 360},
        {"heigth", 240}
    };

    arry.append(object9);

    QJsonObject object10
    {
        {"uuid", QUuid::createUuid().toByteArray().data()},
        {"name", QStringLiteral("(2:3) 640 * 960 pixel")},
        {"width", 640},
        {"heigth", 960}
    };

    arry.append(object10);

    QJsonObject object11
    {
        {"uuid", QUuid::createUuid().toByteArray().data()},
        {"name", QStringLiteral("(3:4) 360 * 480 pixel")},
        {"width", 360},
        {"heigth", 480}
    };

    arry.append(object11);

    QJsonObject object12
    {
        {"uuid", QUuid::createUuid().toByteArray().data()},
        {"name", QStringLiteral("(4:3) 120 * 90 pixel")},
        {"width", 120},
        {"heigth", 90}
    };

    arry.append(object12);

    QJsonObject object13
    {
        {"uuid", QUuid::createUuid().toByteArray().data()},
        {"name", QStringLiteral("(4:3) 640 * 480 pixel")},
        {"width", 640},
        {"heigth", 480}
    };

    arry.append(object13);

    QJsonObject object14
    {
        {"uuid", QUuid::createUuid().toByteArray().data()},
        {"name", QStringLiteral("(6:5) 180 * 150 pixel")},
        {"width", 180},
        {"heigth", 150}
    };

    arry.append(object14);

    QJsonObject object15
    {
        {"uuid", QUuid::createUuid().toByteArray().data()},
        {"name", QStringLiteral("(6:5) 300 * 250 pixel")},
        {"width", 300},
        {"heigth", 250}
    };

    arry.append(object15);

    QJsonObject object16
    {
        {"uuid", QUuid::createUuid().toByteArray().data()},
        {"name", QStringLiteral("(8:5) 640 * 400 pixel")},
        {"width", 640},
        {"heigth", 400}
    };

    arry.append(object16);

    QJsonDocument doc(arry);
    QString content = doc.toJson().data();

    QFile file(filePath);
    file.open(QIODeviceBase::ReadWrite);
    file.write(content.toStdString().c_str(), content.size());        // write to stderr
    file.close();

}

void GifSizeOp::readData()
{
    initial();
}

void GifSizeOp::saveData()
{
     QJsonArray arry;
     for(const auto &u : lstsizeInf)
     {

         QJsonObject object
         {
             {"bCustom", u.bCustom},
             {"uuid", u.uuid},
             {"name", u.name},
             {"width", u.width},
             {"heigth", u.heigth}
         };

         arry.append(object);
     }

     QJsonDocument doc(arry);
     QString content = doc.toJson().data();

     QString filePath = QCoreApplication::applicationDirPath() + "/config/gifSize.json";
     QFile file(filePath);
     file.open(QIODeviceBase::ReadWrite|QIODeviceBase::Truncate);
     file.write(content.toStdString().c_str(), content.size());        // write to stderr
     file.close();
}

void GifSizeOp::initial()
{
    QDir dir;
    if(!dir.exists("./config"))
    {
       dir.mkdir("./config");
    }

    QString filePath = QCoreApplication::applicationDirPath() + "/config/gifSize.json";
    if( !QFileInfo::exists(filePath))
    {
        initJosnData(filePath);

    }
    //读取json 数据
    {
        QFile file(filePath);
        file.open(QIODeviceBase::ReadOnly);
        QString content = file.readAll();
        file.close();

        QJsonDocument doc = QJsonDocument::fromJson(content.toStdString().c_str());
        if(doc.isArray())
        {
            QJsonArray arry = doc.array();
            for (int i = 0; i < arry.size(); i++)
            {
                QJsonObject obj = arry[i].toObject();
                sizeInf inf;
                inf.uuid = obj["uuid"].toString();
                inf.name = obj["name"].toString();
                inf.heigth = obj["heigth"].toInt();
                inf.width = obj["width"].toInt();
                inf.bCustom = obj["bCustom"].toBool();

                lstsizeInf.emplace_back(inf);


            }
        }
    }
}

void GifSizeOp::addSizeInf(const sizeInf & sInf)
{
    lstsizeInf.emplace_back(sInf);
}

sizeInf GifSizeOp::getSizeInfBU(const QString & strUUid)
{
    std::vector<sizeInf>::iterator it = std::find(lstsizeInf.begin(), lstsizeInf.end(), strUUid);
    if(it != lstsizeInf.end())
    {
        return *it;
    }else
    {
        return sizeInf();
    }
}

void GifSizeOp::setdata(int iwidth, int iheigth, const QString &struuid)
{
    std::vector<sizeInf>::iterator it = std::find(lstsizeInf.begin(), lstsizeInf.end(), struuid);
    if(it != lstsizeInf.end())
    {
        it->width = iwidth;
        it->heigth = iheigth;
    }
}

void GifSizeOp::setName(const QString &name, const QString &struuid)
{
    std::vector<sizeInf>::iterator it = std::find(lstsizeInf.begin(), lstsizeInf.end(), struuid);
    if(it != lstsizeInf.end())
    {
        it->name = name;
    }
}

void GifSizeOp::removeSize(const QString & strUUid)
{
    std::vector<sizeInf>::iterator it = std::find(lstsizeInf.begin(), lstsizeInf.end(), strUUid);
    if(it != lstsizeInf.end())
    {
        lstsizeInf.erase(it);
    }
}

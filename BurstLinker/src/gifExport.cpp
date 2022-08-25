#include "gifExport.h"

#include <QThread>
#include <QDebug>
#include <QImage>
#include <QCoreApplication>
#include <QDir>
#include <QBuffer>
#include <QPainter>

#include <iostream>

#include <vector>

#include <Magick++.h>
#include <list>

using namespace std;

using namespace Magick;

#include "BurstLinker.h"

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

using namespace blk;

GifExport::GifExport(QObject *parent)
{
    m_subThread = new QThread;
    moveToThread(m_subThread);
    m_subThread->start();

    initial();

    setconnect();
}

void GifExport::startGifExport(QString file)
{
    emit s_GifExport(file);

}

void GifExport::slot_GifExportMagick(QString file)
{
    std::vector<Magick::Image> lstImages;

    for(auto pix : lstPixmap)
    {
        QImage img = pix.toImage();
        QImage scalImage = img.scaled(QSize(iWidth, iHeigth),
                                      Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QImage desImage(iWidth, iHeigth, QImage::Format_ARGB32);
        desImage.fill(proInf->color);

        QRect rectPic(0, 0, scalImage.width(), scalImage.height());
        if (scalImage.width() < iWidth)
        {
            rectPic.setX((iWidth - scalImage.width()) / 2);
            rectPic.setY(0);
            rectPic.setWidth(scalImage.width());
            rectPic.setHeight(scalImage.height());
        }

        if (scalImage.height() < iHeigth)
        {
            rectPic.setX(0); rectPic.setY((iHeigth - scalImage.height()) / 2);
            rectPic.setWidth(scalImage.width());
            rectPic.setHeight(scalImage.height());
        }

        QPainter painter(&desImage);
        painter.drawImage(rectPic, scalImage);

        QByteArray bytes;
                 QBuffer buffer(&bytes);
                 buffer.open(QIODevice::WriteOnly);
                 desImage.save(&buffer, "PNG");


        Magick::Image imgMagick;

        Blob bi(bytes.data(), bytes.size());

        imgMagick.read(bi);
        imgMagick.alpha(true);
        imgMagick.animationDelay(proInf->delay);
        imgMagick.gifDisposeMethod(BackgroundDispose);
        lstImages.emplace_back(imgMagick);
    }

    writeImages(lstImages.begin(), lstImages.end(), file.toStdString().c_str(), true);
}

void GifExport::slot_GifExport(QString file)
{

    QuantizerType quantizerType = QuantizerType::Octree;
        DitherType ditherType = DitherType::No;
        int delay = 250;

        int startPosition = 1;

        int n;
        int imageSize = iWidth * iHeigth;

        BurstLinker burstLinker;
        if (!burstLinker.init(file.toStdString().c_str(), iWidth, iHeigth, 0, 4)) {
            std::cout << "GifEncoder init fail" << std::endl;
            return;
        }

        std::vector<std::vector<uint32_t >> tasks;
        int enableTransparency = 0;
        int isum = 0;
        for(auto pix : lstPixmap)
        {

            isum++;
            QImage img = pix.toImage();
            QImage scalImage = img.scaled(QSize(iWidth, iHeigth),
                                          Qt::KeepAspectRatio, Qt::SmoothTransformation);
            QRect rectPic(0, 0, scalImage.width(), scalImage.height());
            if (scalImage.width() < iWidth)
            {
                rectPic.setX((iWidth - scalImage.width()) / 2);
                rectPic.setY(0);
                rectPic.setWidth(scalImage.width());
                rectPic.setHeight(scalImage.height());
            }

            if (scalImage.height() < iHeigth)
            {
                rectPic.setX(0); rectPic.setY((iHeigth - scalImage.height()) / 2);
                rectPic.setWidth(scalImage.width());
                rectPic.setHeight(scalImage.height());
            }


            n = img.depth() / 8;
            std::vector<uint32_t> image;
            image.reserve(iWidth * iHeigth);

            int a = 255;
            int r = 0;
            int g = 0;
            int b = 0;
            for (uint32_t k = 0; k < iHeigth ; k++) {
                for (uint32_t j = 0; j < iWidth; j++) {

                    if(rectPic.contains(j,k) == false)
                    {
                        r = 255;
                        g = 255;
                        b = 255;
                        a = 255;
                        image.push_back(a << 24 | b << 16 | g << 8 | r);
                        continue;
                    }
                    int jRelative = j - rectPic.x();
                    int iRelative = k - rectPic.y();

                    if (n == 3) {

                    QColor color = QColor(scalImage.pixel(jRelative,iRelative));
                    r = color.red();
                    g = color.green();
                    b = color.blue();

                    } else if (n == 4) {
                        QColor color = QColor(scalImage.pixel(jRelative,iRelative));
                        r = color.red();
                        g = color.green();
                        b = color.blue();
                        a = color.alpha();
                    } else {
                        std::cout << "Unsupported images" << std::endl;
                        return;
                    }
                    if (enableTransparency == 0) {

                        enableTransparency = (n == 4 ? 1 : 0);
                    }
                    image.push_back(a << 24 | b << 16 | g << 8 | r);
                }
            }

            tasks.push_back(image);
        }

        int ignoreTranslucency = 0;
        int transparencyOption = ignoreTranslucency << 8 | enableTransparency;
        burstLinker.connect(tasks, delay, quantizerType, ditherType, transparencyOption, 0, 0);

        burstLinker.release();
        emit s_FinGifExport();

}

GifExport::~GifExport()
{
    m_subThread->quit();
    m_subThread->wait();
}

void GifExport::initial()
{
    Magick::InitializeMagick(NULL);
}

void GifExport::setconnect()
{
    connect(this, &GifExport::s_GifExport, this, &GifExport::slot_GifExportMagick);
}


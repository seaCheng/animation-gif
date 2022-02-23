#include "gifExport.h"

#include <QThread>
#include <QDebug>
#include <QImage>
#include <QCoreApplication>
#include <QDir>

#include <iostream>
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

void GifExport::slot_GifExport(QString file)
{
    QuantizerType quantizerType = QuantizerType::Octree;
        DitherType ditherType = DitherType::No;
        int delay = 10;

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
                                          Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            n = img.depth() / 8;
            std::vector<uint32_t> image;
            image.reserve(iWidth * iHeigth);
            int index = 0;
            int a = 255;
            int r = 0;
            int g = 0;
            int b = 0;
            for (uint32_t k = 0; k < iWidth; k++) {
                for (uint32_t j = 0; j < iHeigth; j++) {
                    if (n == 3) {

                    QColor color = QColor(scalImage.pixel(k,j));
                    r = color.red();
                    g = color.green();
                    b = color.blue();

                    } else if (n == 4) {
                        QColor color = QColor(scalImage.pixel(k,j));
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

}

void GifExport::setconnect()
{
    connect(this, &GifExport::s_GifExport, this, &GifExport::slot_GifExport);
}


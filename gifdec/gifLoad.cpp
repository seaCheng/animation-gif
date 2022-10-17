#include "gifLoad.h"
#include "gifdec.h"
#include "SDL.h"

#include <QThread>
#include <QDebug>
#include <QImage>
#include <QCoreApplication>

#include <vector>

#include <Magick++.h>
#include <list>

using namespace std;

using namespace Magick;

GifLoad::GifLoad(QObject *parent)
{
    m_subThread = new QThread;
    moveToThread(m_subThread);
    m_subThread->start();

    setconnect();
    initial();
}

void GifLoad::startGifLoad(QString file)
{
    m_lstPixmap.clear();
    emit s_GifLoad(file);
}

void GifLoad::slot_GifLoad(QString file)
{
    /*
    int sum = 0 ;
    Uint8 *color, *frame, *bgColor;
    SDL_Surface *surface;
    Uint32 pixel;
    void *addr;

    gd_GIF *gif = gd_open_gif(file.toStdString().c_str());
    if (!gif) {
            fprintf(stderr, "Could not open %s\n", "");
            return;
        }

    surface = SDL_CreateRGBSurface(0, gif->width, gif->height, 32, 0, 0, 0, 0);
        if (!surface) {
            SDL_Log("SDL_CreateRGBSurface() failed: %s", SDL_GetError());
            return;
        }

        bgColor = &gif->gct.colors[gif->bgindex * 3];

    frame = (uint8_t *)malloc(gif->width * gif->height * 3);
    while (gd_get_frame(gif))
    {
        sum++;
        SDL_LockSurface(surface);
        gd_render_frame(gif, frame);
        color = frame;

        for (int i = 0; i < gif->height; i++)
        {
            for (int j = 0; j < gif->width; j++) {
                if (!gd_is_bgcolor(gif, color))
                    pixel = SDL_MapRGB(surface->format, color[0], color[1], color[2]);
                else if (((i >> 2) + (j >> 2)) & 1)
                    pixel = SDL_MapRGB(surface->format, bgColor[0], bgColor[1], bgColor[2]);
                else
                    pixel = SDL_MapRGB(surface->format, bgColor[0], bgColor[1], bgColor[2]);

                color += 3;
            }
        }

        SDL_UnlockSurface(surface);

        QImage img((unsigned char*)frame, gif->width, gif->height, gif->width * 4, QImage::Format_ARGB32);
        m_lstPixmap.emplace_back(QPixmap::fromImage(img));

    }

    free(frame);
    gd_close_gif(gif);
    */


    list<Image> imageList;
    readImages( &imageList, file.toStdString().c_str());
    for(auto it : imageList)
    {
        Magick::Blob bo;
        it.write(&bo);

        const QByteArray imageData1((char*)(bo.data()),bo.length());
        QPixmap item1p;
        item1p.loadFromData(imageData1);
        m_lstPixmap.emplace_back(item1p);
    }

    emit s_FinGifLoad();
}

GifLoad::~GifLoad()
{
    m_subThread->quit();
    m_subThread->wait();
}

void GifLoad::initial()
{

}

void GifLoad::setconnect()
{
    connect(this, &GifLoad::s_GifLoad, this, &GifLoad::slot_GifLoad);
}


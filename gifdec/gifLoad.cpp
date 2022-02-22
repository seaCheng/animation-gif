#include "gifLoad.h"
#include "gifdec.h"
#include "SDL.h"

#include <QThread>
#include <QDebug>
#include <QImage>
#include <QCoreApplication>

GifLoad::GifLoad(QObject *parent)
{
    m_subThread = new QThread;
    moveToThread(m_subThread);
    m_subThread->start();

    setconnect();
    initial();
    int sum = 0 ;
    Uint8 *color, *frame;
    SDL_Surface *surface;
    Uint32 pixel;
    void *addr;
    QString strPath = QCoreApplication::applicationDirPath()  + "/test.gif";

    /*
    color = &gif->gct.colors[gif->bgindex * 3];
    SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], 0x00);
    */

    gd_GIF *gif = gd_open_gif(strPath.toStdString().c_str());
    if (!gif) {
            fprintf(stderr, "Could not open %s\n", "");
            return;
        }

    surface = SDL_CreateRGBSurface(0, gif->width, gif->height, 32, 0, 0, 0, 0);
        if (!surface) {
            SDL_Log("SDL_CreateRGBSurface() failed: %s", SDL_GetError());
            return;
        }
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
                    pixel = SDL_MapRGB(surface->format, 0x7F, 0x7F, 0x7F);
                else
                    pixel = SDL_MapRGB(surface->format, 0x00, 0x00, 0x00);

                //addr = (Uint32 *)surface->pixels + (i * surface->pitch + j * sizeof(pixel));
                memcpy(color, &pixel, sizeof(pixel));
                color += 3;
            }
        }

        SDL_UnlockSurface(surface);

        QImage img((unsigned char*)frame, gif->width, gif->height, gif->width * 3, QImage::Format_RGB888);
        img.save(QString("%1.png").arg(sum));

    }

    free(frame);
    gd_close_gif(gif);


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
    //
}


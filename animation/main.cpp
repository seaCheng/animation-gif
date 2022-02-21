#include "mainwindow.h"

#include "SDL.h"

#include "QtSingleApplication"
#include "AWLogger.h"
#include "AWLoggerFactory.h"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION

#include <QApplication>
#include <QResource>
#include <QFile>
#include <QDebug>


#include "gifdec.h"



long long currentTimeMs() {
    std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> tp = std::chrono::time_point_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now());
    auto tmp = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch());
    auto timestamp = tmp.count();
    return timestamp;
}


int main(int argc, char *argv[])
{
    QtSingleApplication app(QLatin1String("D9CF0D0E-7784-4181-9D91-EBE77E2F1C39-animation++"),argc, argv);
    if(app.isRunning())
    {
        app.sendMessage("raise_window_noop", 2000); //2s后激活前个实例
        return 0;
    }

    QCoreApplication::addLibraryPath("./");
    app.setApplicationName("Animation");

    QFont font;
    font.setPointSize(12);
    #if defined (_WIN32) || defined (WIN32)
        font.setFamily("微软雅黑");
    #else
        font.setFamily("PingFangSC-Regular");
    #endif
    app.setFont(font);

    bool bReg = QResource::registerResource(QCoreApplication::applicationDirPath() + "/resource/instance.rcc");
    QFile file(":/resource/wndcss.qss");
    bool bRst = file.open(QFile::ReadOnly);
    qDebug()<<"bReg"<<bReg<<"bRst:"<<bRst;
    app.setStyleSheet(file.readAll());
    file.close();
    /*

    std::shared_ptr<AMLog::AMLogger> logger = AMLog::AWLoggerFactory::instace()->CreateLogger("outputMessage1");
    logger->info("app launch...");
    logger->info("bReg:{}, bRst:{}", bReg, bRst);
    MainWindow w;
    w.show();
    */

    SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Surface *surface;
        SDL_Texture *texture;
        SDL_Event event;
        gd_GIF *gif;
        char title[32] = {0};
        Uint8 *color, *frame;
        void *addr;
        int i, j;
        Uint32 pixel;
        int ret, paused, quit;
        Uint32 t0, t1, delay, delta;

        if (argc != 2) {
            fprintf(stderr, "usage:\n  %s gif-file\n", argv[0]);
            return 1;
        }
        gif = gd_open_gif("test.gif");
        if (!gif) {
            fprintf(stderr, "Could not open %s\n", argv[1]);
            return 1;
        }
        frame = (Uint8 *)malloc(gif->width * gif->height * 3);
        if (!frame) {
            fprintf(stderr, "Could not allocate frame\n");
            return 1;
        }
        if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0) {
            SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
            return 1;
        }
        if (SDL_CreateWindowAndRenderer(gif->width, gif->height, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
            SDL_Log("Couldn't create window and renderer: %s", SDL_GetError());
            return 1;
        }
        snprintf(title, sizeof(title) - 1, "GIF %dx%d %d colors",
                 gif->width, gif->height, gif->palette->size);
        SDL_SetWindowTitle(window, title);
        color = &gif->gct.colors[gif->bgindex * 3];
        SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], 0x00);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
        surface = SDL_CreateRGBSurface(0, gif->width, gif->height, 32, 0, 0, 0, 0);
        if (!surface) {
            SDL_Log("SDL_CreateRGBSurface() failed: %s", SDL_GetError());
            return 1;
        }
        paused = 0;
        quit = 0;
        while (1) {
            while (SDL_PollEvent(&event) && !quit) {
                if (event.type == SDL_QUIT)
                    quit = 1;
                if (event.type == SDL_KEYDOWN) {
                    if (event.key.keysym.sym == SDLK_q)
                        quit = 1;
                    else if (event.key.keysym.sym == SDLK_SPACE)
                        paused = !paused;
                }
            }
            if (quit) break;
            if (paused) {
                SDL_Delay(10);
                continue;
            }
            t0 = SDL_GetTicks();
            ret = gd_get_frame(gif);
            if (ret == -1)
                break;
            SDL_LockSurface(surface);
            gd_render_frame(gif, frame);
            color = frame;
            for (i = 0; i < gif->height; i++) {
                for (j = 0; j < gif->width; j++) {
                    if (!gd_is_bgcolor(gif, color))
                        pixel = SDL_MapRGB(surface->format, color[0], color[1], color[2]);
                    else if (((i >> 2) + (j >> 2)) & 1)
                        pixel = SDL_MapRGB(surface->format, 0x7F, 0x7F, 0x7F);
                    else
                        pixel = SDL_MapRGB(surface->format, 0x00, 0x00, 0x00);
                    addr = (char *)surface->pixels + (i * surface->pitch + j * sizeof(pixel));
                    memcpy(addr, &pixel, sizeof(pixel));
                    color += 3;
                }
            }
            SDL_UnlockSurface(surface);
            texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_RenderCopy(renderer, texture, NULL, NULL);
            SDL_RenderPresent(renderer);
            SDL_DestroyTexture(texture);
            t1 = SDL_GetTicks();
            delta = t1 - t0;
            delay = gif->gce.delay * 10;
            delay = delay > delta ? delay - delta : 1;
            SDL_Delay(delay);
            if (ret == 0)
                gd_rewind(gif);
        }
        SDL_FreeSurface(surface);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        free(frame);
        gd_close_gif(gif);

    //app.setActivationWindow(&w,1);

    return app.exec();
}


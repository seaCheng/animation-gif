#include "mainwindow.h"

#include "QtSingleApplication"
#include "AWLogger.h"
#include "AWLoggerFactory.h"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION

#include <QApplication>
#include <QResource>
#include <QFile>
#include <QDebug>

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


    std::shared_ptr<AMLog::AMLogger> logger = AMLog::AWLoggerFactory::instace()->CreateLogger("outputMessage1");
    logger->info("app launch...");
    logger->info("bReg:{}, bRst:{}", bReg, bRst);
    MainWindow w;
    w.show();

    app.setActivationWindow(&w,1);

    return app.exec();
}

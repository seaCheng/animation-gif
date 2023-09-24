#include "mainwindow.h"

#include "QtSingleApplication"
#include "AWLogger.h"
#include "AWLoggerFactory.h"
#include "utils.h"
#include "dpi.h"

#include <iostream>

#include <QApplication>
#include <QResource>
#include <QFile>
#include <QDebug>
#include <QTranslator>


int main(int argc, char *argv[])
{
    qDebug()<<"app launch...";
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
    font.setFamily("Microsoft YaHei");
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

    QLocale::Language language;
    QLocale locale;
    QString language_value;
    language = locale.language();

    if ( language == (int)QLocale::Chinese )
    {
        language_value = QString(":/language/animationGif_ch.qm");
    }else
    {
        language_value = QString(":/language/animationGif_en_US.qm");
    }

    QTranslator translator;
    translator.blockSignals(true);
    translator.load(language_value);
    translator.blockSignals(false);
    app.installTranslator(&translator);

    MainWindow mainWindow;
    mainWindow.setGeometry(DPI::getScaleUI(100), DPI::getScaleUI(100),
                           DPI::getScaleUI(1400), DPI::getScaleUI(900));
    mainWindow.show();

    app.setActivationWindow(&mainWindow,1);

    return app.exec();
}


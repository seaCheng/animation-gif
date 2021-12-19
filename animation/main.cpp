#include "mainwindow.h"

#include "QtSingleApplication"
#include "AWLogger.h"
#include "AWLoggerFactory.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QtSingleApplication app(QLatin1String("D9CF0D0E-7784-4181-9D91-EBE77E2F1C39-animation++"),argc, argv);
    if(app.isRunning())
    {
        app.sendMessage("raise_window_noop", 2000); //2s后激活前个实例
        return 0;
    }

    std::shared_ptr<AMLog::AMLogger> logger = AMLog::AWLoggerFactory::instace()->CreateLogger("outputMessage1");
    logger->info("app launch...");

    MainWindow w;
    w.show();

    app.setActivationWindow(&w,1);

    return app.exec();
}

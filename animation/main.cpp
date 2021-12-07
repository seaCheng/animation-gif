#include "mainwindow.h"

#include "./../QtSingleApplication/QtSingleApplication"
#include "./../AMLogger/AWLogger.h"
#include "./../AMLogger/AWLoggerFactory.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QtSingleApplication app(QLatin1String("D9CF0D0E-7784-4181-9D91-EBE77E2F1C39-animation++"),argc, argv);
    if(app.isRunning())
    {
        //app.sendMessage("show",3000);
        //app.sendMessage("raise_window_noop");
        app.sendMessage("raise_window_noop", 2000); //2s后激活前个实例
        return 0;
    }



    std::shared_ptr<AMLog::AMLogger> logger = AMLog::AWLoggerFactory::instace()->CreateLogger("outputMessage1");
    logger->info("app launch...");

    MainWindow w;
    w.show();

    //app.setActivationWindow(&w,false);
    app.setActivationWindow(&w,1);
    //QObject::connect(&app, &QtSingleApplication::messageReceived, &w, &MainWindow::slot_show);

    return app.exec();
}

#include "mainwindow.h"
#include "ui_animationMW.h"

#include "QtSingleApplication"
#include "graphicsscenecontroller.h"
#include "samplemodel.h"
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::animationMW)
{
    setObjectName("MainWindow");
    ui->setupUi(this);
    ui->scrollAreaPicScal->setObjectName("scrollAreaPicScal");
    ui->scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");

    SampleModel * samp = new SampleModel();
    GraphicsSceneController * ctl = new GraphicsSceneController(samp, ui->scrollAreaWidgetContents);
    ConnectableItem *item =  samp->insertConnectableItem("ConnectableItem", 50,50);

    for(int i = 0; i < 100; i++)
    {
        samp->insertConnectableItem("ConnectableItem", 50,50);
        samp->insertConnectableItem("ConnectableItem", 50,50);
        samp->insertConnectableItem("ConnectableItem", 50,50);
    }

}

void MainWindow::slot_show(const QString &message)
{
    setVisible(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}


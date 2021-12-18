#include "mainwindow.h"
#include "ui_animationMW.h"

#include "./../QtSingleApplication/QtSingleApplication"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::animationMW)
{
    ui->setupUi(this);



}

void MainWindow::slot_show(const QString &message)
{
    setVisible(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}


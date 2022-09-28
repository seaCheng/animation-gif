#include "mainwindow.h"
#include "ui_animationMW.h"

#include "QtSingleApplication"
#include "modelController.h"
#include "pictureModel.h"

#include "mvvm/commands/undostack.h"
#include "mvvm/model/modelutils.h"
#include "picScaleComp.h"
#include "mainAreaView.h"
#include "propertyAreaView.h"
#include "gifLoad.h"
#include "mvvm/model/sessionitem.h"

#include "gifExport.h"

#include <QAction>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QSplitter>
#include <QUndoStack>
#include <QRandomGenerator>
#include <QToolBar>
#include <QFileDialog>
#include <QScrollArea>
#include <QSplitter>

#include <vector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::animationMW)
{
    m_toolBar = addToolBar("test");
    setObjectName("MainWindow");
    ui->setupUi(this);
    ui->scrollAreaPicScal->setObjectName("scrollAreaPicScal");
    ui->scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");

    //添加页面显示
    mainArea = new MainAreaView;
    QHBoxLayout *layout = new QHBoxLayout();
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(mainArea);
    ui->leftView->setLayout(layout);

    //添加tab 属性页
    propertyArea = new PropertyAreaView;

    mainArea->setGifCommpro(propertyArea->getGifCommpro());
    GifExport::instace()->setGifCommpro(propertyArea->getGifCommpro());

    mainArea->setWhiteBoardPro(propertyArea->getWhiteBoardInf(), pro_none);

    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(propertyArea);

    QHBoxLayout *prolayout = new QHBoxLayout();
    prolayout->setContentsMargins(0,0,0,0);
    prolayout->addWidget(scrollArea);
    ui->rightView->setLayout(prolayout);

    //添加 spiltter
    splitter = new QSplitter;
    splitter->setObjectName("topSplitter");
    splitter->setHandleWidth(2);
    ui->topView->layout()->removeWidget(ui->leftView);
    ui->topView->layout()->removeWidget(ui->rightView);

    splitter->addWidget(ui->leftView);
    ui->leftView->setMinimumWidth(450);
    splitter->addWidget(ui->rightView);
    ui->rightView->setMaximumWidth(450);
    ui->topView->layout()->addWidget(splitter);

    m_model = new PictureModel();
    ctl = new ModelController(m_model, ui->scrollAreaWidgetContents);

    setupUndoRedoActions();

    setConnect();

}

void MainWindow::slot_show(const QString &message)
{
    setVisible(true);
}

void MainWindow::slot_save()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                QDir::homePath() + "/untitled.json",
                                tr("Save ( *.json)"));

        if(!fileName.isNull())
        {
            m_model->saveToFile(fileName.toStdString());
        }
}

void MainWindow::slot_load()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                     QDir::homePath(),
                                                     tr("Json (*.json)"));
    if(!fileName.isNull())
    {
        slot_clear();
        m_model->loadFromFile(fileName.toStdString());
    }
}

void MainWindow::slot_export()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Export gif"),
                                QDir::homePath() + "/untitled.gif",
                                tr("Save ( *.gif)"));

        if(fileName.isNull())
        {
            return;
        }

    std::vector<ModelView::SessionItem*> vecSession = m_model->rootItem()->children();
    std::vector<QPixmap> vecPix;
    for (auto item : vecSession)
    {

        vecPix.emplace_back(((PictureItem *)item)->pic());
    }

    GifExport::instace()->setGifSize(propertyArea->getGifCommpro()->width, propertyArea->getGifCommpro()->heigth);
    GifExport::instace()->setGifPictures(vecPix);
    GifExport::instace()->startGifExport(fileName);

}

void MainWindow::slot_import(type_import type)
{
    switch (type) {

    case type_import::import_pic:
        {
            slot_add();
            break;
        }

     case type_import::import_gif:
        {
            slot_importGif();
            break;
        }

    default:
        {

        }

    }
}

void MainWindow::slot_FinimportGif()
{
    std::vector<QPixmap> lstPix = GifLoad::instace()->getPixmaps();
    m_model->insertConnectItems(lstPix);
}

void MainWindow::slot_importGif()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                     QDir::homePath(),
                                                     tr("Gif (*.gif)"));
    if(!fileName.isNull())
    {
        GifLoad::instace()->startGifLoad(fileName);
    }
}

void MainWindow::slot_clear()
{
    m_model->eraseConnectItems(m_model->rootItem()->children());
}

void MainWindow::slot_add()
{
    QFileDialog::Options options =  QFileDialog::ReadOnly;
    QStringList files = QFileDialog::getOpenFileNames(
                             this,
                             "Select one or more files to open",
                             QDir::homePath()/*"/home"*/,
                             "Images (*.bmp *.jpg *.png *.ico)", nullptr, options);

    m_model->insertConnectItems(files);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setConnect()
{
    connect(mainArea, &MainAreaView::s_clicked, this, &MainWindow::slot_import);
    connect(ui->scrollAreaWidgetContents, &PicScaleViewComp::s_selPicItem, [&](PictureItem * item){
        mainArea->slot_selPicItem(item);
    });

    connect(propertyArea, &PropertyAreaView::s_commproFresh, [&](){
         mainArea->setGifCommpro(propertyArea->getGifCommpro());
         GifExport::instace()->setGifCommpro(propertyArea->getGifCommpro());
    });

    connect(propertyArea, &PropertyAreaView::s_whiteBoardProFresh, [&](refreashProType type){
         mainArea->setWhiteBoardPro(propertyArea->getWhiteBoardInf(), type);

    });

    connect(propertyArea, &PropertyAreaView::s_sceneItemInsert, [&](DiagramType type){

         mainArea->start_insertSceneItem(type);
    });

    connect(propertyArea, &PropertyAreaView::s_saveToCurrentPicture, [&](){
         mainArea->saveToCurrentPictire();
         //mainArea->clearsSceneItems();
    });

    connect(propertyArea, &PropertyAreaView::s_saveToAllPictures, [&](){

        std::vector<ModelView::SessionItem*> vecSession = m_model->rootItem()->children();
        std::vector<QPixmap> vecPix;
        for (auto item : vecSession) {

            mainArea->slot_selPicItem((PictureItem *)item);
            mainArea->saveToCurrentPictire();
        }

        mainArea->clearsSceneItems();

    });

    connect(propertyArea, &PropertyAreaView::s_clearGraphicsItems, [&](){
         mainArea->clearsSceneItems();
    });

    connect(GifLoad::instace(), &GifLoad::s_FinGifLoad, this, &MainWindow::slot_FinimportGif);

}

void MainWindow::setupUndoRedoActions()
{
    //load file
    auto loadAction = new QAction("Load project", this);
    connect(loadAction, &QAction::triggered, this, &MainWindow::slot_load
            );
    m_toolBar->addAction(loadAction);

    //save file
    auto saveAction = new QAction("Save project", this);
    connect(saveAction, &QAction::triggered, this, &MainWindow::slot_save);
    m_toolBar->addAction(saveAction);

    m_toolBar->addSeparator();

    //add pic
    auto addAction = new QAction("Add picture", this);
    connect(addAction, &QAction::triggered, this, &MainWindow::slot_add);
    m_toolBar->addAction(addAction);

    // insert empty
    auto insertAction = new QAction("Insert empty", this);
    connect(insertAction, &QAction::triggered,
            [this]()
    {
        m_model->insertEmptyPicture();
    });
    m_toolBar->addAction(insertAction);

    // delete action
    auto deleteAction = new QAction("Remove picture", this);
    connect(deleteAction, &QAction::triggered,
            [this]()
    {
        PicScaleComp * pic =  ui->scrollAreaWidgetContents->getSelItem();
        if(pic)
        {
            m_model->eraseConnectItem(pic->getPictureItem());
        }
    });
    m_toolBar->addAction(deleteAction);

    auto clearAction = new QAction("Clear picture", this);
    connect(clearAction, &QAction::triggered, this, &MainWindow::slot_clear);
    m_toolBar->addAction(clearAction);

    m_toolBar->addSeparator();

    // undo action
    auto undoAction = new QAction("Undo", this);
    connect(undoAction, &QAction::triggered, [this]() { ModelView::Utils::Undo(*m_model); });
    undoAction->setDisabled(true);
    m_toolBar->addAction(undoAction);

    // redo action
    auto redoAction = new QAction("Redo", this);
    connect(redoAction, &QAction::triggered, [this]() { ModelView::Utils::Redo(*m_model); });
    redoAction->setDisabled(true);
    m_toolBar->addAction(redoAction);

    m_toolBar->addSeparator();

    //export gif
    auto exportAction = new QAction("Export gif", this);
    connect(exportAction, &QAction::triggered, this, &MainWindow::slot_export);
    m_toolBar->addAction(exportAction);

    m_toolBar->addSeparator();

    // enable/disable undo/redo actions when there is something to undo
    if (m_model && m_model->undoStack()) {
        auto can_undo_changed = [undoAction, this]() {
            undoAction->setEnabled(m_model->undoStack()->canUndo());
        };
        connect(ModelView::UndoStack::qtUndoStack(m_model->undoStack()), &QUndoStack::canUndoChanged,
                can_undo_changed);
        auto can_redo_changed = [this, redoAction]() {
            redoAction->setEnabled(m_model->undoStack()->canRedo());
        };

        connect(ModelView::UndoStack::qtUndoStack(m_model->undoStack()), &QUndoStack::canUndoChanged,
                can_redo_changed);
    }
}

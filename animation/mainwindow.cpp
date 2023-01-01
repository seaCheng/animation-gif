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
#include "OSXHideTitleBar.h"

#include "gifExport.h"
#include "videoplayer.h"
#include "utils.h"

#include "dpi.h"

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
#include <QTimer>
#include <QScrollBar>

#include <vector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::animationMW)
{
    //setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    setWindowTitle(QStringLiteral("AnimationGif++"));
    setObjectName("MainWindow");
    ui->setupUi(this);
    ui->scrollAreaPicScal->setObjectName("scrollAreaPicScal");
    ui->scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");

    #ifdef Q_OS_MAC
    OSXHideTitleBar::HideTitleBar(winId());
    #endif

    m_toolBar = new QToolBar(this);
    m_toolBar->setStyleSheet("background-color:rgba(255,255,255, 0);");
    m_toolBar->setFloatable(false);
    m_toolBar->setMovable(false);

    #ifdef Q_OS_MAC
    ui->titleBar->setFixedHeight(DPI::getScaleUI(65));
    ui->titleLayout->addStretch(DPI::getScaleUI(1));
    ui->titleLayout->addWidget(m_toolBar);
    ui->titleLayout->setContentsMargins(DPI::getScaleUI(2),DPI::getScaleUI(35),DPI::getScaleUI(2),DPI::getScaleUI(2));
    ui->titleLayout->addSpacing(DPI::getScaleUI(5));
    #endif

    #ifdef Q_OS_WIN32
    ui->titleLayout->addWidget(m_toolBar);
    ui->titleLayout->addStretch(DPI::getScaleUI(1));
    ui->titleBar->setFixedHeight(DPI::getScaleUI(45));
    ui->titleLayout->setContentsMargins(DPI::getScaleUI(2),DPI::getScaleUI(10),DPI::getScaleUI(2),DPI::getScaleUI(2));
    ui->titleLayout->setSpacing(DPI::getScaleUI(10));
    #endif

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
    ui->scrollAreaWidgetContents->refreashDelayTime(propertyArea->getGifCommpro()->delay);

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
    splitter->setHandleWidth(DPI::getScaleUI(2));
    ui->topView->layout()->removeWidget(ui->leftView);
    ui->topView->layout()->removeWidget(ui->rightView);

    splitter->addWidget(ui->leftView);
    ui->leftView->setMinimumWidth(DPI::getScaleUI(450));
    splitter->addWidget(ui->rightView);
    ui->rightView->setMaximumWidth(DPI::getScaleUI(450));
    ui->topView->layout()->addWidget(splitter);

    player = new VideoPlayer;
    m_model = new PictureModel();
    m_modelDeal = new ModelWrape();
    m_modelDeal->setModel(m_model);
    ctl = new ModelController(m_model, ui->scrollAreaWidgetContents);

    runTimer = new QTimer();
    runTimer->setInterval(40);
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
            m_modelDeal->saveToFile(fileName.toStdString());
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
        m_modelDeal->loadFromFile(fileName.toStdString());
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
    case type_import::import_video:
       {
           slot_importVideos();
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
    m_modelDeal->insertConnectItemsVec(lstPix);
}

void MainWindow::slot_importVideos()
{

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                     QDir::homePath()
                                                     );
    if(!fileName.isNull())
    {
        player->setGeometry(DPI::getScaleUI(100),DPI::getScaleUI(100), DPI::getScaleUI(650), DPI::getScaleUI(400));
        player->reset();
        player->setUrl(QUrl::fromLocalFile(fileName));
        Utils::MoveToCenterP(player, this);
        player->exec();
        player->stop();
    }
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

    std::vector<ModelView::SessionItem*> vecItems = m_model->rootItem()->children();
    std::vector<ModelView::SessionItem*>::reverse_iterator iter = vecItems.rbegin();
    for (; iter != vecItems.rend(); ++iter)
    {
        m_modelDeal->eraseConnectItem(*iter);
        QCoreApplication::processEvents();
    }
}

void MainWindow::slot_add()
{
    QFileDialog::Options options =  QFileDialog::ReadOnly;
    QStringList files = QFileDialog::getOpenFileNames(
                             this,
                             "Select one or more files to open",
                             QDir::homePath()/*"/home"*/,
                             "Images (*.bmp *.jpg *.png *.ico)", nullptr, options);

    for(auto u: files)
    {
        m_modelDeal->insertConnectItemImg(QPixmap(u));
        QCoreApplication::processEvents();
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setConnect()
{
    //[signal] void QAbstractSlider::rangeChanged(int min, int max)
    connect(ui->scrollAreaPicScal->horizontalScrollBar(), &QScrollBar::rangeChanged, [&](int min, int max){

        slot_refreashPicItemView();

    });
    connect(mainArea, &MainAreaView::s_clicked, this, &MainWindow::slot_import);
    connect(ui->scrollAreaWidgetContents, &PicScaleViewComp::s_selPicItem, [&](PictureItem * item){
        mainArea->slot_selPicItem(item);

    });

    connect(propertyArea, &PropertyAreaView::s_commproFresh, [&](){
         mainArea->setGifCommpro(propertyArea->getGifCommpro());
         ui->scrollAreaWidgetContents->refreashDelayTime(propertyArea->getGifCommpro()->delay);
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
         if(ui->scrollAreaWidgetContents->getSelItem())
         {
             mainArea->slot_selPicItem(ui->scrollAreaWidgetContents->getSelItem()->getPictureItem());
         }

    });

    connect(propertyArea, &PropertyAreaView::s_saveToAllPictures, [&](){

        std::vector<ModelView::SessionItem*> vecSession = m_model->rootItem()->children();
        std::vector<QPixmap> vecPix;
        for (auto item : vecSession)
        {
            mainArea->slot_selPicItem((PictureItem *)item);
            mainArea->saveToCurrentPictire();
            QCoreApplication::processEvents();
        }

        mainArea->clearsSceneItems();
        if(ui->scrollAreaWidgetContents->getSelItem())
        {
            mainArea->slot_selPicItem(ui->scrollAreaWidgetContents->getSelItem()->getPictureItem());
        }
    });

    connect(propertyArea, &PropertyAreaView::s_clearGraphicsItems, [&](){
         mainArea->clearsSceneItems();
    });

    connect(player, &VideoPlayer::s_insertImage, [&](const QImage& img){
         if(img.isNull() == false)
         {
             QPixmap pix;
             pix.convertFromImage(img);
             m_modelDeal->insertConnectItemImg(pix);

         }else
         {
             qDebug()<<"s_insertImage null image...";
         }

    });

    connect(GifLoad::instace(), &GifLoad::s_FinGifLoad, this, &MainWindow::slot_FinimportGif);

    connect(runTimer, &QTimer::timeout, [&](){

        if(!ui->scrollAreaWidgetContents->getSelItem())
        {
            return;
        }

        PictureItem * curItem = ui->scrollAreaWidgetContents->getSelItem()->getPictureItem();
        int index = curItem->tagRow().row;
        if(index < m_model->rootItem()->childrenCount() - 1)
        {
            index = curItem->tagRow().next().row;
            curItem = (PictureItem *)m_model->rootItem()->getItem(curItem->tagRow().tag, index);
        }else
        {
            index = 0;
            curItem = (PictureItem *)m_model->rootItem()->getItem(curItem->tagRow().tag, index);
        }

        PicScaleComp * selComp = ui->scrollAreaWidgetContents->getSelPicByItem(curItem);
        if(selComp)
        {
            selComp->s_clicked(true);
        }
    });

    connect(ui->scrollAreaPicScal->horizontalScrollBar(), &QScrollBar::sliderMoved, this, &MainWindow::slot_refreashPicItemView);

}

void MainWindow::setupUndoRedoActions()
{

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
        m_modelDeal->insertEmptyPicture();
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
            m_modelDeal->eraseConnectItem(pic->getPictureItem());

        }
    });
    m_toolBar->addAction(deleteAction);

    auto clearAction = new QAction("Clear picture", this);
    connect(clearAction, &QAction::triggered, this, &MainWindow::slot_clear);
    m_toolBar->addAction(clearAction);

    m_toolBar->addSeparator();

    auto runAction = new QAction("Run", this);
    connect(runAction, &QAction::triggered, this, [=](){

        if(runTimer->isActive())
        {
            runAction->setText(tr("Run"));
            runTimer->stop();
        }else
        {
            runAction->setText(tr("Stop"));
            runTimer->setInterval(propertyArea->getGifCommpro()->delay);
            runTimer->start();
        }

    });
    m_toolBar->addAction(runAction);

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

void MainWindow::slot_refreashPicItemView()
{
    int pos = ui->scrollAreaPicScal->horizontalScrollBar()->sliderPosition();
    if(m_model->rootItem()->childrenCount() > 200)
    {
        int max = ui->scrollAreaPicScal->horizontalScrollBar()->maximum();
        int num = m_model->rootItem()->childrenCount() * pos / max;
        int minRan = num;
        int maxRan = 200 + num;
        maxRan = std::min(m_model->rootItem()->childrenCount()-1, maxRan);
        minRan = std::max(0, minRan);
        if(maxRan == m_model->rootItem()->childrenCount()-1)
        {
            minRan = maxRan - 200;
        }

        std::vector<ModelView::SessionItem*> vecSession = m_model->rootItem()->children();

        for(auto u : vecSession)
        {
            if(u->tagRow().row < minRan || u->tagRow().row > maxRan)
            {
                PicScaleComp * picComp = ui->scrollAreaWidgetContents->getSelPicByItem((PictureItem *)u);
                if(picComp)
                {
                   picComp->setVisible(false);
                }
            }else
            {
                PicScaleComp * picComp = ui->scrollAreaWidgetContents->getSelPicByItem((PictureItem *)u);
                if(picComp)
                {
                   picComp->setVisible(true);
                }
            }

        }

    }else
    {
        std::vector<ModelView::SessionItem*> vecSession = m_model->rootItem()->children();
        for(auto u : vecSession)
        {
            PicScaleComp * picComp = ui->scrollAreaWidgetContents->getSelPicByItem((PictureItem *)u);
            if(picComp)
            {
               picComp->setVisible(true);
            }

        }
    }
}

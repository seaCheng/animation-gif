#include "mainwindow.h"
#include "ui_animationMW.h"

#include "QtSingleApplication"
#include "graphicsscenecontroller.h"
#include "samplemodel.h"

#include "mvvm/commands/undostack.h"
#include "mvvm/model/modelutils.h"
#include "picScaleComp.h"

#include <QAction>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QSplitter>
#include <QUndoStack>
#include <QRandomGenerator>
#include <QToolBar>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::animationMW)
{
    m_toolBar = addToolBar("test");
    setObjectName("MainWindow");
    ui->setupUi(this);
    ui->scrollAreaPicScal->setObjectName("scrollAreaPicScal");
    ui->scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");

    m_model = new SampleModel();
    GraphicsSceneController * ctl = new GraphicsSceneController(m_model, ui->scrollAreaWidgetContents);

    setupUndoRedoActions();

    for(int i = 0; i < 5; i++)
    {
        int iIndex = QRandomGenerator::global()->bounded(11) + 1;
        //m_model->insertConnectableItem("ConnectableItem", 50,50, QPixmap(QString(":/images/%1.bmp").arg(iIndex)));
    }

}

void MainWindow::slot_show(const QString &message)
{
    setVisible(true);
}

void MainWindow::slot_save()
{
          //保存名称为path + image（？） + 日期年y月M日d时h分m秒s
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
        m_model->loadFromFile(fileName.toStdString());
    }
}

void MainWindow::slot_add()
{
    QString fileName = QFileDialog::getOpenFileName(
                    this, tr("open image file"),
                    "./", tr("Image files(*.bmp *.jpg *.png );;All files (*.*)"));

        if(fileName.isEmpty())
        {
            return;

        }

     m_model->insertConnectableItem("ConnectableItem", 50,50, QPixmap(fileName));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupUndoRedoActions()
{

    //load file
    auto loadAction = new QAction("Load", this);
    connect(loadAction, &QAction::triggered, this, &MainWindow::slot_load
            );
    m_toolBar->addAction(loadAction);

    //save file
    auto saveAction = new QAction("Save", this);
    connect(saveAction, &QAction::triggered, this, &MainWindow::slot_save);
    m_toolBar->addAction(saveAction);

    //add pic
    auto addAction = new QAction("Add", this);
    connect(addAction, &QAction::triggered, this, &MainWindow::slot_add);
    m_toolBar->addAction(addAction);

    // delete action
    auto deleteAction = new QAction("Remove selected", this);
    connect(deleteAction, &QAction::triggered,
            [this]()
    {
        PicScaleComp * pic =  ui->scrollAreaWidgetContents->getSelItem();
        if(pic)
        {
            m_model->eraseConnectItem(pic->connectableItem());
        }
    });
    m_toolBar->addAction(deleteAction);


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

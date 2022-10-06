#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "emptyAreaView.h"
#include "framelesswindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class animationMW; }
QT_END_NAMESPACE

class QToolBar;
class PictureModel;
class MainAreaView;
class PropertyAreaView;
class QSplitter;
class ModelController;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setupUndoRedoActions();

    void setConnect();
public slots:

    void slot_show(const QString &message);
    void slot_add();
    void slot_clear();
    void slot_importGif();
    void slot_FinimportGif();

    void slot_save();
    void slot_load();

    void slot_import(type_import type);
    void slot_export();

private:
    Ui::animationMW *ui;
    QToolBar* m_toolBar{nullptr};
    PictureModel * m_model = nullptr;
    MainAreaView * mainArea = nullptr;
    PropertyAreaView * propertyArea = nullptr;
    QSplitter * splitter = nullptr;

    ModelController * ctl = nullptr;
};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class animationMW; }
QT_END_NAMESPACE

class QToolBar;
class SampleModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setupUndoRedoActions();
public slots:

    void slot_show(const QString &message);
    void slot_add();
    void slot_save();
    void slot_load();

private:
    Ui::animationMW *ui;
    QToolBar* m_toolBar{nullptr};
    SampleModel * m_model = nullptr;
};
#endif // MAINWINDOW_H

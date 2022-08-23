#pragma once
#include <QDialog>
#include <QFrame>

#include "gifSizeOp.h"

#include <memory>

class QComboBox;
class QListView;
class QLineEdit;
class QStringListModel;
class QStandardItemModel;
class QTabBar;
class QSpinBox;

class QColorFrame :public QFrame
{
    Q_OBJECT
public:
    QColorFrame();
    void setGifColor(const QColor & color);
signals:
    void s_clicked();
protected:
    void paintEvent(QPaintEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    bool event( QEvent *e) override;

public slots:

private:

    QColor gifColor = Qt::white;
};
class customSizeOp : public QDialog
{
    Q_OBJECT
public:
    customSizeOp(QWidget *parent = 0);
    void setConnect();

    void initial();
signals:
    void s_dataFrash();
    void s_customData(QString uuid);
protected:
    void paintEvent(QPaintEvent *e) override;
    virtual void showEvent(QShowEvent *event) override;
public slots:


protected:

private:
    QListView * view = nullptr;
    QStandardItemModel * stModel = nullptr;

    QPushButton * addBtn = nullptr;
    QPushButton * subBtn = nullptr;
    QPushButton * okBtn = nullptr;
    QPushButton * cancelBtn = nullptr;
    QLineEdit * edWidth = nullptr;
    QLineEdit * edHeigth = nullptr;

    int icount = 0;
};

class QRadioButton;
class CommonPropertyView : public QFrame
{ 
    Q_OBJECT
public:
    CommonPropertyView(QWidget *parent = 0);
    void setConnect();

    void initial();

    void refreashGifSize();
    QSize getGifSize();

signals:
    void s_sizeFresh(QSize);

protected:
    void paintEvent(QPaintEvent *e) override;
public slots:


protected:

private:
    QComboBox * comSize = nullptr;
    QRadioButton * hRadioBtn = nullptr;
    QRadioButton * vRadioBtn = nullptr;

    QComboBox * comFill = nullptr;
    QColorFrame * fColor = nullptr;
    QTabBar * speedBar = nullptr;

    QSpinBox * timeSpinBox = nullptr;
    QSpinBox * secondSpinBox = nullptr;


    //自定义uuid
    QString uuid;
    int prIndex = 0;
    QSize gifSize{360,240};
    std::unique_ptr<customSizeOp> custOP;
};

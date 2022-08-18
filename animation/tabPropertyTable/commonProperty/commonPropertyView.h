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
    QLineEdit * edWidth = nullptr;
    QLineEdit * edHeigth = nullptr;

    int icount = 0;
};

class CommonPropertyView : public QFrame
{ 
    Q_OBJECT
public:
    CommonPropertyView(QWidget *parent = 0);
    void setConnect();

    void initial();
signals:
    //void s_clicked(type_import eType);

protected:
    void paintEvent(QPaintEvent *e) override;
public slots:
    //void slot_selPicItem(PictureItem *);

protected:
    //void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;//重写重绘函数
    //bool eventFilter(QObject *obj, QEvent *event) override;
private:
    QComboBox * comSize = nullptr;

    //自定义uuid
    QString uuid;
    int prIndex = 0;

    std::unique_ptr<customSizeOp> custOP;
};

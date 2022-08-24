#pragma once
#include <QDialog>
#include <QFrame>

#include "gifSizeOp.h"
#include "propertyAreaView.h"

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
class QLabel;
class QButtonGroup;
class CommonPropertyView : public QFrame
{ 
    Q_OBJECT
public:
    CommonPropertyView(std::shared_ptr<propertyInf> proInf, QWidget *parent = 0);
    void setConnect();

    void initial();

    void refreashGifSize();
    std::shared_ptr<propertyInf> getGifCommpro();

signals:
    void s_commproFresh();

protected:
    void paintEvent(QPaintEvent *e) override;
public slots:


protected:

private:
    QComboBox * comSize = nullptr;
    QRadioButton * hRadioBtn = nullptr;
    QRadioButton * vRadioBtn = nullptr;
    QButtonGroup * gScreenrBtn = nullptr;

    QComboBox * comFill = nullptr;
    QColorFrame * fColor = nullptr;
    QTabBar * speedBar = nullptr;

    QComboBox * comQuality = nullptr;

    QSpinBox * timeSpinBox = nullptr;
    QSpinBox * secondSpinBox = nullptr;

    QButtonGroup * gOrderBtn = nullptr;

    QLabel *lSpeedTime = nullptr;
    QLabel *lSpeedSecond = nullptr;

    QRadioButton * revRadioBtn = nullptr;
    QRadioButton * orderRadioBtn = nullptr;


    //自定义uuid
    QString uuid;
    int prIndex = 0;
    QSize gifSize{360,240};
    std::unique_ptr<customSizeOp> custOP;
    std::shared_ptr<propertyInf> proInf;
};

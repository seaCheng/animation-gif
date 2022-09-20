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

enum screenMode{screen_horizal,screen_vertical};
Q_DECLARE_METATYPE(screenMode)

enum fillMode{fill_full = 0,fill_adjust,fill_stretch};
Q_DECLARE_METATYPE(fillMode)

enum orderMode{order_compliant,order_reverse};
Q_DECLARE_METATYPE(orderMode)

enum qualityMode{quality_none,quality_auto};
Q_DECLARE_METATYPE(qualityMode)

struct propertyInf
{
    int width = 360;
    int heigth = 240;
    screenMode scMode = screen_horizal;
    fillMode fMode = fill_adjust;
    QColor color = Qt::white;
    int delay = 20; //ms
    orderMode oMode = order_compliant;
    qualityMode qMode = quality_none;
};
Q_DECLARE_METATYPE(propertyInf)

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
class QColorDialog;

class CommonPropertyView : public QFrame
{ 
    Q_OBJECT
public:
    CommonPropertyView(std::shared_ptr<propertyInf> proInf, QWidget *parent = 0);
    void setConnect();

    void initial();

    void refreashGifSize();

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

    QColorDialog * colorDialog;


    //自定义uuid
    QString uuid;
    int prIndex = 0;
    QSize gifSize{360,240};
    std::unique_ptr<customSizeOp> custOP;
    std::shared_ptr<propertyInf> proInf;
};

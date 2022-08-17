#pragma once
#include <QFrame>

#include "gifSizeOp.h"

#include <memory>

class QComboBox;
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
    std::unique_ptr<GifSizeOp> pSizeOp;

    //自定义uuid
    QString uuid;
    int prIndex = 0;
};

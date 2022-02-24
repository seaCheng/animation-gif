#pragma once
#include <QFrame>
#include "pictureItem.h"

class QHBoxLayout;
class QScrollArea;
class PicScaleComp;

class PicScaleViewComp :public QFrame
{
    Q_OBJECT
public:

    PicScaleViewComp(QWidget *parent = nullptr);
    void initial();
    void setConnect();

    void insertItem(ModelView::SessionItem * item, ModelView::TagRow row);
    void eraseItem(ModelView::SessionItem * item, ModelView::TagRow row);

    void refreashIndex();

    PicScaleComp * getSelItem();

public slots:
     void refreashState();
protected:
    //void paintEvent(QPaintEvent *event) override;
private:
    QHBoxLayout * m_layout = nullptr;
    QScrollArea * m_scroll = nullptr;

    PicScaleComp * m_picScaleCli = nullptr;
    std::map<PictureItem*, PicScaleComp*> m_itemToView;

};

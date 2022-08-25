#pragma once
#include <QFrame>

class QPushButton;
class QLabel;
class ScaleButtonView : public QFrame
{ 
    Q_OBJECT
public:
    ScaleButtonView(QWidget *parent = 0);
    void setConnect();
    void initial();

signals:
    void s_scaleFreash(qreal);

public slots:

protected:

private:
    qreal qScale = 1.0;

    QPushButton * enlargeBtn = nullptr;
    QPushButton * zoomOutBtn = nullptr;
    QLabel *lNum = nullptr;
};

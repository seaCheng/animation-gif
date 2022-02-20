#pragma once
#include <QGraphicsView>

enum type_import{import_none, import_pic,import_gif};

Q_DECLARE_METATYPE(type_import)

class GraphicsViewComp :public QGraphicsView
{
    Q_OBJECT
public:

    GraphicsViewComp(QWidget *parent = nullptr);

signals:
    void s_clicked(type_import eType);
protected:
    void paintEvent(QPaintEvent *event) override;
private:

    QGraphicsWidget * m_GraWid = nullptr;
};

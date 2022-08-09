#ifndef EMPTYAREAVIEW_H
#define EMPTYAREAVIEW_H
#include <QLabel> 

enum class type_import{import_none, import_pic,import_gif};

Q_DECLARE_METATYPE(type_import)

class EmptyAreaView : public QWidget
{ 
    Q_OBJECT
public: EmptyAreaView(QWidget *parent = 0);

signals:
    void s_clicked(type_import eType);

protected:
    //void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;//重写重绘函数
private:

};
#endif

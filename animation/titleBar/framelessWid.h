#ifndef framelessWid_H
#define framelessWid_H

#include <QDialog>

#ifdef Q_OS_WIN32
#include <windows.h>        //注意头文件
#include <windowsx.h>
#endif

#include <QMouseEvent>

class MaskWin;

class framelessWid : public QDialog
{
    Q_OBJECT

public:
    explicit framelessWid(QWidget *parent = nullptr)
        :QDialog(parent)
	{
		setAttribute(Qt::WA_TranslucentBackground);
		setWindowFlags(Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
		boundaryWidth=4;
        //m_mask = new MaskWin();

	}
    ~framelessWid()
    {

    }

    void setMLayP(QWidget * wid, bool bShow = true)
    {
        //m_mask->setParentInf(wid);
        setModal(true);
        m_show = bShow;

    }
protected:
    void mouseMoveEvent(QMouseEvent *e)
   {
       if(e->buttons()&Qt::LeftButton)
           move(e->pos()+pos()-clickPos);

   }
    void closeEvent(QCloseEvent *event)
    {
        if(m_show)
        {
             //m_mask->hide();
        }
    }

    void showEvent(QShowEvent *event)
    {
        if(m_show)
        {
            //m_mask->show();
        }
    }

   void mousePressEvent(QMouseEvent *e)
   {
    if(e->button()==Qt::LeftButton)
            clickPos=e->pos();
   }

   #ifdef Q_OS_WIN32
   bool nativeEvent(const QByteArray &eventType, void *message, long *result)
   {
       MSG* msg = (MSG*)message;
       switch(msg->message)
        {
        case WM_NCHITTEST:
            int xPos = GET_X_LPARAM(msg->lParam) - this->frameGeometry().x();
            int yPos = GET_Y_LPARAM(msg->lParam) - this->frameGeometry().y();
            if(xPos < boundaryWidth && yPos<boundaryWidth)                    //左上角
                *result = HTTOPLEFT;
            else if(xPos>=width()-boundaryWidth&&yPos<boundaryWidth)          //右上角
                *result = HTTOPRIGHT;
            else if(xPos<boundaryWidth&&yPos>=height()-boundaryWidth)         //左下角
                *result = HTBOTTOMLEFT;
            else if(xPos>=width()-boundaryWidth&&yPos>=height()-boundaryWidth)//右下角
                *result = HTBOTTOMRIGHT;
            else if(xPos < boundaryWidth)                                     //左边
                *result =  HTLEFT;
            else if(xPos>=width()-boundaryWidth)                              //右边
                *result = HTRIGHT;
            else if(yPos<boundaryWidth)                                       //上边
                *result = HTTOP;
            else if(yPos>=height()-boundaryWidth)                             //下边
                *result = HTBOTTOM;
            else              //其他部分不做处理，返回false，留给其他事件处理器处理
               return false;
            return true;
        }
        return false;         //此处返回false，留给其他事件处理器处理
     }
     #endif


private:
   
    int boundaryWidth;
    QPoint clickPos;
    MaskWin * m_mask;
    bool m_show = false;
};


#endif // AWTIPWIDGET_H

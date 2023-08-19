#ifndef TABBARPRI_H
#define TABBARPRI_H

#include <QObject>
#include <QFrame>

class QLabel;
class QFrame;

enum tabStatus{tabStatus_normal = 0 , tabStatus_hover, tabStatus_checked};

class tabBtn : public QFrame
{
    Q_OBJECT
public:
    void setChecked(bool check)
    {
        bCheck = check;
    }

    void setStatus(tabStatus status)
    {
        checkStatus = status;
        refreashStyle();
    }

    tabBtn(QWidget *parent = nullptr);
    void initial();

    void setText(QString sText);

    void refreashStyle();
signals:
    void sigChecked();
protected:
    void mousePressEvent(QMouseEvent *event) override;
    virtual void enterEvent(QEnterEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;

private:

    bool bCheck = false;
    QString strText;
    QLabel * label = nullptr;
    QFrame * frame = nullptr;

    tabStatus checkStatus = tabStatus_normal;

};

////////////////////////////////////////////////////////////////////
/// \brief The TabBarPri class
class QHBoxLayout;
class TabBarPri : public QFrame
{
    Q_OBJECT
public:
    explicit TabBarPri(QWidget *parent = nullptr);
    void addTab(QString sText, tabStatus status = tabStatus_normal);
    void setHeight(int height)
    {
        iheight = height;
        setFixedHeight(iheight);
    }

    void setWidth(int width)
    {
        iWidth = width;
    }

    void setCurrentIndex(int iIndex);
signals:

    void sigCheckedChange(int iIndex);
private:
   std::vector<tabBtn *> lstTab;
   QHBoxLayout *lay = nullptr;
   int iheight = 32;
   int iWidth = 125;
   int iIndex = 0;
};

#endif // TABBARPRI_H

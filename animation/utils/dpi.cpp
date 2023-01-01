#include "dpi.h"
#include <QScreen>
#include <QApplication>
#include <QDebug>

bool DPI::s_bInit = false;
double DPI::s_beishu = 1.000;

DPI::DPI(QObject *parent) : QObject(parent)
{
    
}

qreal DPI::getScale()
{
    if (!s_bInit) {
        QScreen* screen = qApp->primaryScreen();
        qreal dpiVal = screen->logicalDotsPerInch();
        s_beishu = dpiVal / 96;
        connect(screen, &QScreen::logicalDotsPerInchChanged, [](qreal dpi) {
            DPI::logicalDotsPerInchChanged(dpi);
        });
        s_bInit = true;
    }
    return s_beishu;
}

int DPI::getScaleUI(int ori)
{
    return ori * getScale();
}

QSize DPI::getScaleUISize(int wid, int hei)
{
    return QSize(getScaleUI(wid), getScaleUI(hei));
}

void DPI::logicalDotsPerInchChanged(qreal dpi)
{
    qInfo() << "DPI Change :" << dpi;
    s_beishu = dpi / 96;
}
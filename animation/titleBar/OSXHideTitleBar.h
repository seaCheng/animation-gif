#ifndef hhhh_osxhidetitlebar_hhhh
#define hhhh_osxhidetitlebar_hhhh
#include <qglobal.h>

#ifdef Q_OS_MAC
class OSXHideTitleBar
{
public:
    static void HideTitleBar(long winid);
    static void setTitlebarVisible(long winid, bool bTitlebarVisible);
    static void setMinBtnEnabled(long winid,bool bEnable);

    static void setZoomBtnEnabled(long winid,bool bEnable);
};

#endif
#endif

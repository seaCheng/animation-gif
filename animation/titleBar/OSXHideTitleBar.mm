#include "OSXHideTitleBar.h"
#include <Cocoa/Cocoa.h>
#include <QDebug>

void OSXHideTitleBar::HideTitleBar(long winid)
{
    NSView *nativeView = reinterpret_cast<NSView *>(winid);
    NSWindow* nativeWindow = [nativeView window];

    [nativeWindow setStyleMask:
        [nativeWindow styleMask] | NSFullSizeContentViewWindowMask | NSWindowTitleHidden];

    [nativeWindow setTitlebarAppearsTransparent:YES];
    [nativeWindow setMovableByWindowBackground:NO];
    [nativeWindow setTitle:@""];


}

void OSXHideTitleBar::setTitlebarVisible(long winid, bool bTitlebarVisible)
{
    qDebug()<<"start setTitlebarVisible.....";

    NSView* view = (NSView*)winid;
    if (0 == view) return;
    NSWindow *window = view.window;
    if (0 == window) return;


    qDebug()<<"middle setTitlebarVisible.....";
    /*[window setStyleMask:
        [window styleMask] | NSWindowStyleMaskFullSizeContentView | NSWindowTitleHidden];
        */


    window.styleMask = window.styleMask | NSWindowStyleMaskFullSizeContentView;
    window.titlebarAppearsTransparent=YES;
    window.titleVisibility = NSWindowTitleHidden;
    window.toolbar = nil;
    /*
    [window setTitlebarAppearsTransparent:YES];
    [window setTitleVisibility:NSWindowTitleHidden];
    [window setTitle:@"yes i do"];
    */



}
void OSXHideTitleBar::setMinBtnEnabled(long winid,bool bEnable)
{
    NSView* view = (NSView*)winid;
    if (0 == view) return;
    NSWindow *window = view.window;
    if (0 == window) return;

    if (bEnable){
        [[window standardWindowButton:NSWindowMiniaturizeButton] setEnabled:YES];
    }else{
        [[window standardWindowButton:NSWindowMiniaturizeButton] setEnabled:NO];
    }
}

void OSXHideTitleBar::setZoomBtnEnabled(long winid,bool bEnable)
{
    NSView* view = (NSView*)winid;
    if (0 == view) return;
    NSWindow *window = view.window;
    if (0 == window) return;
    if (bEnable){
        [[window standardWindowButton:NSWindowZoomButton] setEnabled:YES];
    }else{
        [[window standardWindowButton:NSWindowZoomButton] setEnabled:NO];
    }
}

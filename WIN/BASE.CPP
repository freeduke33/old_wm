#include "wm_win.hpp"


wm_window::wm_window()
{
 Act=0;
 win.data=0;
 win.border=0;
 return;
}

wm_window::wm_window(int xl,int yl,int xr,int yr,int xx,int yy,int isVisible)
{
 wm_window();
 Open(xl,yl,xr,yr,xx,yy);
 return;
}

wm_window::~wm_window(void)
{
 if(Act) { Close(); }
 return;
}

char *wm_window::NameOf(void) const
{
 static char Name[]="Base Window Class";
 return Name;
}

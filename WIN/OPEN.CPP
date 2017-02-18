#include "wm_win.hpp"

int wm_window::Open(int xl,int yl,int xr,int yr,int xx,int yy,int isVisible)
{
  int val;

  if(Act || !IsActive) return wm_BADusage;
  win.X1=xl+1; win.Y1=yl+1; win.X2=xr-1; win.Y2=yr-1;
  win.XX=xx>xr-xl+1 ? xx : xr-xl+1 ; win.YY=yy>yr-yl+1 ? yy : yr-yl+1;
  win.Metod=wm_wCENTER;
  win.setup=wm_default;

  win.Control=BORDER|CURSOR|SCROLL|HIDDEN;
  val=wm_create(&win);
  if(val==wm_OK)
    {
    Act=1;
    if(isVisible) val=Show();
    }
  return val;
}

int wm_window::Close(void)
{
 int val;

 if(!Act) return wm_BADusage;

 val=wm_delete(&win);
 if(val==wm_OK) Act=0;
 return val;
}

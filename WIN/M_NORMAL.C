#include "wm_stdio.h"

void far wm_xNORMAL(wm_windP w,int mode)
{
 int y2=w->Y2;
 switch(mode)
 {
  case wm_OPEN:
   w->Control&=~HIDDEN;
   for(w->Y2=w->Y1;w->Y2<y2;w->Y2++)
   {
    wmx_border(w);
    wmx_redraw();
    wm_wait(10);
   }
   wmx_border(w);
   wmx_redraw();
  break;
  case wm_CLOSE:
   for(;w->Y2>=w->Y1;w->Y2--)
    {
     wmx_border(w);
     wmx_redraw();
     wm_wait(10);
    }
   w->Y2=y2;
   w->Control|=HIDDEN;
   wmx_redraw();
  break;
 }
 wmx_resetmap();
}

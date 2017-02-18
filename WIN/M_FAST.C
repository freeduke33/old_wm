#include "wm_stdio.h"

void far wm_xONOFF(wm_windP w,int mode)
{
 switch(mode)
 {
 case wm_OPEN: w->Control&=~HIDDEN; break;
 case wm_CLOSE: w->Control|=HIDDEN; break;
 }
 wmx_resetmap();
 wmx_redraw();
 return;
}


/*****************************
 *   Window Manadger v1.0    *
 *      for Turbo C          *
 * Created by Dmitry Kokorev *
 *        31.01.92           *
 * (C) 1992    Samara  SamPI *
 *****************************/



#include "wm_stdio.h"

int  wm_move( wm_windP w,int dX,int dY)
{
 int dd=0,ds=0;
 if(w==NULL) return(wm_BADhandle);
 if(w->Control&BORDER) dd=1;
 if(w->Control&SHADOW) ds=1;

 if(w->X1-dd+dX<0||w->Y1-dd+dY<0||
    w->X2+dd+ds+ds+dX>=wm_xSCR||
    w->Y2+dd+ds+dY>=wm_ySCR) return(wm_BADpos);

 w->X1+=dX;  w->X2+=dX;
 w->Y1+=dY;  w->Y2+=dY;
 if(!(w->Control&HIDDEN))
 {
   wmx_resetmap();
   wmx_redraw();
 }
 return(wm_OK);
}


/*****************************
 *   Window Manadger v1.0    *
 *      for Turbo C          *
 * Created by Dmitry Kokorev *
 *        31.01.92           *
 * (C) 1992    Samara  SamPI *
 *****************************/



#include "wm_stdio.h"

int wm__virtual(wm_windP w,int dx,int dy)
{
 int x,y;
 if(w==NULL) return(wm_BADhandle);
 x=w->dXX+dx;
 y=w->dYY+dy;
 if(x<0||x>=w->XX-w->X2+w->X1||y<0||y>=w->YY-w->Y2+w->Y1) return(wm_BADpos);
 w->dXX=x;
 w->dYY=y;
 wmx_redraw();
 return(wm_OK);
}

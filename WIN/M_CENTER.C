#include "wm_stdio.h"

void far wm_xCENTER(wm_windP w,int mode)
{
 int x1=w->X1,x2=w->X2,y1=w->Y1,y2=w->Y2,x,y,dx,dy;
 x=x1+(x2-x1)/2;
 y=y1+(y2-y1)/2;
 if(x2-x1>y2-y1)
 {
  if(y2-y1) dx=(x2-x1)/(y2-y1);
  else dx=4;
  dy=1;
 }
 else
 {
  if(x2-x1)dy=(y2-y1)/(x2-x1);
  else dy=1;
  dx=1;
 }
 switch(mode)
 {
 case wm_OPEN:
   w->Control&=~HIDDEN;
   w->X1=w->X2=x;
   w->Y1=w->Y2=y;

   while(w->X1!=x1||w->Y1!=y1||w->Y2!=y2||w->X2!=x2)
   {
    if(w->Y1-dy<y1) w->Y1=y1;
    else w->Y1-=dy;
    if(w->Y2+dy>y2) w->Y2=y2;
    else w->Y2+=dy;
    if(w->X1-dx<x1) w->X1=x1;
    else w->X1-=dx;
    if(w->X2+dx>x2) w->X2=x2;
    else w->X2+=dx;
    wmx_border(w);
    wm_xtitle(w);
    wmx_redraw();
    wm_wait(20);
   }
  break;
 case wm_CLOSE:

   while(w->X1!=x||w->Y1!=y||w->Y2!=y||w->X2!=x)
   {
    wmx_border(w);
    wmx_redraw();
    wm_wait(20);
    if(w->Y1+dy>y) w->Y1=y;
    else w->Y1+=dy;
    if(w->Y2-dy<y) w->Y2=y;
    else w->Y2-=dy;
    if(w->X1+dx>x) w->X1=x;
    else w->X1+=dx;
    if(w->X2-dx<x) w->X2=x;
    else w->X2-=dx;
   }
   w->Control|=HIDDEN;
   wmx_border(w);
   wm_xtitle(w);
   wmx_redraw();
  break;
 }
 wmx_resetmap();
}

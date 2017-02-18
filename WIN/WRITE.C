
/*****************************
 *   Window Manadger v1.0    *
 *      for Turbo C          *
 * Created by Dmitry Kokorev *
 *        31.01.92           *
 * (C) 1992    Samara  SamPI *
 *****************************/


#include "stdio.h"
#include "stdlib.h"
#include "wm_stdio.h"

int  wm__at(wm_windP w,int x,int y)
{
 if(w==NULL) return(wm_BADhandle);
 if(x>=w->XX||y>=w->YY||x<0||y<0) return(wm_BADpos);
 w->Xpos=x;
 w->Ypos=y;
/* wm_setcursor(w); */
 return(wm_OK);
}

int  wm__say(wm_windP w,char *str)
{
 int i,x,y,xx,yy;
 unsigned int attr;

 if(w==NULL) return(wm_BADhandle);
 x=w->Xpos;y=w->Ypos;xx=w->XX-1;yy=w->YY-1;
 attr=(w->setup.attr_say)<<8;
 for(i=0;str[i];i++)
 {
  switch(str[i])
  {
  case '\n':
    if(y==yy) wm__scroll(w,1,' ');
    else y++;
    break;
  case '\r':
    x=0;
    break;
  case '\b':
    if(x) x--;
    else
     if(y)
     {
      y--;
      x=xx;
     }
   wm_saychar(w,x,y,(unsigned char)str[i]+attr);
   break;
  default:
   wm_saychar(w,x,y,(unsigned char)str[i]+attr);
   if(x==xx)
   {
    if(y==yy) wm__scroll(w,1,' ');
    else y++;
    x=0;
   }
   else x++;
  }
 }
 w->Xpos=x;
 w->Ypos=y;
/* wm_setcursor(w); */
 return(wm_OK);
}


int wm_Printf(int wHandle,const char *format, ...)
{
 return wm_printf(wm_Handle2wind(wHandle),format, ...);
}

int wm_printf(wm_windP w,const char *format, ...)
{
 char str[160];
 if(vsprintf(str,format, ...)>160) abort();
 return(wm_say(w,str));
}


int  wm__atsay(wm_windP w,int x,int y,char *str)
{
 wm_at(w,x,y);
 wm_say(w,str);
 return(wm_OK);
}


/*****************************
 *   Window Manadger v1.0    *
 *      for Turbo C          *
 * Created by Dmitry Kokorev *
 *        31.01.92           *
 * (C) 1992    Samara  SamPI *
 *****************************/



#include <alloc.h>
#include <stdio.h>
#include <stdarg.h>
#include <dos.h>
#include "wm_stdio.h"


wm_setT wm_default={"ÚÄ¿³³ÀÄÙ",0x37,'°',0x13,0x36,0x070,0x37,0x71};
wm_windP wm_actwin;


#include "ini\init.wmc"
#include "ini\create.wmc"
#include "ini\deinit.wmc"
#include "ini\cls.wmc"

int  wm_delete(wm_windP win)
{
 wm_windP w1,w;
 int i;

 w1=wmx_TOP; w=NULL;

 while(w1!=NULL&&w1!=win)
     {
     w=w1;
     w1=w1->next;
     }
 if(w1==NULL) return(wm_BADhandle);
 w1->Metod(w1,wm_CLOSE);
 if(w==NULL) wmx_TOP=w1->next;
 else w->next=w1->next;
 if(w1->Memory&wm_uDATA)   wm_freemem(w1->data);
 if(w1->Memory&wm_uBORDER) wm_freemem(w1->border);
 if(w1->Memory&wm_uTITLE)  for(i=0;i<12;i++) wm_freemem(w1->title[i]);
 if(w1->Memory&wm_uSTRUCT) wm_freemem(w1);
 return(wm_OK);
}


wm_windP  wm_Handle2wind(int wHandle)
{
 wm_windP w;
 w=wmx_TOP;
 while(w)
   {
   if(w->Handle==wHandle) break;
   w=w->next;
   }
 return(w);
}

void  wm_freemem(void far *mem)
{
 if(mem!=NULL) farfree(mem);
 return;
}

void far *wm_allocmem(unsigned int num,unsigned int size)
{
  return farcalloc(num,size);
}


int wm_active(wm_windP w,int mode)
{
 if(w==NULL) return(wm_BADhandle);
 if(mode) wm_top(w);
 wm_actwin=w;
 if(w->Control&CURSOR) wmx_cursorOn();
 return(wm_OK);
}

void wm_wait(int msec) { delay(msec); }


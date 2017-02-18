
/*****************************
 *   Window Manadger v1.0    *
 *      for Turbo C          *
 * Created by Dmitry Kokorev *
 *        31.01.92           *
 * (C) 1992    Samara  SamPI *
 *****************************/


#include "alloc.h"
#include "wm_stdio.h"



int  wm_hide(wm_windP w)
{
 if(w==NULL) return(wm_BADhandle);
 w->Metod(w,wm_CLOSE);
 return(wm_OK);
}

int  wm_show(wm_windP w)
{
 if(w==NULL) return(wm_BADhandle);
 w->Metod(w,wm_OPEN);
 return(wm_OK);
}


int wm_border(wm_windP w,char *box)
{
 int i;

 if(w==NULL) return(wm_BADhandle);
 for(i=0;i<8;i++) w->setup.box[i]=box[i];
 wmx_border(w);
 return(wm_OK);
}

int wm_title(wm_windP w,char *title,int axis,int col,int shift)
{
 int i,j;

 if(!(w->Memory&wm_uTITLE)) return(wm_BADmem);

 wm_freemem(w->title[axis]);
 for(i=0;title[i];i++); i++;
 w->title[axis]=wm_allocmem(2,i+shift);
 if(w->title[axis])
 {
  switch(axis)
  {
   case wm_tTOP1:
   case wm_tLEFT1:
   case wm_tRIGHT1:
   case wm_tBOTTOM1:  /* ----[левый край]----*/
     for(j=1;j<=shift;j++)
     {
      w->title[axis][j*2-1]=0;
      w->title[axis][j*2]=0;
     }
     for(i=0;title[i];j++,i++)
     {
      w->title[axis][j*2-1]=title[i];
      w->title[axis][j*2]=col;
     }
     shift+=i;
	break;
   case wm_tTOP2:
   case wm_tLEFT2:
   case wm_tRIGHT2:
   case wm_tBOTTOM2:  /* ----[середина]----*/
     shift=i-1;
     for(i=1;i<=shift;i++)
     {
      w->title[axis][i*2-1]=title[i-1];
      w->title[axis][i*2]=col;
     }
	break;
   case wm_tTOP3:
   case wm_tLEFT3:
   case wm_tRIGHT3:
   case wm_tBOTTOM3:  /* ----[правый край]----*/
     shift+=i-1;
     for(j=1,i=0;title[i];j++,i++)
     {
      w->title[axis][j*2-1]=title[i];
      w->title[axis][j*2]=col;
     }
     for(;j<shift;j++)
     {
      w->title[axis][j*2-1]=0;
      w->title[axis][j*2]=0;
     }
	break;
  }
  w->title[axis][0]=shift;
  wm_xtitle(w);
  wmx_redraw();
  i=wm_OK;
 }
 else i=wm_BADmem;
 return(i);
}

int wm_xtitle(wm_windP w)
{
 int i,len,k,j,m,u,n;

 if(w)  for(n=(w->X2-w->X1),m=2*(5+n+(w->Y2-w->Y1)*2),n=(n+2)*2,i=11;i+1;i--)
 {
  u=1;
  if(w->title[i])
  {
   switch(i)
   {
   case wm_tTOP1:
     len=min(w->X2-w->X1,w->title[i][0]);
     k=2;
    break;
   case wm_tLEFT1:
     len=min(w->Y2-w->Y1,w->title[i][0]);
     k=n+2;
     u=0;
    break;
   case wm_tRIGHT1:
     len=min(w->Y2-w->Y1,w->title[i][0]);
     k=n+4;
     u=0;
    break;
   case wm_tBOTTOM1:
     len=min(w->X2-w->X1,w->title[i][0]);
     k=m+2;
    break;
   case wm_tTOP3:
     len=min(w->X2-w->X1,w->title[i][0]);
     k=((w->X2-w->X1+2)-len)*2;
    break;
   case wm_tLEFT3:
     len=min(w->Y2-w->Y1,w->title[i][0]);
     k=n+2+((w->Y2-w->Y1+1)-len)*4;
     u=0;
    break;
   case wm_tRIGHT3:
     len=min(w->Y2-w->Y1,w->title[i][0]);
     k=n+4+((w->Y2-w->Y1+1)-len)*4;
     u=0;
    break;
   case wm_tBOTTOM3:
     len=min(w->X2-w->X1,w->title[i][0]);
     k=m+((w->X2-w->X1+2)-len)*2;
    break;
   case wm_tTOP2:
     len=min(w->X2-w->X1+1,w->title[i][0]);
     k=2+(w->X2-w->X1+1)-len;
    break;
   case wm_tLEFT2:
     len=min(w->Y2-w->Y1+1,w->title[i][0]);
     k=n+2+(((w->Y2-w->Y1+1)-len)&~1)*2;
     u=0;
    break;
   case wm_tRIGHT2:
     len=min(w->Y2-w->Y1+1,w->title[i][0]);
     k=n+4+(((w->Y2-w->Y1+1)-len)&~1)*2;
     u=0;
    break;
   case wm_tBOTTOM2:
     len=min(w->X2-w->X1+1,w->title[i][0]);
     k=m+(w->X2-w->X1)-len;
    break;
   }
   if(u)
   {
    k&=~1;
     for(j=1;j<=len*2;j++,k++)
      if(w->title[i][j]) w->border[k]=w->title[i][j];
   }
   else
   {
    k&=~1;
    for(j=1;j<=len*2;j++,k++)
    {
     if(w->title[i][j]) w->border[k]=w->title[i][j];
     if(k%2) k+=2;
    }
   }
  } /* end if */
 }
 return(wm_OK);
}



/*****************************
 *   Window Manadger v1.0    *
 *      for Turbo C          *
 * Created by Dmitry Kokorev *
 *        31.01.92           *
 * (C) 1992    Samara  SamPI *
 *****************************/



#include "wm_stdio.h"

int  wm_off(wm_windP w)
{
 if(w==NULL) return(wm_BADhandle);
 wm_xONOFF(w,wm_CLOSE);
 return(wm_OK);
}

int  wm_on(wm_windP w)
{
 if(w==NULL) return(wm_BADhandle);
 wm_xONOFF(w,wm_OPEN);
 return(wm_OK);
}

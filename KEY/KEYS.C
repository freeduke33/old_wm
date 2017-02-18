
/*****************************
 *   Window Manadger v1.0    *
 *      for Turbo C          *
 * Created by Dmitry Kokorev *
 *        31.01.92           *
 * (C) 1992    Samara  SamPI *
 *****************************/



#include "wm_stdio.h"
#include "conio.h"

#define size_keystack 20

int  far (*wm_KeyFunc)(int)=NULL;
void far (*wm_KeyLoop)(void)=NULL;

int wm_keystack=0,wm_keystk[size_keystack];




int wm_keypressed()
{
 return(kbhit()|wm_keystack);
}

int wm_getkey()
{
 int ret;
 do{
  while(!wm_keypressed()) if(wm_KeyLoop) (*wm_KeyLoop)();
  if(wm_keystack)
  {
   ret=wm_keystk[wm_keystack--];
  }
  else
  {
   ret=(int)getch();
   if(!ret) ret=getch()*0x100+ret;
  }
 }while(wm_KeyFunc!=NULL&&(*wm_KeyFunc)(ret));
 return(ret);
}

void wm_ungetkey(int key)
{
 if(wm_keystack<size_keystack) wm_keystk[++wm_keystack]=key;
 return;
}



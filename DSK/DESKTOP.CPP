#include <conio.h>
#include "wm_dsk.hpp"

Desktop *wm_desktop::Dsk=NULL;

char *wm_desktop::NameOf(void) const
{
 static char Name[]="Normal Desktop";
 return Name;
}

wm_desktop::wm_desktop(int Act)
{
 return;
}


wm_desktop::~wm_desktop()
{
 return;
}

void wm_desktop::SetActive(void)
{
 if(Dsk) Dsk->SetPassive();
 Dsk=this;
 return;
}

void wm_desktop::SetPassive(void)
{
 if(Dsk==this)
   {
   Dsk=NULL;
   }
 return;
}


// -------------------------------------------------------

void wm_desktop::Supervisor()
{
 int ch;
 MsgInfo Info;
 wm_object *Cur=NULL;

 while(IsActive())
   {
   if(kbhit())
      {
      ch=getch();if(ch==0 && kbhit()) ch+=(getch()<<8);
      Info.Key.Code=ch;
      Info.Key.Status=0;
      PushMessage(KEY,0,0,Info);
      }
   if(Cur) { Cur->Run(); Cur=Cur->next; }
   else Cur=Obj;
   }
 return;
}

void wm_desktop::Run(void)
{

  return;
}


void wm_desktop::Register(wm_object *obj)
{
 Obj->prev=obj;
 obj->next=Obj; obj->prev=NULL;
 Obj=obj;
 return;
}


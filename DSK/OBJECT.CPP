#include "wm_obj.hpp"


int wm_object::IsActive=0;
wm_bldT wm_object::Dsk;

wm_object::wm_object()
{
 if(!IsActive)
   {
   if(wm_init(&Dsk)==wm_OK) IsActive=1;
   }
 return;
}


void wm_object::PushMessage(MsgClass Class,MsgOwner Owner,MsgOwner Target,MsgInfo& Info)
{
 Message msg;
 msg.SetClass(Class);
 msg.SetOwner(Owner);
 msg.SetTarget(Target);
 msg.SetInfo(Info);
 PushMessage(msg);
 return;
}

void wm_object::PushMessage(Message& msg)
{
 return;
}

void wm_object::PopMessage(Message& msg)
{
 return;
}

void wm_object::GetMessage(Message& msg)
{
 return;
}


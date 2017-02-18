#include <string.h>
#include "wm_msg.hpp"

void Message::SetInfo(MsgInfo &Info)
{
 memcpy(&Dat,&Info,sizeof(Dat));
 return;
}

void Message::Info(MsgInfo &Info)
{
 memcpy(&Info,&Dat,sizeof(Dat));
 return;
}

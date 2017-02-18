#include "wm_keys.h"
#include "wm_win.hpp"

void wm_window::Run(void)
{
 Message msg;
 MsgInfo Info;

 GetMessage(msg);
 msg.Info(Info);

 switch(msg.Class())
   {
   case KEY:
     switch(Info.Key.Code)
       {
       case ALT_F5: PopMessage(msg);
		    PushMessage(WIN_MOVE,win.Handle,0,Info);
		    break;
       }
   case MOUSE:
   default:
	 if(msg.Owner()==win.Handle)
	    {
	      switch(msg.Class())
		{
		case WIN_OPEN:
		case WIN_CLOSE:
		case WIN_ARRIVE:
		case WIN_DEPART:
		case WIN_RESIZE:
		case WIN_MOVE:
		case WIN_REFRESH: break;
		}
	      }
	    else
	      {
	      if(msg.Target()==win.Handle)
		{
		}
	      else
		if(msg.Target()==0)
		  {
		  }
	      }
   }
}


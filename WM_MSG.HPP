#ifndef __WM_MSG_HPP__
#define __WM_MSG_HPP__

#include "wm_def.h"

typedef enum {   NOMESSAGE,
		 // User owner
		 KEY,MOUSE,
		 // Internal owner
		 MESSAGE,IDLE,TIMER,
		 // Triggers for DeskTop
		 DSK_CAN_OPEN,DSK_CAN_CLOSE,DSK_CAN_ACTIVE,DSK_CAN_PASSIVE,
		 DSK_OPEN,DSK_CLOSE,DSK_ACTIVE,DSK_PASSIVE,
		 // Triggers for Windows
		 WIN_CAN_DEPART,WIN_CAN_ARRIVE,WIN_CAN_OPEN,WIN_CAN_CLOSE,
		 WIN_CAN_RESIZE,WIN_CAN_MOVE,WIN_CAN_TOP,WIN_CAN_DEBTH,
		 WIN_CAN_REFRESH,WIN_CAN_FREEZE,WIN_CAN_UNFREEZE,
		 WIN_DEPART,WIN_ARRIVE,WIN_OPEN,WIN_CLOSE,
		 WIN_RESIZE,WIN_MOVE,WIN_TOP,WIN_DEBTH,
		 WIN_REFRESH,WIN_FREEZE,WIN_UNFREEZE,
		 // Triggers for Entry
		 ENT_CAN_OPEN,ENT_CAN_CANCEL,ENT_CAN_ACCEPT,ENT_CAN_CLOSE,
		 ENT_CAN_REFRESH,ENT_CAN_REPAINT,
		 ENT_OPEN,ENT_CANCEL,ENT_ACCEPT,ENT_CLOSE,
		 ENT_REFRESH,ENT_REPAINT,
		 // Triggers for Entry Field
		 FLD_CAN_ARRIVE,FLD_CAN_DEPART,FLD_CAN_UPDATE,FLD_CAN_SELECT,
		 FLD_CAN_TOUCH,FLD_CAN_CHECKVAL,FLD_CAN_REFRESH,FLD_CAN_REPAINT,
		 FLD_ARRIVE,FLD_DEPART,FLD_UPDATE,FLD_SELECT,
		 FLD_TOUCH,FLD_CHECKVAL,FLD_REFRESH,FLD_REPAINT,
		 // Triggers for menu
		 MNU_CAN_OPEN,MNU_CAN_CLOSE,MNU_CAN_REFRESH,MNU_CAN_REPAINT,
		 MNU_OPEN,MNU_CLOSE,MNU_REFRESH,MNU_REPAINT,
		 // Triggers for menu items
		 ITM_CAN_ARRIVE,ITM_CAN_DEPART,ITM_CAN_SELECT,ITM_CAN_REFRESH,
		 ITM_ARRIVE,ITM_DEPART,ITM_SELECT,ITM_REFRESH
		 } MsgClass;

typedef WordT MsgOwner;

typedef union
{
  struct   // KEY
      {
      KeyT Code;
      KeyStatusT Status;
      } Key;
  struct   // MOUSE
      {
      ClickT Click;
      PositionT Pos;
      KeyStatusT Status;
      } Mouse;
  struct  // MESSAGE
      {
      char Name[15];
      void *Ptr;
      } Message;
} MsgInfo;


typedef class wm_msg
{
 public:

   inline MsgClass Class(void);
   inline MsgOwner Owner(void);
   inline MsgOwner Target(void);
   void Info(MsgInfo &);
   inline void SetClass(MsgClass);
   inline void SetOwner(MsgOwner);
   inline void SetTarget(MsgOwner);
   void SetInfo(MsgInfo &);

 private:
   MsgClass _Class;
   MsgOwner _Owner,_Target;
   MsgInfo Dat;
} Message;

inline MsgClass wm_msg::Class(void)  { return _Class;  }
inline MsgOwner wm_msg::Owner(void)  { return _Owner;  }
inline MsgOwner wm_msg::Target(void) { return _Target; }
inline void wm_msg::SetClass(MsgClass Class)   { _Class=Class;  }
inline void wm_msg::SetOwner(MsgOwner Owner)   { _Owner=Owner;  }
inline void wm_msg::SetTarget(MsgOwner Target) { _Target=Target;}

#endif

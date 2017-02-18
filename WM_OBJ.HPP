#ifndef __WM_OBJ_HPP__
#define __WM_OBJ_HPP__

#include <iostream.h>
#include "wm_def.h"
#include "wm_msg.hpp"



typedef struct wm_msgstack
{
 int Full;
 wm_msg Itm[50];
 struct wm_msgstack *next,*prev;
} MsgStack;

class far wm_deskTop;

class wm_object
{
 public:
     wm_object(void);

// object name
     virtual char *NameOf(void) const=0;

// save/restore object context
     virtual void WriteObject(ostream& os) const;
     virtual void ReadObject(istream& is);

     friend ostream &operator <<(ostream&,const wm_object&);
     friend istream &operator >>(istream&,wm_object&);

// loop function
     virtual void Run(void) =0;

// message functions
     void PushMessage(Message& msg);
     void PushMessage(MsgClass Class,MsgOwner Owner,MsgOwner Target,MsgInfo& Info);
     void PopMessage(Message &msg);
     void GetMessage(Message& msg);


    wm_object *next,*prev;
    wm_deskTop *owner;

    static int IsActive;  // 1 когда менеджер окон нормально работает

  private:
    static wm_bldT Dsk;

    static MsgStack *Stk;


    // работа с очередями сообщений
     void NewMsgStack(void);
     void GetMsgStack(MsgStack *Stk);
     void SetMsgStack(MsgStack *Stk);


};

inline ostream& operator << (ostream& os,const wm_object& obj)
{
  obj.WriteObject(os);
  return os;
}

inline istream& operator >> (istream& is,wm_object& obj)
{
  obj.ReadObject(is);
  return is;
}

#endif

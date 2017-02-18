#ifndef __WM_DSK_HPP__
#define __WM_DSK_HPP__

#include "wm_def.h"
#include "wm_msg.hpp"
#include "wm_obj.hpp"

typedef class wm_desktop:wm_object
{
 public:
    wm_desktop(int Act=1);
   ~wm_desktop(void);
    void Supervisor(void);

     virtual void Run(void);
// object name
     virtual char *NameOf(void) const;

// registration object on desktop
     void Register(wm_object *obj);

    void SetActive(void);

// messages
     wm_object::PushMessage;
     wm_object::PopMessage;
     wm_object::GetMessage;


    inline int IsActive(void);

 private:

   static wm_desktop *Dsk;  // активный рабочий стол
   wm_object *Obj;	    // обьекты на столе

    void SetPassive(void);


} Desktop;

inline int wm_desktop::IsActive(void) { return(Dsk==this); }

#endif

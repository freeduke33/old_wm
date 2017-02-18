#ifndef __WM_WIN_HPP__
#define __WM_WIN_HPP__


#include "wm_win.h"
#include "wm_obj.hpp"

typedef class wm_window Window;

class wm_window:public wm_object
{
 public:
    wm_window(void);
    wm_window(int xl,int yl,int xr,int yr,int xx,int yy,int isVisible);
    virtual ~wm_window(void);

// open/close window into desktop
    inline int Open(int xl,int yl,int xr,int yr);
    inline int Open(int xl,int yl,int xr,int yr,int xx,int yy);
    int Open(int xl,int yl,int xr,int yr,int xx,int yy,int isVisible);
    int Close(void);

    inline int Active(void);
    inline int Active(int GoTOP);

    inline int Show(void);
    inline int Hide(void);

// window definitions/accesories
    inline int Metod(wm_metod metod);

    inline int Title(char *str,char attr);
    inline int BoxMessage(int age,char *str,char attr);
    inline int BoxMessage(int age,char *str,char attr,int shift);

    int ShadowOff(void);
    int ShadowOn(void);
    int ShadowOn(char sh);

// window colors
    int SetColor(int box,int text,int title);

// window manipulations
    inline int Move(int dx,int dy);
    inline int Scroll(int lines);
    inline int Virtual(int dx,int dy);
    inline int Freeze(void);
    inline int UnFreeze(void);

// write strings to window
    inline int At(int x,int y);
    inline int Say(char *str);
    inline int SayChar(char ch);
    inline int AtSay(int x,int y,char *str);
    inline int AtSayChar(int x,int y,char ch);

    int Printf(const char *format, ...);
    int AtPrintf(int x,int y,const char *format, ...);

// cursor
    int CursorOff(void);
    int CursorOn(void);
    int CursorSize(int lo,int hi);

    virtual char *NameOf(void) const;
    virtual void Run(void);

   // messages ...
     wm_object::PushMessage;
     wm_object::PopMessage;
     wm_object::GetMessage;

 private:
   int Act;
   wm_windT win;

};

inline int wm_window::Open(int xl,int yl,int xr,int yr) { return Open(xl,yl,xr,yr,-1,-1,1); }
inline int wm_window::Open(int xl,int yl,int xr,int yr,int xx,int yy) { return Open(xl,yl,xr,yr,xx,yy,1); }
inline int wm_window::Show(void) { if(Act) return wm_show(&win);else return wm_BADusage; }
inline int wm_window::Hide(void) { if(Act) return wm_hide(&win);else return wm_BADusage; }
inline int wm_window::Active() { if(Act) return wm_active(&win,1); else return wm_BADusage; }
inline int wm_window::Active(int mode) { if(Act) return wm_active(&win,mode); else return wm_BADusage; }

inline int wm_window::Metod(wm_metod m) { if(Act) { win.Metod=m;return wm_OK;} else return wm_BADusage; }
inline int wm_window::BoxMessage(int age,char *str,char attr) { if(Act) return wm_title(&win,str,age,attr,0);else return wm_BADusage; }
inline int wm_window::BoxMessage(int age,char *str,char attr,int shift) { if(Act) return wm_title(&win,str,age,attr,shift);else return wm_BADusage; }
inline int wm_window::Title(char *str,char attr) { if(Act) return wm_title(&win,str,wm_tTOP1,attr,0);else return wm_BADusage; }

inline int wm_window::Move(int dx,int dy) {if(Act) return wm_move(&win,dx,dy); else return wm_BADusage;}
inline int wm_window::Virtual(int dx,int dy) {if(Act) return wm_virtual(&win,dx,dy); else return wm_BADusage;}
inline int wm_window::Scroll(int lines)   {if(Act) {wm_scroll(&win,lines,' ');return wm_OK;} else return wm_BADusage;}
inline int wm_window::Freeze(void) {return wm_OK;}
inline int wm_window::UnFreeze(void) {return wm_OK;}

inline int wm_window::At(int x,int y) { if(Act) wm_at(&win,x,y); else return wm_BADusage;}
inline int wm_window::Say(char *str)  { if(Act) wm_say(&win,str); else return wm_BADusage;}
inline int wm_window::SayChar(char ch)  { if(Act) wm_saychar(&win,win.Xpos,win.Ypos,ch); else return wm_BADusage;}
inline int wm_window::AtSay(int x,int y,char *str) { if(Act) wm_atsay(&win,x,y,str); else return wm_BADusage;}
inline int wm_window::AtSayChar(int x,int y,char ch) { if(Act) wm_saychar(&win,x,y,ch); else return wm_BADusage;}

#endif


#ifndef __WM_WIN_H__
#define __WM_WIN_H__

#include "wm_def.h"

#ifdef __cplusplus
 extern "C" {
#endif

/* -------------- [Window Control] ----------------- */

/* ----[Control Codes] ----*/

#define BORDER	  0x80			/* -- draw border in window -- */
#define SHADOW	  0x40			/* -- draw shadow in window -- */
#define COOKED	  0x20			/* -- convert control codes -- */
#define HIDDEN	  0x10			/* -- no draw window today  -- */
#define CURSOR	  0x08			/* -- cursor is ON in window-- */
#define SCROLL	  0x04			/* -- scroll up window if full */
#define SCROLBARS 0x02			/* -- show position in virtual */


#define wm_FAST       0
#define wm_NORMAL     1
#define wm_CENTERED   2
#define wm_FCNTL      3


/*	  TOP
    +-2----1----3-+
    |		  |
 L  2		  2 R
 E  |		  | I
 F  1		  1 G
 T  |		  | H
    3		  3 T
    |		  |
    +-2----1----3-+
	 BOTTOM
*/


#define wm_tTOP2	0
#define wm_tLEFT2	1
#define wm_tRIGHT2	2
#define wm_tBOTTOM2	3
#define wm_tTOP1	4
#define wm_tLEFT1	5
#define wm_tRIGHT1	6
#define wm_tBOTTOM1	7
#define wm_tTOP3	8
#define wm_tLEFT3	9
#define wm_tRIGHT3	10
#define wm_tBOTTOM3	11


#define wm_uDATA	0x01
#define wm_uBORDER	0x02
#define wm_uTITLE	0x04
#define wm_uSTRUCT	0x08


#define wm_wONOFF    wm_xONOFF
#define wm_wNORMAL   wm_xNORMAL
#define wm_wCENTER   wm_xCENTER
#define wm_wFCNTL    wm_xFCNTL

/* ----[Window definitions] ----*/

typedef struct _wm_set wm_setT,far *wm_setP;
typedef void (far* wm_metod)(wm_windP,int);

struct _wm_set				/* --[Color and border structure]--*/
{
 char box[8];				/* -- border definitions -- */
 char attr_box; 			/* -- border attribute	 -- */
 char shadow_ch;			/* -- shadow character if 0 - */
 char attr_shadow;			/* -- shadow attribute	 -- */
 char attr_say; 			/* -- normal text attribute */
 char attr_actget;			/* -- active text attribute */
 char attr_nactget;			/* -- passive text attribute*/
 char attr_title;			/* -- main title attribute  */
};


struct _wm_window
{
 unsigned int Control;			/* -- Window control word -- */
 unsigned int Handle;			/* -- Window Handle	  -- */
 unsigned char Memory;			/* -- Memory using setup  -- */
 unsigned char Y1,X1,Y2,X2;		/* -- Position window on screen */
 unsigned int XX,YY,			/* -- window virtual size -- */
	      dXX,dYY,			/* -- shift showing part  -- */
	      Xpos,Ypos;		/* -- cursor position	  -- */
 wm_metod Metod;			/* -- Open/close method   -- */
 struct _wm_set setup;			/* -- color and border definition */
 char far *title[12];			/* -- array of titles	  -- */
 char far *border;			/* -- border map	  -- */
 char far *data;			/* -- text from window	  -- */
 wm_windP next; 			/* -- next window structure  */
};

extern wm_windP wm_actwin;		/* -- Current active window  */

/* ----[Functions for all windows]---- */

void far pascal wmx_redraw(void);	/* -- redraw all open windows -- */
void far pascal wmx_cursorOn(void);	/* -- set cursor ON in active window */
void far pascal wmx_cursorOff(void);	/* -- set cursor OFF */

void wm_Freeze(void);			/* -- freeze desktop */
void wm_Unfreeze(void); 		/* -- unfreeze desktop */

/* ----[Functions for one window]---- */

/* prefix :
	      wm__x  - level 1, no allocate memory
	      wm_x   - level 2, use structures
	      wm_X   - level 3,for users (high details)
	      wmX    - level 4,for users (low details)

/* -- Create new window and open it on the screen */
int   wmCreate(int x1,int y1,int x2,int y2,char title);
int   wm_Create(int x1,int y1,
		int x2,int y2,
		int xx,int yy,
		int Control,
		char *title,
		wm_metod Metod);

int wm_create(wm_windP w);
int wm__create(wm_windP w);

/* -- Delete window -- */
int   wmDelete(void);
int   wm_Delete(int wHandle);
int   wm_delete(wm_windP w);
int   wm__delete(wm_windP w);

/* -- Close window on the screen -- */
int   wmHide(void);
int   wm_Hide(int wHandle);
int   wm_hide(wm_windP w);
int   wm__hide(wm_windP w);

/* -- Open window on the screen  -- */
int   wmShow(void);
int   wm_Show(int wHandle);
int   wm_show(wm_windP w);
int   wm__show(wm_windP w);

/* -- Erase window from screen at one moment --*/
int   wmOff(void);
int   wm_Off(int wHandle);
int   wm_off(wm_windP w);
int   wm__off(wm_windP w);

/* -- Restore window from screen at one moment --*/
int   wmOn(void);
int   wm_On(int wHandle);
int   wm_on(wm_windP w);
int   wm__on(wm_windP w);

/* -- Move window at current position to ... -- */
int   wmMove(int dX,int dY);
int   wm_Move(int wHandle,int dX,int dY);
int   wm_move(wm_windP w,int dX,int dY);
int   wm__move(wm_windP w,int dX,int dY);


/* -- Copy string ch/attr to window -- */
void wmPutarray(int X,int Y,int Len,int Axis,char *Str);
void wm_Putarray(int wHandle,int X,int Y,int Len,int Axis,char *Str);
void wm_putarray(wm_windP W,int X,int Y,int Len,int Axis,char *Str);
void wm__putarray(wm_windP W,int X,int Y,int Len,int Axis,char *Str);

/* -- Copy string ch/attr from window -- */
void wmGetarray(int X,int Y,int Len,int Axis,char *Str);
void wm_Getarray(int wHandle,int X,int Y,int Len,int Axis,char *Str);
void wm_getarray(wm_windP W,int X,int Y,int Len,int Axis,char *Str);
void wm__getarray(wm_windP W,int X,int Y,int Len,int Axis,char *Str);

/* -- scroll up/down window and full it -- */
void wmScroll(int numLine);
void wm_Scroll(int wHandle,int NumLine,char Fill_char);
void wm_scroll(wm_windP W,int NumLine,char Fill_char);
void wm__scroll(wm_windP W,int NumLine,char Fill_char);

/* -- Put one character to window -- */
void wmSayChar(int x,int y,char Ch);
void wm_SayChar(int wHandle,int x,int y,char Ch);
void wm_saychar(wm_windP W,int x,int y,char Ch);
void wm__saychar(wm_windP W,int x,int y,unsigned int Ch);

/* -- Move showing box in virtual window --*/
int   wmVirtual(int dX,int dY);
int   wm_Virtual(int wHandle,int dx,int dy);
int   wm_virtual(wm_windP w,int dx,int dy);
int   wm__virtual(wm_windP w,int dx,int dy);

/* -- Clear window -- */
int   wmCls(void);
int   wm_Cls(int wHandle);
int   wm_cls(wm_windP w);
int   wm__cls(wm_windP w);

/* -- Write string at current cursor position */
int   wmSay(char *str);
int   wm_Say(int wHandle,char *str);
int   wm_say(wm_windP w,char *str);
int   wm__say(wm_windP w,char *str);

/* -- Get current cursor position -- */
int   wmGetCursor(int *x,int *y);
int   wm_GetCursor(int wHandle,int *x,int *y);
int   wm_getcursor(wm_windP w,int *x,int *y);
int   wm__getcursor(wm_windP w,int *x,int *y);

/* -- Change cursor position -- */
int   wmAt(int x,int y);
int   wm_At(int wHandle,int x,int y);
int   wm_at(wm_windP w,int x,int y);
int   wm__at(wm_windP w,int x,int y);

/* -- Write string and change cursor position */
int   wmAtsay(int x,int y,char *str);
int   wm_Atsay(int wHandle,int x,int y,char *str);
int   wm_atsay(wm_windP w,int x,int y,char *str);
int   wm__atsay(wm_windP w,int x,int y,char *str);

/* -- Write formated string */
int   wmPrintf(const char *format, ...);
int   wm_Printf(int wHandle,const char *format, ...);
int   wm_printf(wm_windP w,const char *format, ...);

/* -- Change border characters -- */
int   wmBorder(char *border);
int   wm_Border(int wHandle,char *border);
int   wm_border(wm_windP w,char *border);
int   wm__border(wm_windP w,char *border);

/* -- Move window into desktop -- */
int   wmExchg(int wHandle1);
int   wm_Exchg(int wHandle1,int wHandle2);
int   wm_exchg(wm_windP w1,wm_windP w2);
int   wm__exchg(wm_windP w1,wm_windP w2);

int   wmTop(void);
int   wm_Top(int wHandle);
int   wm_top(wm_windP w);
int   wm__top(wm_windP w);

int   wmBottom(void);
int   wm_Bottom(int wHandle);
int   wm_bottom(wm_windP w);
int   wm__bottom(wm_windP w);

/* -- Define border message -- */
int   wmTitle(char *Title,int mode,int color,int shift);
int   wm_Title(int wHandle,char *Title,int mode,int color,int shift);
int   wm_title(wm_windP w,char *Title,int mode,int color,int shift);
int   wm__title(wm_windP w,char *Title,int mode,int color,int shift);

/* -- Set window active -- */
int   wmActive(int wHandle,int go_TOP);
int   wm_Active(int wHandle,int go_TOP);
int   wm_active(wm_windP w,int go_TOP);
int   wm__active(wm_windP w,int go_TOP);



/* ----[Internal routines]---- */

#define wm_OPEN  0
#define wm_CLOSE 1

void far pascal wmx_scroll(wm_windP W,int NumLine,char Fill_char);
void far pascal wmx_border(wm_windP W);
void far pascal wmx_putarray(wm_windP W,int X,int Y,int Len,int Axis,char *Str);
void far pascal wmx_getarray(wm_windP W,int X,int Y,int Len,int Axis,char *Str);
void far pascal wmx_saychar(wm_windP W,int x,int y,unsigned int Ch);

wm_windP  wm_Handle2wind(int wHandle);
int   wm_xcls(wm_windP w);
int   wm_xtitle(wm_windP w);
void  far wm_xONOFF(wm_windP w,int mode);
void  far wm_xNORMAL(wm_windP w,int mode);
void  far wm_xCENTER(wm_windP w,int mode);
void  far wm_xFCNTL(wm_windP w,int mode);

#define wm_Freeze()	((wmx_FREEZE<0xff) ? ++wmx_FREEZE:wmx_FREEZE)
#define wm_Unfreeze()	((wmx_FREEZE>0) ? --wmx_FREEZE:wmx_FREEZE)


#define wm__scroll(w,n,c)     wmx_scroll(w,n,c)
#define wm_saychar(w,x,y,ch)  wmx_saychar(w,x,y,ch)
#define wm__saychar(w,x,y,ch) wmx_saychar(w,x,y,ch)
#define wm_atsay(w,x,y,str)  wm__atsay(w,x,y,str)
#define wm_say(w,str)	     wm__say(w,str)
#define wm_at(w,x,y)	     wm__at(w,x,y)

#define wm_Delete(h)	   wm_delete(wm_Handle2wind(h))
#define wm_Active(h,m)	   wm_active(wm_Handle2wind(h),m)
#define wm_Cls(h)	   wm_cls(wm_Handle2wind(h))
#define wm_Exchg(h1,h2)    wm_exchg(wm_Handle2wind(h1),wm_Handle2wind(h2))
#define wm_Bottom(h)	   wm_exchg(wm_TOP->next,wm_Handle2wind(h))
#define wm_Top(h)	   wm_top(wm_Handle2wind(h))
#define wm_Move(h)	   wm_move(wm_Handle2wind(h))
#define wm_On(h)	   wm_on(wm_Handle2wind(h))
#define wm_Off(h)	   wm_off(wm_Handle2wind(h))
#define wm_Scroll(h,x,y)   wm_scroll(wm_Handle2wind(h),x,y)
#define wm_Hide(h)	   wm_hide(wm_Handle2wind(h))
#define wm_Show(h)	   wm_show(wm_Handle2wind(h))
#define wm_At(h,x,y)	   wm_at(wm_Handle2wind(h),x,y)
#define wm_Say(h,s)	   wm_say(wm_Handle2wind(h),s)
#define wm_Atsay(h,x,y,s)  wm_atsay(wm_Handle2wind(h),x,y,s)

#define wmDelete()	 wm_delete(wm_actwin->Handle)
#define wmCls() 	 wm_cls(wm_actwin->Handle)
#define wmBottom()	 wm_exchg(wm_TOP->next,wm_actwin->Handle)
#define wmTop() 	 wm_top(wm_actwin->Handle)
#define wmMove()	 wm_move(wm_actwin->Handle)
#define wmOn()		 wm_on(wm_actwin->Handle)
#define wmOff() 	 wm_off(wm_actwin->Handle)
#define wmScroll(x,y)	 wm_scroll(wm_actwin->Handle)
#define wmHide()	 wm_hide(wm_actwin->Handle)
#define wmShow()	 wm_show(wm_actwin->Handle)
#define wmAt(x,y)	 wm_at(wm_actwin->Handle,x,y)
#define wmSay(s)	 wm_say(wm_actwin->Handle,s)
#define wmAtsay(x,y,s)	 wm_atsay(wm_actwin->Handle,x,y,s)

extern struct _wm_set wm_default;

#ifdef __cplusplus
 }
#endif

#endif
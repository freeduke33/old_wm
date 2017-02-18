#ifndef __WM_MNU_H__
#define __WM_MNU_H__

#include "wm_win.h"


#ifdef __cplusplus
  extern "C" {
#endif
/* --------------- [Menu Control] ------------------ */

/* ----[Control codes]---- */


/* Режимы при определении пунктов меню */

#define wm_iFUNCTION	 0x00	 /* пункт вызывает функцию */
#define wm_iSUBMENU	 0x01	 /* пункт вызывает под-меню */
#define wm_iSEPARATOR	 0x02	 /* пункт-разделитель */
#define wm_iUNAVAILABLE  0x04	 /* невыбираемый пункт */
#define wm_iCHECKED1	 0x08	 /* отмечается один из них */
#define wm_iCHECKED2	 0x10	 /* отмечается любой из них */
#define wm_iHIDDEN	 0x20	 /* скрыть меню перед выполнением */
#define wm_iRETURN	 0x40	 /* выйти из меню после выполнения */

#define wm_ixSELECTED	 0x80	 /* установлен если пункт отмечен */


/* Режимы при определении меню */

#define wm_mVERTICAL	 0x01	  /* делать вертикальное меню */
#define wm_mHORIZONTAL	 0x02	  /* делать горизонтальное меню */

#define wm_mSINGLE	 0x04
#define wm_mDOUBLE	 0x08


/* Коды возврата из функции в меню */
#define wm_mLEAVE  0x01  /* выйти из меню */
#define wm_mREDRAW 0x02  /* перерисовать активное подменю */
#define wm_mSELECT 0x03  /* отметить активный пункт */


/* ----[Menu definitions]---- */

typedef struct wm_menustruct *wm_MENU;
typedef struct wm_itemstruct *wm_ITEM;

struct wm_menustruct
{
 int Control,windControl;
 int wHandle,max_LenItem;
 wm_metod Metod;
 struct _wm_set setup;
 int x,y,dx;
 struct wm_itemstruct *first,*current;
 struct wm_menustruct *topmenu;
 char *title;
};

/* ----[Item definitions]---- */


struct wm_itemstruct
{
  int Control;
  int x,y;
  unsigned char *name,*help,*ActStr;
  void *params;
  struct wm_itemstruct *next;
  union
  {
   int (*exec)(wm_MENU);
   struct wm_menustruct *submenu;
  } enter;
};
/* ----[Menu routines]---- */

int   wm_Menu(wm_MENU m);
int   wm_DisplayMenu(wm_MENU m);
int   wm_AssignMenu(wm_MENU m);
int   wmx_mAddItem(wm_MENU menu,char *name,char *ActStr,void *point,
		   void *params,char *help,int control);
wm_MENU wm_mCreate(int x,int y,int dx,char *title,int control,
		   int wControl,wm_metod Metod);


/* -- Global variables -- */
extern struct _wm_set wm_defaultmenu;
extern void far (*wm_KeyLoop)(void);
extern int  far (*wm_KeyFunc)(int);
extern void far (*wm_MenuFunc)(wm_MENU m,int *key);

#ifdef __cplusplus
  }
#endif

#endif

#ifndef __WM_ENT_H__
#define __WM_ENT_H__


#include "wm_def.h"

#ifdef __cplusplus
 extern "C" {
#endif
/* ------------ [Get fields Control] --------------- */

/* ----[field definitions]---- */

typedef struct _fieldtype wm_fieldtype;

struct _fieldtype
{
 char *str,*tmp,*pic;
 int Xbas,Ybas,dX,dY,wHandle;
 char control;
 wm_fieldtype *next;
};

typedef struct _gettype wm_gettype;

struct _gettype
{
 wm_fieldtype *begin,*curr;
 int next,prev,enter,cancel;
 int (*getproc)(void);
};

/* ----[Pick definitions]---- */

typedef struct _pictype wm_pictype;

struct _pictype
{
 char pic;
 int (*picproc)(char *str,char *pic,char c,int *pos,int *delt);
};

/* ----[Get fields]---- */

int   wmx_ReadGets(wm_gettype *tab);
int   wm_Getfield(wm_gettype *tab);
int   wmx_Atget(wm_gettype *tab,
		int wHandle,
		int x,int y,
		char *str,
		char *pic);
int   wmx_Get(wm_gettype *tab,
		int wHandle,
		char *str,
		char *pic);

/* ----[Pick routines]---- */

int   wm_Addpic(char pic,int (*picproc)(char *str,char *pic,char c,int *pos,int *delt));
void *wm_Delpic(char pic);

#define wm_Atget(w,x,y,str,pic) wmx_Atget(&wm_getdefault,w,x,y,str,pic)
#define wm_Get(w,str,pic)     wmx_Get(&wm_getdefault,w,str,pic)
#define wm_ReadGets()	      wmx_ReadGets(&wm_getdefault)

extern wm_gettype wm_getdefault;

#ifdef __cplusplus
 }
#endif

#endif


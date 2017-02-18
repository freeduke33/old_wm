#ifndef __WM_DEF_H__
#define __WM_DEF_H__


/* ----------- [Window Manadger Control] ----------- */

/* ----[Control Codes]---- */

#define wm_OK	      0
#define wm_BADpos    -1
#define wm_BADmem    -2
#define wm_BADhandle -3
#define wm_BADfield  -4
#define wm_BADtable  -5
#define wm_BADmenu   -6
#define wm_BADusage  -7



/* ----[Global definitions]---- */

typedef struct _wm_window wm_windT,far *wm_windP;

typedef struct
{
 void far *Map;        /*--[карта видимости]--*/
 void far *Windows;    /*--[буфер пре-вывода]--*/
 wm_windP   SCREEN;    /*--[базовое окно пакета]--*/
} wm_bldT,far *wm_bldP;

typedef char CharT,*CharP;
typedef unsigned char ByteT,*ByteP;
typedef int IntT,*IntP;
typedef unsigned int WordT,*WordP;
typedef WordT KeyT;
typedef WordT KeyStatusT;

typedef enum { None,ClickSR,ClickSL,ClickSB,
		    ClickDR,ClickDL,ClickDB } ClickT;
typedef struct { ByteT X; ByteT Y; } PositionT;

/* ----[Global routines]---- */

#ifdef __cplusplus
  extern "C" {
#endif
int   wm_Init(void);			/* -- initial WM routine -- */
int   wm_init(wm_bldP ini);		/*  Label 2 */
int   wm__init(wm_bldP ini);		/*  Label 3 */

int   wm_Deinit(void);			/* -- final WM routine	 -- */

int   wm_getkey(void);
void  wm_ungetkey(int key);
int   wm_keypressed(void);


char  wm_upper(char c);
char  wm_lower(char c);

void  wm_wait(int msec);

/* ----[Internal routines]---- */

void far pascal wmx_setmap(int wHandle);
void far pascal wmx_resetmap(void);
int  far pascal wmx_init(void);
void far pascal wmx_save(char far *data);
int  far pascal wmx_deinit(void);

void far *wm_allocmem(unsigned int num,unsigned int size);
void wm_freemem(void far *Ptr);
#ifdef __cplusplus
  }
#endif

/* ----[Internal Variables]---- */

extern wm_windP far pascal wmx_TOP;
extern char far* far pascal wmx_MAP,
	    far* far pascal wmx_WINDOWS,
	    far* far pascal wmx_DISPLAY;
extern char pascal wm_SHOWCHECK;
extern unsigned char pascal wmx_FREEZE;

extern unsigned int far pascal wm_xSCR,
		    far pascal wm_ySCR,
		    far pascal wm_cPos,
		    far pascal wm_cSize;


/* -------------[Global Macros]-------------*/

#ifndef max
#define max(a,b) ((a) > (b) ? (a) : (b) )
#endif
#ifndef min
#define min(a,b) ((a) < (b) ? (a) : (b) )
#endif


#ifndef NULL
#if defined(__TINY__) || defined(__SMALL__) || defined(__MEDIUM__)
#define NULL	0
#else
#define NULL	0L
#endif
#endif

#endif


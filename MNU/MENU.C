#include <alloc.h>
#include "wm_stdio.h"
#include "wm_keys.h"


int wmx_DisplayItem(wm_MENU m,wm_ITEM item,int wHandle,
			unsigned int act,unsigned int nact);
int wm_mSelect(wm_MENU m);




struct _wm_set wm_defaultmenu={"ÚÄ¿³³ÀÄÙ",0x7,'°',0x03,0x06,0x070,0x37,0x71};

void far (*wm_MenuFunc)(wm_MENU m,int *key);

wm_MENU wm_mCreate(int x,int y,int dx,char *title,
			int control,int wControl,wm_metod Metod)
{
 wm_MENU m;
 int i;

 for(i=0;title[i];i++);
 m=calloc(1,sizeof(struct wm_menustruct)+i+1);
 if(m==NULL) return(m);
 m->Control=control;
 m->x=x;
 m->dx=dx;
 m->y=y;
 m->title=(char *)m+sizeof(struct wm_menustruct);
 for(i=0;title[i];i++) m->title[i]=title[i];m->title[i]=0;
 m->first=m->current=NULL;
 m->setup=wm_defaultmenu;
 m->Metod=Metod;
 m->windControl=wControl;
 m->wHandle=0;
 return(m);
}


int wmx_mAddItem(wm_MENU menu,char *name,char *ActStr,void *point,
		 void *params,char *help,int control)
{
 wm_ITEM item;
 int i,j;

 if(menu==NULL) return(wm_BADmenu);
 for(i=0;name[i];i++);
 for(j=0;help[j];j++);

 item=calloc(1,(sizeof(struct wm_itemstruct)+i+j+4));
 if(item==NULL) return(wm_BADmem);
 item->name=(unsigned char *)item+sizeof(struct wm_itemstruct);
 item->help=item->name+i+1;
 for(i=0;name[i];i++) item->name[i]=name[i]; item->name[i]=0;
 for(i=0;help[i];i++) item->help[i]=help[i]; item->help[i]=0;

 for(i=0;ActStr[i];i++); i++;
 item->ActStr=calloc(1,i);
 if(item->ActStr==NULL) {free(item);return(wm_BADmem);}

 for(i=0;ActStr[i];i++) item->ActStr[i]=ActStr[i]; item->ActStr[i]=0;
 item->Control=control;
 item->next=NULL;
 item->enter.submenu=(wm_MENU)point;
 if(control&wm_iSUBMENU) item->enter.submenu->topmenu=menu;
 item->params=params;
 if(menu->current!=NULL) menu->current->next=item;
 else menu->first=item;
 menu->current=item;

 return(wm_OK);
}



int wm_AssignMenu(wm_MENU m)
{
 wm_ITEM item;
 int i,k,j,l,no;

 if(m==NULL&&m->first==NULL) return(wm_BADmenu);

 item=m->first;
 m->max_LenItem=j=k=0;
 while(item!=NULL)
 {
  for(i=no=0;item->name[i];i++) if(item->name[i]=='~') no++;
  i-=no;
  j++;
  item->x=j;
  if(m->Control&wm_mVERTICAL)
   {
    item->y=k++;
    j--;
    for(l=0;item->ActStr[l];l++,i++); i++;
    if(i>m->max_LenItem) m->max_LenItem=i;
   }
  else
  {
   j+=i;
   if(j%m->dx<j)
   {
     k++;j=i;
     item->x=1;
   }
   else
   {
    if(j-1>m->max_LenItem) m->max_LenItem=j-1;
   }
   item->y=k;
  }
  item=item->next;
 }
 j--;
 j=max(j,m->max_LenItem);
 if(m->Control&wm_mVERTICAL) k--;

 if(m->max_LenItem==0) return(wm_BADmenu);

 if(m->windControl&BORDER) {j+=2;k+=2;}
 m->wHandle=wm_Create(m->x,m->y,m->x+j,m->y+k,-1,-1,
		      m->windControl|HIDDEN,m->title,m->Metod);
 if(m->wHandle<0) return(m->wHandle);
 return(wm_OK);
}


int wmx_DisplayItem(wm_MENU m,wm_ITEM item,int wHandle,
			unsigned int act,unsigned int nact)
{
 int x,y,i,k,ch;
 unsigned int attr;
 wm_windP w;
  w=wm_Handle2wind(wHandle);
  if(w==NULL) return(wm_BADmenu);

  x=item->x;
  y=item->y;
  if(item->Control&wm_ixSELECTED) ch='+';
  else ch=' ';

  act<<=8;
  attr=nact<<=8;
  wm_saychar(w,x-1,y,ch+attr);
  for(i=k=0;item->name[i];i++)
  {
    if(item->name[i]=='~') {i++;k++;attr=act;}
    wm_saychar(w,(x++),y,item->name[i]+attr);
    attr=nact;
  }
  i-=k;
  if(m->Control&wm_mVERTICAL)
  {
   for(k=0;item->ActStr[k];k++);
   for(;i<m->max_LenItem-k;i++) wm_saychar(w,(x++),y,' '+attr);
   for(k=0;item->ActStr[k];i++,k++) wm_saychar(w,(x++),y,item->ActStr[k]+attr);
  }
 return(wm_OK);
}


int wm_DisplayMenu(wm_MENU m)
{
 wm_ITEM item;
 int attr;

 if(m==NULL) return(wm_BADmenu);

 item=m->first;
 while(item!=NULL)
 {
  if(item==m->current) attr=(m->setup.attr_actget);
  else attr=(m->setup.attr_nactget);
  wmx_DisplayItem(m,item,m->wHandle,m->setup.attr_title,attr);
  item=item->next;
 }
 return(wm_OK);
}


int wm_Menu(wm_MENU m)
{
 int ret;
 if(m==NULL||m->first==NULL) return(wm_BADmenu);
 m->current=m->first;
 wm_AssignMenu(m);
 if(wm_DisplayMenu(m)<0) return(wm_BADmenu);
 wm_Show(m->wHandle);
 ret=wm_mSelect(m);
 wm_Delete(m->wHandle);
 return(ret);
}

int wm_mSelect(wm_MENU m)
{
 int Exit=0,key,key1,i;
 wm_ITEM tmp;

 while(!Exit)
 {
  key=wm_getkey();
  if(key>0)
  {
   key1=key;
   if(wm_MenuFunc!=NULL) (*wm_MenuFunc)(m,&key);
  }
  switch(key)
  {
   case KEY_up:
     if(m->Control&wm_mVERTICAL) wm_ungetkey(-2);
     else wm_ungetkey(-3);
     break;
   case KEY_down:
     if(m->Control&wm_mVERTICAL) wm_ungetkey(-1);
     else wm_ungetkey(-3);
     break;
   case KEY_left:
     if(m->Control&wm_mHORIZONTAL) wm_ungetkey(-2);
     else wm_ungetkey(-3);
     break;
   case KEY_right:
     if(m->Control&wm_mHORIZONTAL)wm_ungetkey(-1);
     else wm_ungetkey(-3);
     break;
   case KEY_ESC:  Exit=1; break;
   case KEY_ENTER:
     if(m->current->enter.exec==NULL) { wm_ungetkey(-4);break;}
     if(m->current->Control&wm_iSUBMENU)
     {
      if(wm_Menu(m->current->enter.submenu)) wm_ungetkey(-4);
     }
     else
     {
      key=(*m->current->enter.exec)(m);
      switch(key)
      {
       case wm_OK:                       break;
       case wm_mSELECT: wm_ungetkey(-4); break;
       case wm_mREDRAW: wm_ungetkey(-5); break;
       default:         Exit=2;          break;
      }
     }
    break;
   case -1:  /* next item */
     tmp=m->current;
     if(tmp->next==NULL) tmp=m->first;
     else tmp=tmp->next;
     wm_ungetkey(-10);
    break;
   case -2:  /* prev item */
     tmp=m->first;
     if(tmp==m->current) while(tmp->next!=NULL) tmp=tmp->next;
     else while(tmp->next!=m->current) tmp=tmp->next;
     wm_ungetkey(-10);
    break;
   case -10:
     wmx_DisplayItem(m,m->current,m->wHandle,m->setup.attr_title,m->setup.attr_nactget);
     wmx_DisplayItem(m,tmp,m->wHandle,m->setup.attr_title,m->setup.attr_actget);
     m->current=tmp;
    break;
   case -4:   /* item is selecting */
      if(m->current->Control&wm_iCHECKED1)
      {
       tmp=m->first;
       while(tmp!=NULL)
       {
	if(tmp->Control&wm_iCHECKED1)
	{
	 tmp->Control&=~wm_ixSELECTED;
	}
	tmp=tmp->next;
       }
       m->current->Control|=wm_ixSELECTED;
      }
      if(m->current->Control&wm_iCHECKED2)
      {
       if(m->current->Control&wm_ixSELECTED) m->current->Control&=~wm_ixSELECTED;
       else m->current->Control|=wm_ixSELECTED;
      }
      wm_DisplayMenu(m);
      if(m->current->Control&wm_iRETURN) Exit=2;
    break;
   case -5:
      wm_Delete(m->wHandle);
      wm_AssignMenu(m);
      if(wm_DisplayMenu(m)<0) return(0);
      wm_Show(m->wHandle);
    break;
   case -3: key=key1;
   default:
       tmp=m->first;
       while(tmp!=NULL)
       {
	for(i=0;tmp->name[i];i++)
	 if(tmp->name[i]=='~'&&wm_upper(tmp->name[i+1])==wm_upper(key))
	  {
	   i=-1;
	   wm_ungetkey(KEY_ENTER);
	   wm_ungetkey(-10);
	   break;
	  }
	if(i<0) break;
	tmp=tmp->next;
       }
    break;
  }
 }
 return(Exit-1);
}

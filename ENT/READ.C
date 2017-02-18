#include "stdlib.h"
#include "wm_stdio.h"
#include "wm_keys.h"
#define picAREA 20

wm_picnum(char *str,char *pic,char c,int *pos,int *delt);
wm_picall(char *str,char *pic,char c,int *pos,int *delt);

wm_pictype wm_picture[picAREA]={{'X',wm_picall},{'x',wm_picall},{'9',wm_picnum}};
wm_gettype wm_getdefault={NULL,NULL,KEY_pagedown,KEY_pageup,KEY_ENTER,KEY_ESC};

int wm_maxpic=3;


int wm_getfield(wm_gettype *tab)
{
 wm_fieldtype *field;
 int ok,c,i,j,oldpos,pos,delt,max_pos,curr_pic,ret=0,act,nact;
 wm_windP w;

 field=tab->curr;
 w=wm_Handle2wind(field->wHandle);
 act=w->setup.attr_actget*0x100;
 nact=w->setup.attr_nactget*0x100;
 pos=oldpos=0;
 max_pos=field->dX*field->dY;
 delt=1;
 do{
  ok=0;
  do{
   if(pos<max_pos&&pos>=0)
   {
    for(i=0;i<wm_maxpic;i++)
     if(field->pic[pos]==wm_picture[i].pic)
     {
      ok=1;
      curr_pic=i;
      break;
     }
    if(!ok) pos+=delt;
   }
   else
   {
    pos=oldpos;
   }
  }while(!ok);
  oldpos=pos;
  for(i=0;i<field->dY;i++)
   for(j=0;j<field->dX;j++)
    wm_saychar(w,field->Xbas+j,field->Ybas+i,(field->tmp[j+(i*field->dX)])+act);
  w->Xpos=field->Xbas+(pos%(field->dX+1));
  w->Ypos=field->Ybas+(pos/(field->dX+1));
/*  wm_setcursor(w); */
  c=wm_getkey();
  if(c==tab->next)  { ret= 2;goto cancel;}
  if(c==tab->prev)  { ret=-2;goto cancel;}
  if(c==tab->enter) { ret= 1;goto cancel;}
  if(c==tab->cancel){ ret=-1;goto cancel;}
  switch(c)
  {
   case KEY_up:
     delt=-field->dX;
     if(pos+delt>=0) pos+=delt;
    break;
   case KEY_down:
     delt=field->dX;
     if(pos+delt<max_pos) pos+=delt;
    break;
   case KEY_left:
     delt=-1;
     if(pos+delt>=0) pos+=delt;
    break;
   case KEY_right:
     delt=1;
     if(pos+delt<max_pos) pos+=delt;
    break;
   case KEY_home:
     delt=1;
     pos=0;
    break;
   case KEY_end:
     delt=-1;
     pos=max_pos-1;
    break;
   default:
     delt=1;
    (*wm_picture[curr_pic].picproc)(field->tmp,field->pic,c,&pos,&delt);
    break;
  }
 cancel:;
 }while(!ret);
  for(i=0;i<field->dY;i++)
   for(j=0;j<field->dX;j++)
    wm_saychar(w,field->Xbas+j,field->Ybas+i,(field->tmp[j+(i*field->dX)])+nact);
 return(ret);
}

int wmx_readgets(wm_gettype *tab)
{
 int key,exit=0,i;
 wm_fieldtype *tmp;

 if(tab==NULL||tab->begin==NULL) return(wm_BADfield);
 tab->curr=tab->begin;
 while(!exit)
 {
  key=wm_getfield(tab);
  switch(key)
  {
   case  1:
    tmp=tab->begin;
    while(tmp!=NULL)
    {
     for(i=0;i<tmp->dX*tmp->dY;i++) tmp->str[i]=tmp->tmp[i];
     tmp->str[i]=0;
     tmp=tmp->next;
    }
     exit=2;
    break;
   case -1:
     exit=1;
    break;
   case  2:
     if(tab->curr->next!=NULL) tab->curr=tab->curr->next;
    break;
   case -2:
     tmp=tab->begin;
     if(tmp!=tab->curr)
     {
      while(tmp->next!=tab->curr) tmp=tmp->next;
      tab->curr=tmp;
     }
    break;
  }
 }
 tab->curr=tab->begin;
 while(tab->curr!=NULL)
 {
  tmp=tab->curr;
  tab->curr=tmp->next;
  wm_freemem(tmp);
 }
 tab->begin=NULL;
 return(exit-1);
}

wmx_atget(wm_gettype *tab,int wHandle,int x,int y,char *str,char *pic)
{
 wm_fieldtype *new,*tmp;
 wm_windP w;
 int len,i,j,attr;

 w=wm_Handle2wind(wHandle);
 if(w==NULL) return(wm_BADhandle);

 if(tab==NULL) return(wm_BADtable);
 for(len=0;pic[len];len++);
 new=calloc(1,sizeof(wm_fieldtype)+len+len);
 if(new==NULL) return(wm_BADmem);
 new->pic=(char *)new+sizeof(wm_fieldtype);
 new->tmp=new->pic+len;
 new->str=str;
 new->wHandle=wHandle;

 for(i=0;i<len;i++)
 {
  new->tmp[i]=new->pic[i]=pic[i];
  for(j=0;j<wm_maxpic;j++)
   if(wm_picture[j].pic==pic[i]) new->tmp[i]=str[i];
 }
 new->Xbas=x; new->dX=len;
 new->Ybas=y; new->dY=1;
 new->next=NULL;
 if(tab->begin==NULL) tab->begin=new;
 else
 {
  tmp=tab->begin;
  while(tmp->next!=NULL) tmp=tmp->next;
  tmp->next=new;
 }
 attr=w->setup.attr_nactget*0x100;
  for(i=0;i<new->dY;i++)
   for(j=0;j<new->dX;j++)
    wm_saychar(w,new->Xbas+j,new->Ybas+i,(new->tmp[j+(i*new->dX)])+attr);
 return(wm_OK);
}

int wmx_get(wm_gettype *tab,int wHandle,char *str,char *pic)
{
 wm_windP w;
 w=wm_Handle2wind(wHandle);
 if(w==NULL) return(wm_BADhandle);
 return wmx_atget(tab,wHandle,w->Xpos,w->Ypos,str,pic);
}


wm_picall(char *str,char *pic,char c,int *pos,int *delt)
{
 if(pic[*pos]=='X') c=wm_upper(c);
 else c=wm_lower(c);
 str[*pos]=c;
 (*pos)++;
 (*delt)=1;
 return;
}

wm_picnum(char *str,char *pic,char c,int *pos,int *delt)
{
 if((c<=pic[*pos])&&(c>='0'))
 {
  str[*pos]=c;
  (*pos)++;
  (*delt)=1;
 }
 else *delt=0;
 return(wm_OK);
}

int wm_addpic(char pic, int (*func)(char *str,char *pic,char c,int *pos,int *delt))
{
 int k,i,ret=wm_OK;
 k=-1;
 for(i=0;i<wm_maxpic;i++) if(wm_picture[i].pic==pic) k=i;
 if(k==-1)
 {
  k=wm_maxpic;
  if(wm_maxpic<picAREA) wm_maxpic++;
  else ret=wm_BADmem;
 }
 wm_picture[k].pic=pic;
 wm_picture[k].picproc=func;
 return(ret);
}

void *wm_delpic(char pic)
{
 int i,j=-1;
 int (*func)(char *str,char *pic,char c,int *pos,int *delt);

 if(!wm_maxpic) return(NULL);
 for(i=0;i<wm_maxpic;i++) if(wm_picture[i].pic==pic) j=i;
 if(j==-1) return(NULL);
 func=wm_picture[j].picproc;
 for(;j<wm_maxpic;j++) wm_picture[j]=wm_picture[j+1];
 wm_maxpic--;
 return((void *)func);
}

char wm_upper(char c)
{
 if(c>='a'&&c<='z') c=c+'A'-'a';
 if(c>='†'&&c<='Ø') c=c+'Ä'-'†';
 if(c>='‡'&&c<='Ô') c=c+'ê'-'‡';
 if(c=='Ò') c='';
 return c;
}

char wm_lower(char c)
{
 if(c>='A'&&c<='Z') c=c+'a'-'A';
 if(c>='Ä'&&c<='è') c=c+'†'-'Ä';
 if(c>='ê'&&c<='ü') c=c+'‡'-'ê';
 if(c=='') c='Ò';
 return c;
}

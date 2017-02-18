#include "wm_stdio.h"

int wm_exchg(wm_windP w1,wm_windP w2)
{
 wm_windP tmp;
 int k1,k2,i;

 if(w1==NULL||w2==NULL||w1==wmx_TOP||w2==wmx_TOP||w1==w2) return(wm_BADhandle);

 k1=0;tmp=wmx_TOP;while(tmp->next!=w1) {tmp=tmp->next;k1++;}
 tmp->next=w1->next;
 k2=0;tmp=wmx_TOP;while(tmp->next!=w2) {tmp=tmp->next;k2++;}
 tmp->next=w2->next;

 tmp=wmx_TOP;for(i=0;i<k2;i++) tmp=tmp->next;
 w1->next=tmp->next;tmp->next=w1;
 tmp=wmx_TOP;for(i=0;i<k1;i++) tmp=tmp->next;
 w2->next=tmp->next;tmp->next=w2;

 wmx_resetmap();
 wmx_redraw();
 return(wm_OK);
}

int wm_top(wm_windP w)
{
 wm_windP tmp;

 if(wmx_TOP==NULL) return(wm_BADhandle);
 tmp=wmx_TOP;while(tmp->next!=NULL) tmp=tmp->next;
 return wm_exchg(w,tmp);
}


#include <conio.h>
#include "wm_stdio.h"


main()
{
 int m,i;

 wm_Init();
  getch();
 for(i=0;i<10;i++)
  {
  m=wm_Create(10,5,70,20,-1,-1,CURSOR|BORDER|SHADOW,"Title 1",wm_xCENTER);
  getch();
  wm_Delete(m);
  }
 wm_Deinit();
 return(0);
}



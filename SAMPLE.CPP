#include <conio.h>
#include "wm_dsk.hpp"
#include "wm_win.hpp"

main()
{
 Desktop Dsk;
 Window  Win;

 Dsk.Register(&Win);
 Win.Open(5,5,20,20);
 getch();
 Win.Close();

 Dsk.Supervisor();
 return 0;

}


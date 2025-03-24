
#include <genesis.h>

int main()
{

    VDP_setScreenWidth256();
    VDP_setScreenHeight224();
    

    while(1)
    {


        SYS_doVBlankProcess();


    }
    return (0);
}

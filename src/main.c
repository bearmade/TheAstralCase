
#include <genesis.h>
#include <resources.h>
#include <../inc/gamemanager.h>


int main()
{

    VDP_setScreenWidth256();
    VDP_setScreenHeight224();

    
    
    showSegaLogo();
    while(1)
    {



        SYS_doVBlankProcess();


    }
    return (0);
}


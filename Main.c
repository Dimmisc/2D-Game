#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string.h>
#include "source/SEL.h"




int WinMain(int argc, char* argv[]){
    WindowSettings WS;
    WS.height = 1060;
    WS.width = 1920;
    strcpy(WS.name, "Start");
    WS.x = 20;
    WS.y = 0;
    SEL_Window *Window = SEL_init(&WS);
    printf("%d\n", Window->WindowSettings.height);
    printf("%d\t%d\n", sizeof(Sprite), sizeof(ParametresSprite));
    SEL_Start(60, Window); // Now dont work because not all structures are fulling after initialisation
    SEL_Exit();

    return 0;
}
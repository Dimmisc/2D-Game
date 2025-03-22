#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string.h>


#include "source/SEL.h"


int WinMain(int argc, char* argv[]){

    WindowSettings WS;
    WS.height = 1000;
    WS.width = 1500;
    strcpy(WS.name, "Start");
    WS.x = 0;
    WS.y = 0;
    SEL_Window *Window = SEL_init(&WS);
    printf("%d\t%d\n", sizeof(Sprite), sizeof(ParametresSprite));
    SEL_Exit();
    return 0;
}
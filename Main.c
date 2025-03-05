#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <string.h>


#include "source/SEL.h"


int WinMain(int argc, char* argv[]){
    SEL_Window *Window;
    WindowSettings WS;
    WS.height = 1000;
    WS.width = 1500;
    // strcpy(WS.name,"Start");
    WS.x = 0;
    WS.y = 0;
    SEL_init(Window, &WS);
    printf("Some new!\n");
    char exit[4]="   ";
    while(strcmp(exit, "quit")) {scanf("%s", &exit);}
    return 0;
}
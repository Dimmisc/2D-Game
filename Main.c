#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <string.h>



int WinMain(int argc, char* argv[]){
    printf("Some new!\n");
    char exit[4]="   ";
    while(strcmp(exit, "quit")) {scanf("%s", &exit);}
    return 0;
}
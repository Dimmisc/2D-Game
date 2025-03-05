#ifndef _SEL_H_
#define _SEL_H_


#include "Area/Area.h"

// Needable to Rethink



typedef struct WindowSetting {
    int width;
    int height;
    int x;
    int y;
    char name[15];
} WindowSettings;

typedef struct SEL_Window {
    Layot layots;
    SDL_Window *window;
    SDL_Surface *surface;
    SDL_Renderer *render;
    AreaMap *Map;
    Player *player;
    char Error[30];
    int Ll;
    short int error_continue;
} SEL_Window;

SEL_Window *SEL_init( WindowSettings *settings);
int Moving_of_Sprites(AreaMap *AREA, int speed);
int UpdateScreen(SEL_Window *ARG);
int SEL_Start(int TPS, SEL_Window *Window);
int SEL_WQuit(SEL_Window *ARG);
int SEL_AQuit(AreaMap *Area);
int SEL_Exit();


#endif
#ifndef _SEL_H_
#define _SEL_H_
#include "Area/Area.h"

typedef struct WindowSetting {
    int width;
    int height;
    int x;
    int y;
    char name[15];
} WindowSettings;


typedef struct SWS {
    int height;
    int width;
} SWS ;


typedef struct SEL_Window {
    char Error[30];
    SDL_Window *window;
    SDL_Surface *surface;
    SDL_Renderer *render;
    SWS WindowSettings;
    AreaMap *Map;
    uint8_t ErrorContinue;
} SEL_Window ;


SEL_Window *SEL_init( WindowSettings *settings);
int Moving_of_Sprites(AreaMap *AREA, int speed);
int UpdateScreen(SEL_Window *ARG);
uint64_t get_monotonic_time_ns();
int SEL_Start(int target_fps, SEL_Window *Window);
int SEL_WQuit(SEL_Window *ARG);
int SEL_AQuit(AreaMap *Area);
int SEL_Exit();


#endif
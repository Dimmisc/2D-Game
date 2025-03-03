#ifndef _SEL_H_
#define _SEL_H_


typedef struct SEL_Window {
    SDL_Window *window;
    SDL_Surface *surface;
    SDL_Renderer *render;
    Layot layots;
    Player *player;
    char Error[30];
    int Ll;
    short int error_continue;
} SEL_Window;

typedef struct WindowSetting {
    int width;
    int height;
    int x;
    int y;
    char name[];
} WindowSettings;



int SEL_init(SEL_Window *ARG, WindowSettings *settings);
int SEL_Moving_of_Sprites(AreaMap *AREA, int speed);
int UpdateScreen(SEL_Window *ARG);
int SEL_Start(int TPS, SEL_Window *Window);
int SEL_WQuit(SEL_Window *ARG);
int SEL_AQuit(AreaMap *Area);
int SEL_Exit();


#endif
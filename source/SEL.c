#define _SEL_C_

#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <SDL2/SDL_image.h>

#include "SEL.h"



SEL_Window *SEL_init(WindowSettings *settings) {
    SEL_Window ARG;
    printf("Start initialization Window: %s\n", settings->name);
    int succes = 0;
    ARG.window = SDL_CreateWindow(settings->name,
                                   settings->x,
                                   settings->y,
                                   settings->width,
                                   settings->height,
                                   SDL_WINDOW_SHOWN
                                   );
    if (ARG.window == NULL) {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return NULL;
    } else {
        printf("Window is created: %s\n", settings->name);
        ARG.render = SDL_CreateRenderer(ARG.window, -1, SDL_RENDERER_ACCELERATED);
        if (ARG.render == NULL) {
            printf( "Render could not be created! SDL_Error: %s\n", SDL_GetError() );
            return NULL;
        } else {
            printf("Render is created. Window: %s\n", settings->name);
        }
    }
    return &ARG;
}

int Moving_of_Sprites(AreaMap *AREA, int speed) {
    int succes = 1, truth = 0;
    // for (int i=0;i<AREA->sizeflexingsprites;i++) {
    //     //truth = InitEventSprite(AREA->flexingsprites[i]); //It will be avalible

    //     if (truth == 0) {
    //         succes = 0;
    //         //strncpy(AREA->error, GetSpriteError(), 30); // It will be avalible
    //         break;
    //     }
    // }
    return succes;
}


int Update_shown_sprites(AreaMap *Map){
    
    return 1;
}


int UpdateScreen(SEL_Window *ARG) {
    static int screenupdate = 0;
    int succes = 1;
    if (screenupdate > 0){
        SDL_RenderClear(ARG->render);
    }
    printf("%d screen update\n", ++screenupdate);
    uint8_t _PlayerLayot = ARG->Map->player.layot;
    uint8_t _Len_layot = ARG->Map->cellsArg.layots;
    Player * _PlayerP = &ARG->Map->player;

    printf("%d screen update\n", ++screenupdate);
    int _Px = _PlayerP->arguments.pah.x, _Py = _PlayerP->arguments.pah.y;
    int Hw = ARG->WindowSettings.width / 2, Hh = ARG->WindowSettings.height / 2;
    for (int layot = 0; layot < _Len_layot; layot++) {
        if (_PlayerLayot == layot) {
            SDL_Rect Prect = {Hh, Hw, 0, 0};
            SDL_Point PCenterR = {Hh + (_PlayerP->SHeight / 2), Hw + (_PlayerP->SWidth / 2)};
            SDL_RenderCopyEx(ARG->render,
                             _PlayerP->texture, 
                             NULL, 
                             &Prect, 
                             _PlayerP->arguments.rotation, 
                             &PCenterR,
                             _PlayerP->arguments.reflaction);
        }

        int CBNW = (int)ceil(((float)_Px + Hw) / ARG->Map->cellsArg.width), 
        CBNH = (int)ceil(((float)_Py + Hh) /ARG->Map->cellsArg.height);


        for (int sW = (_Px - Hw) / ARG->Map->cellsArg.width; sW < CBNW; sW++){
            for (int sH = (_Py - Hh) / ARG->Map->cellsArg.height; sH < CBNH; sH++) {
                for (int sprite = 0; sprite < ARG->Map->cells[sW][sH].layots[layot].LenSprites;sprite++) {

                    Sprite *P_TO_S = &ARG->Map->cells[sW][sH].layots[layot].sprites[sprite];
                    SDL_Rect Srect = {P_TO_S->arguments.pah.x - _PlayerP->arguments.pah.x + Hw,
                                      P_TO_S->arguments.pah.y - _PlayerP->arguments.pah.y + Hh, 0, 0};
                    SDL_Point SCenterR = {P_TO_S->arguments.pah.x - _PlayerP->arguments.pah.x + Hw, 
                                          P_TO_S->arguments.pah.y - _PlayerP->arguments.pah.y + Hh};

                    
                    if (Srect.x < ARG->WindowSettings.width & Srect.x > 0 & Srect.y < ARG->WindowSettings.height & Srect.y > 0){
                        int true = SDL_RenderCopyEx(ARG->render,
                                        P_TO_S->typeSet->STexture,
                                        NULL,
                                        &Srect,
                                        P_TO_S->arguments.rotation,
                                        &SCenterR,
                                        P_TO_S->arguments.reflaction
                                        );
                        if (!true) {
                            printf("Error of showing sprite: %s, %d, %d, %d, %d;\n SDL Error: %s",
                                   P_TO_S->name, Srect.x, Srect.y, SCenterR.x, SCenterR.y, SDL_GetError());
                        }
                    }
                }
            }
        }
    }
    SDL_RenderPresent(ARG->render);
    return succes;
}


/* Function of starting playing your own game  */
int SEL_Start(int TPS, SEL_Window *Window) {
    struct timeval st, vt;
    int Exit = 0;
    double change_coeficent = 1 / TPS;
    gettimeofday(&st, 0);
    double started_game_time = (st.tv_sec + (double)st.tv_usec / 100000);
    double cst = (st.tv_sec + (double)st.tv_usec / 100000) + change_coeficent, mt = 0;

    printf("Game started, time: %lf, Window: {}\n", started_game_time);

    while (Exit == 0) {
        gettimeofday(&vt, 0);
        mt = vt.tv_sec + (double)vt.tv_usec / 100000;
        if ((mt - cst) >= 0) {
            UpdateScreen(Window);
            cst += change_coeficent;
        }
    }
    printf("Game ended, Error: %s\n", Window->Error);
    return 1;
}


/*This Function is necessary t brake your window */
int SEL_WQuit(SEL_Window *ARG) {
    SDL_DestroyRenderer( ARG->render );
    SDL_FreeSurface( ARG->surface );
    SDL_DestroyWindow( ARG->window );
    SDL_Quit();
    return 1;
}

int SEL_AQuit(AreaMap *Area){
    CloseArea(Area);
    return 1;
}

int SEL_Exit() {
    SDL_Quit();
    IMG_Quit();
    return 1;
}

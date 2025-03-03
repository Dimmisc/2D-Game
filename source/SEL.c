#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Area/Area.h"
#include "sprites/sprite.h"
#include "effects/effect.h"
#include "SEL.h"



int SEL_init(SEL_Window *ARG, WindowSettings *settings) {
    int succes = 0;
    ARG->window = SDL_CreateWindow(settings->name,
                                   settings->x,
                                   settings->y,
                                   settings->width,
                                   settings->height,
                                   SDL_WINDOW_SHOWN
                                   );
    if (ARG->window == NULL) {
        
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
    } else {
        ARG->render = SDL_CreateRenderer(ARG->window, -1, SDL_RENDERER_ACCELERATED);
        if (ARG->render == NULL) {
            printf( "Render could not be created! SDL_Error: %s\n", SDL_GetError() );
        } else {
            succes = 1;
        }
    }
    return succes;
}

int SEL_Moving_of_Sprites(AreaMap *AREA, int speed) {
    int succes = 1, truth = 0;
    for (int i=0;i<AREA->sizeflexingsprites;i++) {
        //truth = InitEventSprite(AREA->flexingsprites[i]); //It will be avalible

        if (truth == 0) {
            succes = 0;
            //strncpy(AREA->error, GetSpriteError(), 30); // It will be avalible
            break;
        }
    }
    return succes;
}

int UpdateScreen(SEL_Window *ARG) {
    int succes = 1;
    SDL_RenderClear(ARG->render);
    for (int i=0;i<ARG->lsS; i++) {
        SDL_RenderCopyEx(ARG->render,
                         ARG->shownSprites[i]->spriteTexture,
                         NULL,
                         &ARG->shownSprites[i]->arguments.parametres,
                         ARG->shownSprites[i]->arguments.rotation,
                         &ARG->shownSprites[i]->arguments.center_rotation,
                         ARG->shownSprites[i]->reflaction
                         );
    }
    SDL_RenderPresent(ARG->render);
    return succes;
}


/* Function of starting playing your own game*/
int SEL_Start(int TPS, SEL_Window *Window) {
    struct timeval st, vt;
    int Exit = 0;
    double change_coeficent = 1 / TPS;
    gettimeofday(&st, 0);
    double started_game_time = (st.tv_sec + (double)st.tv_usec / 100000);
    double cst = (st.tv_sec + (double)st.tv_usec / 100000) + change_coeficent, mt = 0;
    printf("Game started, time:%lf", started_game_time);
    while (Exit == 0) {
        gettimeofday(&vt, 0);
        mt = vt.tv_sec + (double)vt.tv_usec / 100000;
        if ((mt - cst) >= 0) {
            UpdateScreen(Window);
            cst += change_coeficent;
        }
    }
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

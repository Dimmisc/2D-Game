#ifndef _Player_H_
#define _Player_H_


#include "sprites/sprite.h"


typedef struct Player {
    char name[15];
    SDL_Texture *spriteTexture;
    parametresSprite arguments;
    SDL_RendererFlip reflaction;
    int SWidth;
    int SHeight;
} Player;



#endif
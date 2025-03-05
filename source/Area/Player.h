#ifndef _Player_H_
#define _Player_H_


#include "sprites/sprite.h"


typedef struct Player {
    char name[15];
    Inventory inventory;
    SDL_Texture *spriteTexture;
    ParametresSprite arguments;
    SDL_RendererFlip reflaction;
    unsigned int type;
    int SWidth;
    int SHeight;
} Player;



#endif
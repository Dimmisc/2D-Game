#ifndef _Player_H_
#define _Player_H_


#include "../sprites/sprite.h"


typedef struct Player {
    char name[15];
    Inventory inventory;
    SDL_Texture *texture;
    ParametresSprite arguments;
    SDL_Point CenterR;
    int SWidth;
    int SHeight;
    uint8_t type;
    uint8_t layot;
} Player;



#endif
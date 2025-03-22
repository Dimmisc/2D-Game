#ifndef _Player_H_
#define _Player_H_


#include "../sprites/sprite.h"

typedef struct PlayerType {
    SDL_Texture *playerTexture;
    
    uint8_t type;
} PlayerType;



typedef struct Player {
    char name[15];
    Inventory inventory;
    ParametresSprite arguments;
    PlayerType *TypeSet;
    uint8_t layot;
} Player;



#endif
#ifndef _Player_H_
#define _Player_H_


#include "../sprites/sprite.h"


typedef struct PlayerType {
    SDL_Texture *playerTexture;
    int width;
    int height;
    SDL_Point PointOffset;
    unsigned int type;
} PlayerType;


typedef struct Player {
    char name[15];
    Inventory inventory;
    ParametresSprite arguments;
    PlayerType *TypeSet;
    uint8_t layot;
} Player;


int InitPlayers(SDL_Renderer *RENDER, SDL_Surface *SURFACE);
PlayerType *_loadPlayerType(unsigned int Type);
void QPlayers();


#endif
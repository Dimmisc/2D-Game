#define _Player_C_


#include "Player.h"
#include "../Area.h"

#include <SDL2/SDL_image.h>

typedef struct _PlayerPattern{
    char ImgPath[40];
    uint16_t textureHeight;
    uint16_t textureWidth;
    Point centerOffset;
} _PlayerPattern;

_PlayerPattern PLAYERTYPES[2] = {{"/PlayersTextures/StartPlayer.png", 128, 256, {0, 0}}, {}};
int PPT = 2;
PlayerType *PlayerTypes = NULL;

int InitPlayers(SDL_Renderer *RENDER, SDL_Surface *SURFACE) {
    size_t some = sizeof(int);
    PlayerTypes = calloc(PPT, sizeof(PlayerType));
    for (int i = 0;i<PPT;i++){
        SURFACE = IMG_Load(PLAYERTYPES[i].ImgPath);
        PlayerTypes[i].playerTexture = SDL_CreateTextureFromSurface(RENDER, SURFACE);
        PlayerTypes[i].height = PLAYERTYPES[i].textureHeight, PlayerTypes[i].width = PLAYERTYPES[i].textureWidth, PlayerTypes[i].PointOffset = PLAYERTYPES[i].centerOffset;
        PlayerTypes[i].type = i;
        SDL_FreeSurface(SURFACE);
    }
    // Types[0].type = 0;
    // Types[0].playerTexture = _loadTexture();
    return 0;
}


PlayerType *_loadPlayerType(unsigned int Type) {
    return &PlayerTypes[Type];
}

void QPlayers() {
    for (int i = 0;i<PPT;i++){
        SDL_DestroyTexture(PlayerTypes[i].playerTexture);
        free(&PlayerTypes[i]);
    }
}
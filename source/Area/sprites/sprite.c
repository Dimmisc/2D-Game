#include <stdlib.h>

#include "sprite.h"



typedef struct {
    char path[100];
    unsigned int _type;
    int width;
    int height;
    SDL_Point centerOffset;
    SDL_RendererFlip reflaction;
    Collision Scolis;
} _Type;


const _Type TYPESET[4];
int _TYPES_COUNT = 4;


_Type SpriteTYPES[2] = {{"source/Area/sprites/Grass.png", .height = 50, .width = 50, .centerOffset = {1, 1}}};
int PST = 1;
type *SpriteTypes = NULL;

int InitSprites(SDL_Renderer *RENDER, SDL_Surface *SURFACE) {
    size_t some = sizeof(int);
    SpriteTypes = calloc(PST, sizeof(type));
    for (int i = 0;i<PST;i++){
        SURFACE = IMG_Load(SpriteTYPES[i].path);
        if (!SURFACE){
            printf("Error: loading Surface. %s\n", SDL_GetError());
        }
        SpriteTypes[i].STexture = SDL_CreateTextureFromSurface(RENDER, SURFACE);
        if (!SpriteTypes[i].STexture){
            printf("Error: Creating Texture Sprite. %s\n", SDL_GetError());
        }
        SpriteTypes[i].height = SpriteTYPES[i].height, 
        SpriteTypes[i].width = SpriteTYPES[i].width, 
        SpriteTypes[i].CenterOffset = SpriteTYPES[i].centerOffset;
        printf("%d %d:: %d %d\n", SpriteTYPES[i].width, SpriteTypes[i].width, SpriteTYPES[i].height, SpriteTypes[i].height);
        SpriteTypes[i].type = i;
        SDL_FreeSurface(SURFACE);
    }
    if (PST == 0){
        printf("Warning Have no Sprite Types\n");
    }
    // Types[0].type = 0;
    // Types[0].playerTexture = _loadTexture();
    printf("S Inited!\n");
    return 0;
}


type *_loadSpriteType(unsigned int Type) {
    return &SpriteTypes[Type];
}

void QSprites() {
    for (int i = 0;i<PST;i++){
        SDL_DestroyTexture(SpriteTypes[i].STexture);
        free(&SpriteTypes[i]);
    }
}
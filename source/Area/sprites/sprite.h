#ifndef _Sprite_H_
#define _Sprite_H_


#include <SDL.h>


typedef struct {
    unsigned int item_id;
    unsigned int count;
} Item;

typedef struct {
    Item **items;
    int Litems;
} Inventory;

typedef struct {
    SDL_Rect parametres;
    double rotation;
    SDL_Point center_rotation;
    unsigned short int layot;
} parametresSprite;

typedef struct Sprite {
    SDL_Texture *spriteTexture;
    parametresSprite arguments;
    SDL_RendererFlip reflaction;
    char name[15];
} Sprite;

typedef struct ThinkSprite {
    SDL_Texture *spriteTexture;
    parametresSprite arguments;
    char name[15];
    SDL_RendererFlip reflaction;
    int typemove;
} ThinkSprite;

typedef struct InventorySprite {
    SDL_Texture *spriteTexture;
    parametresSprite arguments;
    char name[15];
    SDL_RendererFlip reflaction;
    int typemove;
} InventorySprite;

#endif
#ifndef _Sprite_H_
#define _Sprite_H_


#include <SDL.h>


typedef struct {
    unsigned int type;
    int width;
    int height;
    char path[30];
    SDL_RendererFlip reflaction;
} Type;


typedef struct {
    Type types[4];
    unsigned int LT;
} ConstTypes;


typedef struct {
    unsigned int item_id;
    unsigned int count;
} Item;

typedef struct {
    Item *items;
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
    unsigned int type;    
} Sprite;

typedef struct ThinkSprite {
    Inventory inventory;
    SDL_Texture *spriteTexture;
    parametresSprite arguments;
    char name[15];
    SDL_RendererFlip reflaction;
    int typemove;
    unsigned int type;
} ThinkSprite;

typedef struct InventorySprite {
    Inventory inventory;
    SDL_Texture *spriteTexture;
    parametresSprite arguments;
    char name[15];
    SDL_RendererFlip reflaction;
    int typemove;
    unsigned int type;
} InventorySprite;

Type *Give_Type(unsigned int type);

#endif
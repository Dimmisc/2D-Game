#ifndef _Sprite_H_
#define _Sprite_H_

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdint.h>

typedef SDL_Point Point;

typedef struct {
    SDL_RendererFlip reflaction;
    SDL_Rect pah;
    double rotation;
    uint8_t layot;
} ParametresSprite;

typedef struct Rectangle {
    SDL_Point TLPoint;
    SDL_Point BRPoint;
} Rectangle;

typedef struct Collision {
    Rectangle *rectangles;
    int16_t SRect;
} Collision;


typedef struct type{
    uint16_t type;
    Collision TypeCollision;
    SDL_Point CenterOffset;
    int height;
    int width;
    SDL_Texture *STexture;
} type;


typedef struct Sprite {
    char name[15];
    ParametresSprite arguments;
    type *typeSet;
    uint32_t id;   
} Sprite;   



typedef struct {
    unsigned int item_id;
    unsigned int count;
} Item;


typedef struct {
    Item *items;
    int Litems;
} Inventory;



typedef struct ThinkSprite {
    char name[15];
    Inventory inventory;
    SDL_Texture *spriteTexture;
    ParametresSprite arguments;
    SDL_RendererFlip reflaction;
    int typemove;
    unsigned int type;
} ThinkSprite;


typedef struct InventorySprite {
    char name[15];
    Inventory inventory;
    SDL_Texture *spriteTexture;
    ParametresSprite arguments;
    SDL_RendererFlip reflaction;
    int typemove;
    unsigned int type;
} InventorySprite;

int InitSprites(SDL_Renderer *RENDER, SDL_Surface *SURFACE);
type *_loadSpriteType(unsigned int Type);

#endif
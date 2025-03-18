#ifndef _Sprite_H_
#define _Sprite_H_

#include <stdlib.h>
#include <SDL.h>
#include <stdint.h>

typedef struct SDL_Point Point;

typedef struct {
    char path[30];
    unsigned int type;
    int width;
    int height;
    SDL_Point Center;
    SDL_RendererFlip reflaction;
} Type;


typedef struct Rectangle {
    int U_x;
    int U_y;
    int D_x;
    int D_y;
} Rectangle;


typedef struct Collision {
    Rectangle *rectangles;
    int count;
} Collision;

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
} ParametresSprite;


typedef struct Sprite {
    char name[15];
    Collision collision;
    SDL_Texture *spriteTexture;
    ParametresSprite arguments;
    SDL_RendererFlip reflaction;
    unsigned int id;
    unsigned int type;    
} Sprite;


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


Type *Give_Type(unsigned int type);

#endif
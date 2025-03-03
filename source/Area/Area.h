#ifndef _AreaBox_H_
#define _AreaBox_H_

#include "sprites/sprite.h"
#include "Player.h"
#include "Area.h"


typedef struct Layot {
    Sprite *sprites;
    int LenSprites;
} Layot;


typedef struct Cell {
    Layot *layots;
    int SizeLayots;
} Cell;


typedef struct CellSettings {
    int height;
    int width;
    int massHeight;
    int massWidth;
} CellSettings;


typedef struct AreaMap {
    char error[30];
    Cell **cells;
    CellSettings cellsArg;
    Player player;
    int mapwidth;
    int mapheight;
    //effect* effects;
    //int sizeffects;
} AreaMap;


int *Area(unsigned int inwidth, unsigned int inheight, unsigned int inlayots);


#endif
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


int CreateSprite(AreaMap *Map, int x, int y, int layot, char name[15], unsigned int type, double rotation, SDL_Renderer *Render);
int Load_Texture(SDL_Texture **Place, Type *type, SDL_Renderer *Render);
int ChangePositionSprite_BI(AreaMap *Map, unsigned long int id, int x, int y, SDL_Point Vector);
Sprite *MSprite_BI(AreaMap *Map, unsigned long int id, int x, int y);
int FreeSprite(Sprite *SPRITE);
int CloseArea(AreaMap *Map);
char *AreaGetError(AreaMap *folder);


#endif
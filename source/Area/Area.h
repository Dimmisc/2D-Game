#ifndef _AreaBox_H_
#define _AreaBox_H_

#include "sprites/sprite.h"
#include "Player/Player.h"


typedef struct Layot {
    Sprite *sprites;
    int LenSprites;
    uint8_t height;
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
    int layots;
} CellSettings;


typedef struct AreaMap {
    char error[30];
    CellSettings cellsArg;
    Player player;
    char name[15];
    Cell **cells;
    int mapwidth;
    int mapheight;
    //effect* effects;
    //int sizeffects;
} AreaMap;

int _InitMap(char *NAME, SDL_Renderer *RENDER, SDL_Surface *SURFACE);
int CreateSprite(AreaMap *Map, int x, int y, int layot, char name[15], unsigned int type, double rotation, SDL_Renderer *Render);
int _loadTexture(SDL_Texture **Place, char path[], SDL_Renderer *Render);
int ChangePositionSprite_BI(AreaMap *Map, unsigned long int id, int x, int y, SDL_Point Vector);
Sprite *MSprite_BI(AreaMap *Map, unsigned long int id, int x, int y);
int CloseArea(AreaMap *Map);
char *AreaGetError(AreaMap *folder);



#endif
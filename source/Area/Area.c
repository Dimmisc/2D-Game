#define _Area_C_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL_image.h>


#include "Area.h"
    
typedef Point cord;

/* 
*   need to do libiration sprite structures
*/

 cord find_cell(int x, int y, AreaMap *Map) {
    cord arg;
    arg.x = x / Map->cellsArg.height;
    arg.y = y / Map->cellsArg.width;
    return arg;
 }


AreaMap *Load_Area() {
    AreaMap folder;
    return &folder;
}


int SafeArea(AreaMap *Map){
    return 1;
}


AreaMap *CreateSprite(AreaMap *Map, int x, int y, int layot, char name[15], unsigned int type, double rotation, SDL_Renderer *Render) {
    cord nsc = find_cell(x, y, Map);
    Layot *P_to_L = &Map->cells[nsc.x][nsc.y].layots[layot];
    Type *New_Sprite_type = Give_Type(type);
    P_to_L->LenSprites++;
    Load_Texture(&P_to_L->sprites[P_to_L->LenSprites].spriteTexture, type, Render);
    P_to_L->sprites = realloc(P_to_L->LenSprites, (sizeof(Sprite) * P_to_L->LenSprites));
    strncpy(P_to_L->sprites[P_to_L->LenSprites].name, name, 15);
    P_to_L->sprites[P_to_L->LenSprites].type = type;
    P_to_L->sprites[P_to_L->LenSprites].arguments.layot = layot;
    P_to_L->sprites[P_to_L->LenSprites].arguments.parametres.x = x;
    P_to_L->sprites[P_to_L->LenSprites].arguments.parametres.y = y;
    P_to_L->sprites[P_to_L->LenSprites].arguments.rotation = rotation;
    P_to_L->sprites[P_to_L->LenSprites].arguments.center_rotation = New_Sprite_type->Center;
    P_to_L->sprites[P_to_L->LenSprites].reflaction = New_Sprite_type->reflaction;
    return 1;
}


int Load_Texture(SDL_Texture **Place, Type *type, SDL_Renderer *Render){
    SDL_Surface *FSurface = IMG_Load(type->path);
    *Place = SDL_CreateTextureFromSurface(Render, FSurface);
    SDL_FreeSurface(FSurface);
    return 1;
}


AreaMap *ChangePositionSprite(AreaMap *Map, unsigned int id, SDL_Point Vector) {
    
    return 1;
}


Sprite *ReturnSprite_BI(AreaMap *Map, unsigned int id) { // Returned pointer to Sprite by finding it's id
    Sprite sprite;
    return &sprite;
}


int FreeSprite(Sprite *SPRITE){
    SDL_DestroyTexture(SPRITE->spriteTexture);
    for (int i=0;i<SPRITE->collision.count;i++) {
        free(&SPRITE->collision.rectangles);
    }
    free(&SPRITE->collision.rectangles);
    return 1;
}


void CloseArea(AreaMap *Map){
    for (int i=0; i<Map->cellsArg.massWidth;i++) {
        for (int j=0;j<Map->cellsArg.massHeight;j++) {
            for (int l=0;l<Map->cells[i][j].SizeLayots; l++) {
                for (int s=0;s<Map->cells[i][j].layots[l].LenSprites; s++) {
                    FreeSprite(&Map->cells[i][j].layots[l].sprites[s]);
                    free(&Map->cells[i][j].layots[l].sprites[s]);
                }
                free(&Map->cells[i][j].layots[l]);
            }
            free(&Map->cells[i][j]);
        }
    }
    return 1;
}


char AreaGetError(AreaMap *folder){
    return folder->error;
}


/*
AreaMap *moveright(char namesp byrite[15], int speed){
    while (strcmp(folder.sprites[i].name, namesprite) == 0 && i < folder.sizesprites - 1){
        i++;
    }
    if (strcmp(namesprite, folder.sprites[i].name) == 0){
        strcpy(folder.error, "No sprite with this name");
        return &folder;
    }
    folder.sprites[i].posy++;
    i = 0;
    return &folder;
}

AreaMap *moveleft(char namesprite[15], int speed){
    while (strcmp(folder.sprites[i].name, namesprite) == 0 && i < folder.sizesprites - 1){
        i++;
    }
    if (strcmp(namesprite, folder.sprites[i].name) == 0){
        strcpy(folder.error, "No sprite with this name");
        return &folder;
    }
    folder.sprites[i].posy -= 1;
    i = 0;
    return &folder;
}

AreaMap *moveup(char namesprite[15], int speed){
    while (strcmp(folder.sprites[i].name, namesprite) == 0 && i < folder.sizesprites - 1){
        i++;
    }
    if (strcmp(namesprite, folder.sprites[i].name) == 0){
        strcpy(folder.error, "No sprite with this name");
        return &folder;
    }
    folder.sprites[i].posx++;
    i = 0;
    return &folder;
}

AreaMap *movedown(char namesprite[15], int speed){
    while (strcmp(folder.sprites[i].name, namesprite) == 0 && i < folder.sizesprites - 1){
        i++;
    }
    if (strcmp(namesprite, folder.sprites[i].name) == 0){
        strcpy(folder.error, "No sprite with this name");
        return &folder;
    }
    folder.sprites[i].posx -= 1;
    i = 0;
    return &folder;
}
*/
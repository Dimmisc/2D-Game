#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Area.h"

    
int Area(unsigned int width, unsigned int height, unsigned int layots) {
    AreaMap folder;
    folder.mapheight = height;
    folder.mapwidth = width;
    folder.maplayots = layots;
    //folder.sizeffects = 0;
    folder.sizesprites = 0;
    folder.sprites = (sprite*) malloc(sizeof(sprite) * 1);
    //folder.effects = (effect*) malloc(sizeof(effect) * 1);
    return &folder;
}

AreaMap *CreateSprite(AreaMap *folder, char name[15], int x, int y, int angle) {
    if (&folder) {
        folder->sizesprites++;
        folder->sprites = realloc(folder->sprites, (sizeof(sprite) * folder->sizesprites));
        folder->sprites[folder->sizesprites].arguments.parametres.x = x;
        folder->sprites[folder->sizesprites].arguments.parametres.y = y;
        folder->sprites[folder->sizesprites].arguments.layot = 1;
        folder->sprites[folder->sizesprites].arguments.rotation = angle;
        //folder.sprites[folder->sizesprites].reflaction = {0, 0, 0, 0};
        strncpy(folder->sprites[folder->sizesprites].name, name, 15);
        return 1;
    } else {
        printf("Error: Not initialisated Map!");
        return 0;
    }
}

AreaMap *ChangePositionSprite(AreaMap *folder, char namesprite[15], SDL_Rect *Argchange){
    int succes = 0;
    i = 0;
    while (strcmp(folder->sprites[i].name, namesprite) == 0 && i < folder->sizesprites - 1){i++;}
    if (i == folder->sizesprites) {
        strcpy(folder->error, "No sprite with this name");
        return 0;
    } else {
        folder->sprites[i].arguments.parametres.x = Argchange->x;
        folder->sprites[i].arguments.parametres.y = Argchange->y;
        succes = 1;
    }
    return 1;
}

Sprite *ReturnNSprite(AreaMap *folder, int n){
    if (n <= folder->sizesprites){
        return &folder->sprites[n];
    }
    else {
        strcpy(folder->error, "Error in function ReturnNSprite");
        return 1;
    }
}

void CloseArea(AreaMap *folder){
    i = 0;
    free(folder->sprites);
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
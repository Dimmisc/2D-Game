#include <string.h>

#include "MapLoad.h"

#include "../sprites/sprite.h"
#include "../Player/Player.h"
#include "../Area.h"


// int _load_sprite(char *STRING[]) {

//     return 1;
// }


// int _load_player(char *STRING[]) {
//     return 1;
// }


// int _load_Map(char *Map_Name[]) {
//     return 1;
// }


int _save_sprite(Sprite *SPRITE){
    return 1;
}


int _save_player(Player *PLAYER){
    return 1;
}


int SaveMap(AreaMap *MAP){
    char Map_File[10] = strcat(MAP->name, ".txt");
    FILE *Map_File = fopen(Map_File, "w");
    char Map_File[1000];




    
    char ns[10];
    snprintf(ns, sizeof ns, "%d", MAP->cellsArg.layots);
    strcat(Map_File, strcat(strcat(strcat("M:", MAP->name), ";"), ns));


    fclose(Map_File);
    return 1;
}


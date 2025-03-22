#define _Player_C_


#include "Player.h"
#include "../Area.h"


PlayerType Types[2] = {{}, {}};
int ST = 2;

int _InitPlayers(SDL_Renderer *render, ){
    SDL_Surface *FSurface = NULL;
    for (int i = 0;i<ST;  )
    Types[0].type = 0;
    Types[0].playerTexture = _loadTexture();

}


int _loadPlayer(){

}
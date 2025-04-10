#define _Player_C_


#include "Player.h"
#include "../Area.h"

#include <SDL2/SDL_image.h>

typedef struct _PlayerPattern{
    char ImgPath[100];
    uint16_t textureHeight;
    uint16_t textureWidth;
    Point centerOffset;
} _PlayerPattern;

_PlayerPattern PLAYERTYPES[1] = {{"source/Area/Player/PlayersTextures/StartPlayer.png", 128, 256, {0, 0}}};
int PPT = 1;
PlayerType *PlayerTypes = NULL;

int InitPlayers(SDL_Renderer *RENDER, SDL_Surface *SURFACE) {
    size_t some = sizeof(int);
    PlayerTypes = calloc(PPT, sizeof(PlayerType));
    for (int i = 0;i<PPT;i++){
        SURFACE = IMG_Load(PLAYERTYPES[i].ImgPath);
        if (!SURFACE){
            printf("Error loading surface for Player {%s} texture!\n");
        }
        PlayerTypes[i].playerTexture = SDL_CreateTextureFromSurface(RENDER, SURFACE);
        if (!PlayerTypes[i].playerTexture) {
            printf("Error creating texture for Player\n");
        }
        PlayerTypes[i].height = PLAYERTYPES[i].textureHeight,
        PlayerTypes[i].width = PLAYERTYPES[i].textureWidth,
         PlayerTypes[i].PointOffset = PLAYERTYPES[i].centerOffset;
        PlayerTypes[i].type = i;
        SDL_FreeSurface(SURFACE);
    }
    // Types[0].type = 0;
    // Types[0].playerTexture = _loadTexture();
    printf("P Inited!\n");
    return 0;
}


PlayerType *_loadPlayerType(unsigned int Type) {
    return &PlayerTypes[Type];
}

void QPlayers() {
    for (int i = 0;i<PPT;i++){
        SDL_DestroyTexture(PlayerTypes[i].playerTexture);
        free(&PlayerTypes[i]);
    }
}

int _PlayerKeybordManage(Player *Player) {


    uint8_t M_U = 0, M_D = 0, M_L = 0, M_R = 0;
    Uint8* keyboardState = SDL_GetKeyboardState(NULL);
    vector *_argument = &Player->arguments.VectorMotion;
    SDL_RendererFlip *_position = &Player->arguments.reflaction;



    if (keyboardState[SDL_SCANCODE_W] || keyboardState[SDL_SCANCODE_UP]) {
        M_U = 1;
        // Код для движения вперед
    }
    if (keyboardState[SDL_SCANCODE_S] || keyboardState[SDL_SCANCODE_DOWN]) {
        M_D = 1;
        // Код для движения назад
    }
    if (keyboardState[SDL_SCANCODE_A] || keyboardState[SDL_SCANCODE_LEFT]) {
        M_L = 1;
        // Код для движения влево
    }
    if (keyboardState[SDL_SCANCODE_D] || keyboardState[SDL_SCANCODE_RIGHT]) {
        M_R = 1;
        // Код для движения вправо
    }

    // Player Braking

    if (_argument->x !=0 && M_L == 0 && M_R == 0){
        if (_argument->x > 0) {
            _argument->x -= (int) round(_argument->x * 0.1) + 1;
        }
        else {
            _argument->x -= (int) round(_argument->x * 0.1) - 1;
        }
    }
    if (_argument->y !=0 && M_U == 0 && M_D == 0){
        if (_argument->y > 0) {
            _argument->x -= (int) round(_argument->x * 0.1) + 1;
        }
        else {
            _argument->x -= (int) round(_argument->x * 0.1) - 1;
        }
    }
    return 0;
}

int _PlayerHandler(AreaMap *MAP){
    if (_PlayerKeybordManage(&MAP->player) != NULL){
        printf("Error: Managing keybord of Player!");
    }
    return 0;
}



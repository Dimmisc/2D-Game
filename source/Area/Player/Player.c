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
    
    uint8_t M_U = 0, M_D = 0, M_L = 0, M_R = 0, running = 0;
    const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
    vector *_argument = &Player->arguments.VectorMotion;
    SDL_Rect *_position = &Player->arguments.pah;
    SDL_Event Event;

    SDL_Event event;
        // Сначала обрабатываем все события - это обновит внутреннее состояние клавиатуры
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = 0;
        }
        // Можно добавить обработку SDL_KEYDOWN/UP здесь для однократных действий
    }

    if (keyboardState[SDL_SCANCODE_W] == 1) {
        M_U = 1;
        // Код для движения вперед
        _argument->y -= 20;
    }
    if (keyboardState[SDL_SCANCODE_S] == 1) {
        M_D = 1;
        // Код для движения назад
        _argument->y += 20;
    }
    if (keyboardState[SDL_SCANCODE_A] == 1) {
        M_L = 1;
        // Код для движения влево
        _argument->x -= 20;
        
    }   
    if (keyboardState[SDL_SCANCODE_D] == 1) {
        M_R = 1;
        // Код для движения вправо
        _argument->x += 20;
    }
    // while (SDL_PollEvent(&Event)) {
    //     if (Event.type == SDL_KEYDOWN) {
    //       if (Event.key.keysym.sym == SDLK_UP) {
    //         printf("Up\n");
    //       } else if (Event.key.keysym.sym == SDLK_DOWN) {
    //         printf("Down\n");
    //       } else if (Event.key.keysym.sym == SDLK_LEFT) {
    //         printf("left\n");
    //       } else if (Event.key.keysym.sym == SDLK_RIGHT) {
    //         printf("Right\n");
    //       }
    //     }
    //   }
    // Player mowing

    _position->x += _argument->x;
    _position->y += _argument->y;
    printf("%d %d %d %d \n", _argument->x, _argument->y, _position->x, _position->y);
    // Player Braking

    if (_argument->y !=0 && (M_U == 0 || M_D == 0)){
        if (_argument->y > 0) {
            _argument->y -= (int) round(_argument->y * 0.45) + 1;
        }
        else {
            _argument->y -= (int) round(_argument->y * 0.45) - 1;
        }
    }
    if (_argument->x !=0 && (M_L == 0 || M_R == 0)){
        if (_argument->x > 0) {
            _argument->x -= (int) round(_argument->x * 0.45) + 1;
        }
        else {
            _argument->x -= (int) round(_argument->x * 0.45) - 1;
        }
    }
    return 0;
}




int _PlayerHandler(AreaMap *MAP){
    if (_PlayerKeybordManage(&MAP->player) != 0){
        printf("Error: Managing keybord of Player!");
    }
    return 0;
}
#define _Player_C_


#include "Player.h"
#include "../Area.h"

#include <SDL2/SDL_image.h>

typedef struct PlayerPattern{
    char ImgPath[40];
    uint16_t textureHeight;
    uint16_t textureWidth;
    Point centerOffset;
} PlayerPattern;

PlayerPattern PLAYERTYPES[2] = {{"/PlayersTextures/StartPlayer.png", 128, 256, {0, 0}}, {}};
int PT = 2;
PlayerType *PlayerTypes = NULL;

int InitPlayers(SDL_Renderer *RENDER, SDL_Surface *SURFACE) {
    size_t some = sizeof(int);
    PlayerTypes = malloc((sizeof(PlayerType) * PT));
    for (int i = 0;i<PT;i++){
        SURFACE = IMG_Load(PLAYERTYPES[i].ImgPath);
        PlayerTypes[i].playerTexture = SDL_CreateTextureFromSurface(RENDER, SURFACE);
        PlayerTypes[i].height = PLAYERTYPES[i].textureHeight, PlayerTypes[i].width = PLAYERTYPES[i].textureWidth, PlayerTypes[i].PointOffset = PLAYERTYPES[i].centerOffset;
        PlayerTypes[i].type = i;
        SDL_FreeSurface(SURFACE);
    }
    // Types[0].type = 0;
    // Types[0].playerTexture = _loadTexture();
    return 0;
}


int _loadPlayer(unsigned int Type, Player PLAYER) {

}
int loadSpriteFromFile(Sprite *sprite, const char *filename) {
    printf("Started to load sprite\n");
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Ошибка открытия файла для чтения");
        return 1;
    }

    
    memset(sprite, 0, sizeof(Sprite));
    sprite->typeSet = NULL; 
    
    char line[256];
    char key[64];
    char value[128];

    while (fgets(line, sizeof(line), file) != NULL) {
        if (line[0] == '\n' || line[0] == '#') continue;

        // Разбираем строку на ключ и значение (если они есть)
        if (sscanf(line, "%63[^:]: %127[^\n]", key, value) == 2) {
            printf("%s|%s\n", key, value);
            // Обработка ключей
            if (strcmp(key, "Name") == 0) {
                strncpy(sprite->name, value, sizeof(sprite->name) - 1);
                sprite->name[sizeof(sprite->name) - 1] = '\0'; // Гарантируем завершение строки
            } else if (strcmp(key, "ID") == 0) {
                sprite->id = strtoul(value, NULL, 10);
            } else if (strcmp(key, "  Reflection") == 0) {
                sprite->arguments.reflaction = (SDL_RendererFlip)atoi(value);
            } else if (strcmp(key, "  Rect") == 0) {
                sscanf(value, "%d %d %d %d", &sprite->arguments.pah.x, &sprite->arguments.pah.y,
                       &sprite->arguments.pah.w, &sprite->arguments.pah.h);
            } else if (strcmp(key, "  Rotation") == 0) {
                sprite->arguments.rotation = strtod(value, NULL);
            } else if (strcmp(key, "  Layout") == 0) {
                sprite->arguments.layot = (uint8_t)strtoul(value, NULL, 10);
            } else if (strcmp(key, "Type") == 0) {
            }
            
        } else {
            printf("Error\n");
            printf("%s|%s\n", key, value);
        }
    }

    printf("\n\n\n");
    fclose(file);
    printf("Sprite loaded from %s\n", filename);
    return 0; 
}

void QPlayers() {
    for (int i = 0;i<PT;i++){
        SDL_DestroyTexture(PlayerTypes[i].playerTexture);
        free(&PlayerTypes[i]);
    }
}
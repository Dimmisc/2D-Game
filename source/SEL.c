#define _SEL_C_

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h> 
#include <profileapi.h> 
#include <intrin.h>  
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>


#include "SEL.h"

#define STARTPLAYER 0U
volatile int g_stop_signal_received = 0;


SEL_Window *SEL_init(WindowSettings *settings) {
    SEL_Window *ARG = (SEL_Window*)calloc(1, sizeof(SEL_Window));
    printf("Start initialization Window: %s\n", settings->name);
    int succes = 0;
    ARG->window = SDL_CreateWindow(settings->name,
                                   settings->x,
                                   settings->y,
                                   settings->width,
                                   settings->height,
                                   SDL_WINDOW_SHOWN
                                   );
    if (ARG->window == NULL) {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return NULL;
    } else {
        printf("Window is created: %s\n", settings->name);
        ARG->render = SDL_CreateRenderer(ARG->window, -1, SDL_RENDERER_ACCELERATED);
        if (ARG->render == NULL) {
            printf( "Render could not be created! SDL_Error: %s\n", SDL_GetError() );
            return NULL;
        } else {
            printf("Render is created. Window: %s\n", settings->name);
        }
    }
    ARG->Map = _InitMap("TestMap", ARG->render, ARG->surface);
    printf("%s\n", ARG->Map->name);
    return ARG;
}

int Moving_of_Sprites(AreaMap *AREA, int speed) {
    int succes = 1, truth = 0;
    // for (int i=0;i<AREA->sizeflexingsprites;i++) {
    //     //truth = InitEventSprite(AREA->flexingsprites[i]); //It will be avalible

    //     if (truth == 0) {
    //         succes = 0;
    //         //strncpy(AREA->error, GetSpriteError(), 30); // It will be avalible
    //         break;
    //     }
    // }
    return succes;
}


int UpdateScreen(SEL_Window *ARG) {
    static int screenupdate = 0;
    int succes = 1;
    if (screenupdate > 0){
        SDL_RenderClear(ARG->render);
    }
    uint8_t _PlayerLayot = ARG->Map->player.layot;
    uint8_t _Len_layot = ARG->Map->cellsArg.layots;
    Player * _PlayerP = &ARG->Map->player;

    printf("%d screen update\n", screenupdate++);
    int _Px = _PlayerP->arguments.pah.x, _Py = _PlayerP->arguments.pah.y;
    int Hw = ARG->WindowSettings.width / 2, Hh = ARG->WindowSettings.height / 2;
    for (int layot = 0; layot < _Len_layot; layot++) {
        if (_PlayerLayot == layot) {
            SDL_Rect Prect = {Hh, Hw, 0, 0};
            SDL_Point PCenterR = {Hh + (_PlayerP->TypeSet->height / 2), Hw + (_PlayerP->TypeSet->width / 2)};
            SDL_RenderCopyEx(ARG->render,
                             _PlayerP->TypeSet->playerTexture, 
                             NULL, 
                             &Prect, 
                             _PlayerP->arguments.rotation, 
                             &PCenterR,
                             _PlayerP->arguments.reflaction);
        }

        int CBNW = (int)ceil(((float)_Px + Hw) / ARG->Map->cellsArg.width), 
        CBNH = (int)ceil(((float)_Py + Hh) /ARG->Map->cellsArg.height);


        for (int sW = (_Px - Hw) / ARG->Map->cellsArg.width; sW < CBNW; sW++){
            for (int sH = (_Py - Hh) / ARG->Map->cellsArg.height; sH < CBNH; sH++) {
                for (int sprite = 0; sprite < ARG->Map->cells[sW][sH].layots[layot].LenSprites;sprite++) {

                    Sprite *P_TO_S = &ARG->Map->cells[sW][sH].layots[layot].sprites[sprite];
                    SDL_Rect Srect = {P_TO_S->arguments.pah.x - _PlayerP->arguments.pah.x + Hw,
                                      P_TO_S->arguments.pah.y - _PlayerP->arguments.pah.y + Hh, 0, 0};
                    SDL_Point SCenterR = {P_TO_S->arguments.pah.x - _PlayerP->arguments.pah.x + Hw, 
                                          P_TO_S->arguments.pah.y - _PlayerP->arguments.pah.y + Hh};

                    
                    if (Srect.x < ARG->WindowSettings.width & Srect.x > 0 & Srect.y < ARG->WindowSettings.height & Srect.y > 0){
                        int true = SDL_RenderCopyEx(ARG->render,
                                        P_TO_S->typeSet->STexture,
                                        NULL,
                                        &Srect,
                                        P_TO_S->arguments.rotation,
                                        &SCenterR,
                                        P_TO_S->arguments.reflaction
                                        );
                        if (!true) {
                            printf("Error of showing sprite: %s, %d, %d, %d, %d;\n SDL Error: %s",
                                   P_TO_S->name, Srect.x, Srect.y, SCenterR.x, SCenterR.y, SDL_GetError());
                                   g_stop_signal_received = 1;
                        }
                    }
                }
            }
        }
    }
    SDL_RenderPresent(ARG->render);
    return succes;
}
static LARGE_INTEGER g_qpc_frequency = {0};

int initialize_timing() {
    if (g_qpc_frequency.QuadPart == 0) {
        if (!QueryPerformanceFrequency(&g_qpc_frequency)) {
            fprintf(stderr, "Error: QueryPerformanceFrequency not handling.\n");
            return 0;
        }
        if (g_qpc_frequency.QuadPart == 0) {
             fprintf(stderr, "Error: QueryPerformanceFrequency gived 0.\n");
            return 0;
        }
    }
    return 1;
}

uint64_t get_monotonic_time_ns() {
    if (g_qpc_frequency.QuadPart == 0) {
        if (!initialize_timing()) return 0;
    }
    LARGE_INTEGER counter;
    QueryPerformanceCounter(&counter);
    uint64_t whole_seconds = counter.QuadPart / g_qpc_frequency.QuadPart;
    uint64_t remainder_ticks = counter.QuadPart % g_qpc_frequency.QuadPart;
    uint64_t fractional_ns = (remainder_ticks * 1000000000ULL) / g_qpc_frequency.QuadPart;
    return (whole_seconds * 1000000000ULL) + fractional_ns;
}


void precise_sleep_ns(uint64_t nanoseconds) {
    if (nanoseconds == 0) return;
    uint64_t start_time = get_monotonic_time_ns();
    if (start_time == 0) return;
    uint64_t target_end_time = start_time + nanoseconds;
    const uint64_t min_sleep_threshold_ns = 2000000ULL; // 2 мс
    const uint64_t spin_wait_allowance_ns = 1500000ULL; // 1.5 мс

    if (nanoseconds > min_sleep_threshold_ns) {
        uint64_t sleep_duration_ns = nanoseconds - spin_wait_allowance_ns;
        DWORD sleep_ms = (DWORD)(sleep_duration_ns / 1000000ULL);
        if (sleep_ms > 0) {
            Sleep(sleep_ms);
        }
    }
    while (get_monotonic_time_ns() < target_end_time) {
        YieldProcessor();
    }
}

int SEL_Start(int target_fps, SEL_Window *Window) {
    if (target_fps <= 0) {
        fprintf(stderr, "Ошибка: target_fps должен быть больше 0.\n");
        return 0;
    }
    if (!initialize_timing()) {
        return 0;
    }
    const uint64_t target_frame_ns = 1000000000ULL / (uint64_t)target_fps;
    uint64_t frame_count = 0;
    uint64_t current_time_ns = get_monotonic_time_ns();
    if (current_time_ns == 0 && g_qpc_frequency.QuadPart != 0) { 
        fprintf(stderr, "Ошибка: Не удалось получить начальное время.\n");
        return FALSE;
    }
    uint64_t next_frame_target_time_ns = current_time_ns + target_frame_ns;
    printf("Started with FPS=%d, Frame value: %llu ns\n", target_fps, (unsigned long long)target_frame_ns);
    while (g_stop_signal_received == 0) {


        // Place to state functions

        UpdateScreen(Window);
        printf("Incredible\n");
        frame_count++;
        current_time_ns = get_monotonic_time_ns();
        if (current_time_ns < next_frame_target_time_ns) {
            uint64_t sleep_time_ns = next_frame_target_time_ns - current_time_ns;
            precise_sleep_ns(sleep_time_ns);
        }
        next_frame_target_time_ns += target_frame_ns;
        current_time_ns = get_monotonic_time_ns();
        if (next_frame_target_time_ns < current_time_ns) {
            next_frame_target_time_ns = current_time_ns + target_frame_ns;
        }
    }

    printf("Ended\n");
    return TRUE;
}





/*This Function is necessary t brake your window */
int SEL_WQuit(SEL_Window *ARG) {
    SDL_DestroyRenderer( ARG->render );
    SDL_FreeSurface( ARG->surface );
    SDL_DestroyWindow( ARG->window );
    SDL_Quit();
    return 1;
}

int SEL_AQuit(AreaMap *Area){
    CloseArea(Area);
    return 1;
}

int SEL_Exit() {
    SDL_Quit();
    IMG_Quit();
    return 1;
}

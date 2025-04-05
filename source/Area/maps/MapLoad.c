#include <string.h>

#include "MapLoad.h"

#include "../sprites/sprite.h"
#include "../Player/Player.h"
#include "../Area.h"


int saveParametresSprite(FILE *fp, const ParametresSprite *params) {
    int write_err = 0;
    write_err |= (fprintf(fp, "%d ", (int)params->reflaction) < 0); // Cast enum to int
    write_err |= (fprintf(fp, "%d %d %d %d ", params->pah.x, params->pah.y, params->pah.w, params->pah.h) < 0);
    write_err |= (fprintf(fp, "%lf ", params->rotation) < 0);
    // Save uint8_t as unsigned int to be safe with format specifiers
    write_err |= (fprintf(fp, "%u\n", (unsigned int)params->layot) < 0);
    return write_err ? -1 : 0;
}

int loadParametresSprite(FILE *fp, ParametresSprite *params) {
    int reflaction_int;
    unsigned int layot_uint;
    int expected_reads = 7;
    int actual_reads = fscanf(fp, "%d %d %d %d %d %lf %u",
                              &reflaction_int,
                              &params->pah.x, &params->pah.y, &params->pah.w, &params->pah.h,
                              &params->rotation,
                              &layot_uint); // Read uint8_t into unsigned int

    if (actual_reads != expected_reads) return -1;

    params->reflaction = (SDL_RendererFlip)reflaction_int; // Cast back to enum
    params->layot = (uint8_t)layot_uint; // Cast back to uint8_t
    fgetc(fp); // Consume trailing newline
    return 0;
}

int savePlayer(FILE *fp, const Player *player) {
    int write_err = 0;
    // Save name - use %14s safety? Not needed for fprintf, but good practice for fscanf later
    write_err |= (fprintf(fp, "%s\n", player->name) < 0);

    // Save Inventory (Dummy implementation)
    // Replace with actual inventory saving logic
    write_err |= (fprintf(fp, "InventoryDataPlaceholder_%s\n", player->inventory) < 0);

    // Save arguments
    if (!write_err) write_err |= saveParametresSprite(fp, &player->arguments);
    // saveParametresSprite adds its own newline

    // Save PlayerType* (Saving pointer address is useless)
    // Save a placeholder (e.g., 0 for NULL, or an ID if you have one)
    // A real system needs a way to reconstruct/link this pointer on load.
    write_err |= (fprintf(fp, "%p\n", (void*)player->TypeSet) < 0); // Saving address only for demo, WILL NOT WORK on load properly

    // Save player layot
    write_err |= (fprintf(fp, "%u\n", (unsigned int)player->layot) < 0);

    return write_err ? -1 : 0;
}

int loadPlayer(FILE *fp, Player *player) {
    // Load name
    if (fscanf(fp, "%14s", player->name) != 1) return -1;
    fgetc(fp); // Consume newline

    // Load Inventory (Dummy implementation)
    char inv_buffer[100]; // Buffer to read the placeholder line
    if (fgets(inv_buffer, sizeof(inv_buffer), fp) == NULL) return -1; // Read and discard line
    // In a real implementation, parse inv_buffer to load inventory data

    // Load arguments
    if (loadParametresSprite(fp, &player->arguments) != 0) return -1;
    // loadParametresSprite consumes its newline

    // Load PlayerType* (Placeholder - set to NULL)
    void* temp_ptr_val; // Read the saved pointer address (which is useless)
    if (fscanf(fp, "%p", &temp_ptr_val) != 1) return -1;
    player->TypeSet = NULL; // <<<< IMPORTANT: Must set to NULL or reconstruct properly
    fgetc(fp); // Consume newline

    // Load player layot
    unsigned int layot_uint;
    if (fscanf(fp, "%u", &layot_uint) != 1) return -1;
    player->layot = (uint8_t)layot_uint;
    fgetc(fp); // Consume newline

    return 0;
}


int saveSprite(FILE *fp, const Sprite *sprite) {
    int write_err = 0;
    // Save name
    write_err |= (fprintf(fp, "%s\n", sprite->name) < 0);

    // Save arguments
    if (!write_err) write_err |= saveParametresSprite(fp, &sprite->arguments);
    // saveParametresSprite adds its own newline

    // Save type* (Placeholder - see PlayerType*)
    write_err |= (fprintf(fp, "%d\n", sprite->typeSet->id) < 0); // Saving address - WILL NOT WORK

    // Save ID
    write_err |= (fprintf(fp, "%u\n", sprite->id) < 0); // %u for uint32_t

    return write_err ? -1 : 0;
}

int loadSprite(FILE *fp, Sprite *sprite) {
    // Load name
    if (fscanf(fp, "%14s", sprite->name) != 1) return -1;
    fgetc(fp); // Consume newline

    // Load arguments
    if (loadParametresSprite(fp, &sprite->arguments) != 0) return -1;
    // loadParametresSprite consumes its newline

    // Load type* (Placeholder - set to NULL)
    int type;
    if (fscanf(fp, "%d", &type) != 1) return -1;
    sprite->typeSet = NULL; // <<<< IMPORTANT: Must set to NULL or reconstruct properly
    fgetc(fp); // Consume newline

    // Load ID
    if (fscanf(fp, "%u", &sprite->id) != 1) return -1; // %u for uint32_t
    fgetc(fp); // Consume newline

    return 0;
}


int loadParametresSprite(FILE *fp, ParametresSprite *params) {
    int reflaction_int;
    unsigned int layot_uint;
    int expected_reads = 7;
    int actual_reads = fscanf(fp, "%d %d %d %d %d %lf %u",
                              &reflaction_int,
                              &params->pah.x, 
                              &params->pah.y, 
                              &params->pah.w, 
                              &params->pah.h,
                              &params->rotation,
                              &layot_uint); // Read uint8_t into unsigned int

    if (actual_reads != expected_reads) return -1;

    params->reflaction = (SDL_RendererFlip)reflaction_int; // Cast back to enum
    params->layot = (uint8_t)layot_uint; // Cast back to uint8_t
    fgetc(fp); // Consume trailing newline
    return 0;
}


AreaMap *_load_map(const char *filename) {
    if (!filename) {
        fprintf(stderr, "Error: NULL filename passed to loadAreaMap.\n");
        return NULL;
    }
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Error opening file for reading");
        return NULL;
    }
    AreaMap *map = (AreaMap *)calloc(1, sizeof(AreaMap));
    if (!map) {
        perror("Failed to allocate memory for AreaMap");
        fclose(fp);
        return NULL;
    }
    int read_err = 0;
    int expected_reads = 0;
    int actual_reads = 0;
    expected_reads = 1;
    actual_reads = fscanf(fp, "%29s", map->error);
    if (actual_reads != expected_reads) { read_err = 1; goto cleanup; }
    fgetc(fp);
    expected_reads = 5;
    actual_reads = fscanf(fp, "%d %d %d %d %d",
                          &map->cellsArg.height, 
                          &map->cellsArg.width,
                          &map->cellsArg.massHeight, 
                          &map->cellsArg.massWidth,
                          &map->cellsArg.layots);
    if (actual_reads != expected_reads) { read_err = 1; goto cleanup; }
    fgetc(fp);
    if (loadPlayer(fp, &map->player) != 0) { read_err = 1; goto cleanup; }
    expected_reads = 1;
    actual_reads = fscanf(fp, "%14s", map->name); // Use %14s for char[15]
    if (actual_reads != expected_reads) { read_err = 1; goto cleanup; }
    fgetc(fp);
    expected_reads = 2;
    actual_reads = fscanf(fp, "%d %d", 
                          &map->mapwidth, 
                          &map->mapheight);
    if (actual_reads != expected_reads || map->mapwidth <= 0 || map->mapheight <= 0) {
        fprintf(stderr, "Error: Invalid map dimensions loaded (%d x %d).\n", map->mapwidth, map->mapheight);
        read_err = 1;
        goto cleanup;
    }
    printf("hoho%c\n", fgetc(fp));
    map->cells = (Cell **)malloc(map->mapheight * sizeof(Cell *));
    if (!map->cells) { perror("Failed to allocate memory for cell rows"); read_err = 1; goto cleanup; }
    for(int i = 0; i < map->mapheight; ++i) map->cells[i] = NULL;

    for (int i = 0; i < map->mapheight; ++i) {
        map->cells[i] = (Cell *)calloc(map->mapwidth, sizeof(Cell));
        if (!map->cells[i]) { perror("Failed to allocate memory for cell row"); read_err = 1; goto cleanup; }

        for (int j = 0; j < map->mapwidth; ++j) {
            Cell *currentCell = &map->cells[i][j];
            expected_reads = 1;
            actual_reads = fscanf(fp, "%d", &currentCell->SizeLayots);
            if (actual_reads != expected_reads || currentCell->SizeLayots < 0) {
                 fprintf(stderr, "Error reading SizeLayots for cell [%d][%d].\n", i, j);
                 read_err = 1; goto cleanup;
            }
            fgetc(fp); 
            if (currentCell->SizeLayots > 0) {
                currentCell->layots = (Layot *)calloc(currentCell->SizeLayots, sizeof(Layot));
                if (!currentCell->layots) { perror("Failed to allocate memory for layots"); read_err = 1; goto cleanup; }

                for (int k = 0; k < currentCell->SizeLayots; ++k) {
                    Layot *currentLayot = &currentCell->layots[k];
                    expected_reads = 1;
                    actual_reads = fscanf(fp, "%d", &currentLayot->LenSprites);
                     if (actual_reads != expected_reads || currentLayot->LenSprites < 0) {
                        fprintf(stderr, "Error reading LenSprites for cell [%d][%d], layot %d.\n", i, j, k);
                        read_err = 1; goto cleanup;
                     }
                    fgetc(fp);
                    if (currentLayot->LenSprites > 0) {
                        currentLayot->sprites = (Sprite *)calloc(currentLayot->LenSprites, sizeof(Sprite)); // Use calloc
                        if (!currentLayot->sprites) { perror("Failed to allocate memory for sprites"); read_err = 1; goto cleanup; }

                        for (int l = 0; l < currentLayot->LenSprites; ++l) {
                            Sprite *currentSprite = &currentLayot->sprites[l];
                            if (loadSprite(fp, currentSprite) != 0) {
                                 fprintf(stderr, "Error loading sprite %d for cell [%d][%d], layot %d.\n", l, i, j, k);
                                 read_err = 1; goto cleanup;
                            }
                        }
                    } else {
                        currentLayot->sprites = NULL;
                    }
                }
            } else {
                 currentCell->layots = NULL;
            }
        }
    }

cleanup:
    fclose(fp);

    if (read_err) {
        fprintf(stderr, "Error: Failed to load data completely from %s.\n", filename);
        freeAreaMapData(map);
        return NULL;
    }

    printf("AreaMap successfully loaded from %s\n", filename);
    return map;
}


int _save_map(const AreaMap *map, const char *filename) {
    if (!map || !filename) {
        fprintf(stderr, "Error: NULL map or filename passed to saveAreaMap.\n");
        return -1;
    }
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("Error opening file for writing");
        return -1;
    }
    int write_err = 0;
    write_err |= (fprintf(fp, "%s\n", map->error) < 0);
    write_err |= (fprintf(fp, "%d %d %d %d %d\n",
                          map->cellsArg.height, map->cellsArg.width,
                          map->cellsArg.massHeight, map->cellsArg.massWidth,
                          map->cellsArg.layots) < 0);
    if (!write_err) write_err |= savePlayer(fp, &map->player);
    write_err |= (fprintf(fp, "%s\n", map->name) < 0);
    write_err |= (fprintf(fp, "%d %d\n", map->mapwidth, map->mapheight) < 0);
    for (int i = 0; i < map->mapheight && !write_err; ++i) {
        for (int j = 0; j < map->mapwidth && !write_err; ++j) {
            if (!map->cells || !map->cells[i]) {
                 fprintf(stderr, "Warning: Encountered NULL pointer in map->cells[%d] during save.\n", i);
                 write_err |= (fprintf(fp, "0\n") < 0);
                 continue; 
            }
            Cell *currentCell = &map->cells[i][j];
            write_err |= (fprintf(fp, "%d\n", currentCell->SizeLayots) < 0);
            for (int k = 0; k < currentCell->SizeLayots && !write_err; ++k) {
                 if (!currentCell->layots) {
                    fprintf(stderr, "Warning: Encountered NULL pointer for layots array in cell [%d][%d] during save, expected %d layots.\n", i, j, currentCell->SizeLayots);
                    write_err |= (fprintf(fp, "0\n") < 0);
                    continue;
                 }
                Layot *currentLayot = &currentCell->layots[k];
                write_err |= (fprintf(fp, "%d\n", currentLayot->LenSprites) < 0);
                for (int l = 0; l < currentLayot->LenSprites && !write_err; ++l) {
                    if (!currentLayot->sprites) {
                        fprintf(stderr, "Warning: Encountered NULL pointer for sprites array in cell [%d][%d], layot %d during save, expected %d sprites.\n", i, j, k, currentLayot->LenSprites);
                         break;
                    }
                    Sprite *currentSprite = &currentLayot->sprites[l];
                    write_err |= saveSprite(fp, currentSprite);
                }
            }
        }
    }

    fclose(fp);

    if (write_err) {
        fprintf(stderr, "Error: Failed to write data completely to %s.\n", filename);
        return -1;
    }

    printf("AreaMap successfully saved to %s\n", filename);
    return 0;
}


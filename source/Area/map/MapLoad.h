#ifndef _MapLoad_H_
#define _MapLoad_H_
#include "../Area.h"

int _save_map(const AreaMap *map, const char *filename);
AreaMap *_load_map(const char *filename);

#endif //_MapLoad_H_
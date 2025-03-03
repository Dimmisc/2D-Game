#include <stdlib.h>

#include "sprite.h"


ConstTypes TYPESET;


int Init_Sprites() {
    
    TYPESET.LT = 1;
    return 1;
}

Type *Give_Type(unsigned int type) {
    for (int i=0;i<TYPESET.LT; i++) {
        if (TYPESET.types[i].type == type) {
            return &TYPESET.types[i];
        }
    }
    return 0;
}
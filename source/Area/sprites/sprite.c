#include <stdlib.h>

#include "sprite.h"


const Type TYPESET[4];
int TYPES_COUNT = 4;


Type *Give_Type(unsigned int type) {
    for (int i=0;i<TYPES_COUNT; i++) {
        if (TYPESET[i].type == type) {
            return &TYPESET[i];
        }
    }
    Type nnn;
    return &nnn;
}
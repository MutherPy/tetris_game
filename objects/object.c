#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "../types.h"
#include "objects.h"
#include "object_calculator/object_calculator.h"


Object* create_object(Type t){
    Object* new = (Object*) malloc(sizeof(Object));
    new->type = t;
    new-> x_l_u=0;
    new-> y_l_u=0;
    new-> x_r_d=0;
    new-> y_r_d=0;

    switch (t) {
        case LINE:
            new->figure = (void *)LINE_FIGURE;
            break;
        case SS:
            new->figure = (void *)SS_FIGURE;
            break;
        case SQW:
            new->figure = (void *)SQW_FIGURE;
            break;
    }

    new->rotate = rotate_object;
    return NULL;
}

Type generate_type(){
    return (rand() % 3) + 1;
}

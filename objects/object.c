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

    new->rotate = rotate_object;
    new->build = build_object;
    new->move = move_object;
    return new;
}

Type generate_type(){
    return (rand() % 3) + 1;
}

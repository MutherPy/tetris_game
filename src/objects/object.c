#include <stdlib.h>

#include "../../include/object.h"
#include "../../include/controllers/builders.h"
#include "../../include/controllers/movers.h"
#include "../../include/controllers/rotators.h"

#include <stdio.h>

static void object_setter(Object* obj){
    switch (obj->type) {
        case LINE:
            obj->rotate = line_figure_rotator;
            obj->build = line_figure_builder;
            obj->move = line_figure_mover;
            obj->figure_size = LINE_SIZE;
            break;
        case SS:
            obj->rotate = ss_figure_rotator;
            obj->build = ss_figure_builder;
            obj->move = ss_figure_mover;
            obj->figure_size = SS_SIZE;
            break;
        case SQW:
            obj->rotate = sqw_figure_rotator;
            obj->build = sqw_figure_builder;
            obj->move = sqw_figure_mover;
            obj->figure_size = SQW_SIZE;
            break;
    }
}


Object* create_object(ObjectType t){
    Object* new = (Object*) malloc(sizeof(Object));
    new->type = t;
    object_setter(new);
    new->is_rotated = false;
    new->is_collision = false;
    new->build(new);
    return new;
}

ObjectType generate_type(){
    return rand() % 3 + 1;
}

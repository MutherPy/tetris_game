#include <stdlib.h>

#include "../../include/object.h"
#include "../../include/controllers/builders.h"
#include "../../include/controllers/movers.h"
#include "../../include/controllers/rotators.h"

#include <stdio.h>

static void object_method_setter(Object* obj){
    switch (obj->type) {
        case OBJECT_TYPE_LINE:
            obj->rotate = line_figure_rotator;
            obj->build = line_figure_builder;
            obj->figure_size = OBJECT_SIZE_LINE;
            break;
        case OBJECT_TYPE_SS:
            obj->rotate = ss_figure_rotator;
            obj->build = ss_figure_builder;
            obj->figure_size = OBJECT_SIZE_SS;
            break;
        case OBJECT_TYPE_SQW:
            obj->rotate = sqw_figure_rotator;
            obj->build = sqw_figure_builder;
            obj->figure_size = OBJECT_SIZE_SQW;
            break;
    }
    obj->move = figure_mover;
}

Object* create_object(ObjectType t){
    Object* new = (Object*) malloc(sizeof(Object));
    new->type = t;
    object_method_setter(new);

    new->is_rotated = false;
    new->is_collision = false;

    new->is_movable_left = true;
    new->is_movable_right = true;
    new->is_movable_down = true;

    new->build(new);
    return new;
}

ObjectType generate_type(){
    return rand() % 3 + 1;
}

#include <stdlib.h>

#include "../../include/object.h"
#include "../../include/controllers/builders.h"
#include "../../include/controllers/movers.h"
#include "../../include/controllers/rotators.h"
#include "../../include/controllers/stoppers.h"


Object* create_object(ObjectType t){
    Object* new = (Object*) malloc(sizeof(Object));
    new->type = t;

    switch (new->type) {
        case OBJECT_TYPE_LINE:
            new->figure_size = OBJECT_SIZE_LINE;
            break;
        case OBJECT_TYPE_SS:
            new->figure_size = OBJECT_SIZE_SS;
            break;
        case OBJECT_TYPE_SQW:
            new->figure_size = OBJECT_SIZE_SQW;
            break;
        case OBJECT_TYPE_iSS:
            new->figure_size = OBJECT_SIZE_iSS;
            break;
    }

    new->move = figure_mover;
    new->rotate = figure_rotator;
    new->build = figure_builder;
    new->collision_stop = object_stop_collision;

    new->is_rotated = false;
    new->is_collision = false;

    new->is_acted = true;

    new->build(new);
    return new;
}

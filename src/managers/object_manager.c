#include <stdio.h>
#include "../../include/object.h"

void object_manager(Actions action, Object* current_obj){
    switch (action) {
        case RIGHT:
        case LEFT:
        case DOWN:
            current_obj->move(current_obj, action);
            break;
        case ROTATE:
            current_obj->rotate(current_obj);
            break;
    }
}

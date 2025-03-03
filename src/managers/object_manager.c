#include <stdio.h>
#include "../../include/object.h"
#include "../../include/memory_utils.h"
#include <stdlib.h>


void object_action_manager(ObjectAction action, Object* current_obj){
    if (current_obj == NULL) return;
    if (current_obj->is_collision) return;
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


Object* new_object(){
    ObjectType t = generate_type();
    return create_object(t);
}

void next_object(Object** current_obj){
    free_object(*current_obj);
    *current_obj = NULL;
    ObjectType t = generate_type();
    *current_obj = create_object(t);
}

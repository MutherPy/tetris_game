#include <stdio.h>
#include "../../../include/object.h"
#include "../../../include/field_manager.h"


static void down_mover(Object* current_obj){
    if (edge_d_mover_check(current_obj)){
        current_obj->collision_stop(current_obj);
        return;
    }
    for (int i=0; i<current_obj->figure_size; i++){
        current_obj->figure[i][1] += 1;
    }
}

static void left_mover(Object* current_obj){
    if (edge_lr_movers_check(current_obj, OBJECT_ACTION_LEFT))
        return;
    for (int i=0; i<current_obj->figure_size; i++){
        current_obj->figure[i][0] -= 1;
    }
}

static void right_mover(Object* current_obj){
    if (edge_lr_movers_check(current_obj, OBJECT_ACTION_RIGHT))
        return;
    for (int i=0; i<current_obj->figure_size; i++){
        current_obj->figure[i][0] += 1;
    }
}


void figure_mover(Object* obj, ObjectAction action){
    switch (action) {
        case OBJECT_ACTION_DOWN:
            down_mover(obj);
            break;
        case OBJECT_ACTION_LEFT:
            left_mover(obj);
            break;
        case OBJECT_ACTION_RIGHT:
            right_mover(obj);
            break;
        default:
            break;
    }
}

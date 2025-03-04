
#include "../../../include/object.h"

void object_stop(Object* cur_obj){
    cur_obj->is_movable_right = false;
    cur_obj->is_movable_left = false;
    cur_obj->is_movable_down = false;
}

void object_stop_collision(Object* cur_obj){
    object_stop(cur_obj);
    cur_obj->is_collision = true;
}

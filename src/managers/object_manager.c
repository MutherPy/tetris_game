#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../../include/object.h"
#include "../../include/memory_utils.h"


void set_object_as_acted(Object* current_obj){
    current_obj->is_acted = true;
}

void set_object_as_unacted(Object* current_obj){
    current_obj->is_acted = false;
}

void object_action_manager(ObjectAction action, Object* current_obj){
    if (current_obj == NULL) return;
    pthread_mutex_lock(&lock);
    if (current_obj->is_collision) return;
    switch (action) {
        case OBJECT_ACTION_RIGHT:
        case OBJECT_ACTION_LEFT:
        case OBJECT_ACTION_DOWN:
            current_obj->move(current_obj, action);
            break;
        case OBJECT_ACTION_ROTATE:
            current_obj->rotate(current_obj);
            break;
    }
    set_object_as_acted(current_obj);
    pthread_mutex_unlock(&lock);
}

static ObjectType generate_type(){
    return rand() % 4 + 1;
}

Object* new_object(){
    ObjectType t = generate_type();
    return create_object(t);
}

void next_object(Object** current_obj){
    free_object(*current_obj);
    *current_obj = NULL;
    *current_obj = new_object();
}

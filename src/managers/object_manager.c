#include <stdio.h>
#include "../../include/object.h"
#include <pthread.h>

static pthread_mutex_t lock;

void object_action_manager(ObjectAction action, Object* current_obj){
//    pthread_mutex_lock(&lock);
    switch (action) {
        case RIGHT:
        case LEFT:
        case DOWN:
            current_obj->move(current_obj, action);
            break;
        case ROTATE:
            puts("ROTATOR");
            current_obj->rotate(current_obj);
            break;
    }
//    pthread_mutex_unlock(&lock);
}



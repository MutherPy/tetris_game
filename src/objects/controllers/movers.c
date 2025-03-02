#include <stdio.h>
#include "../../../include/object.h"

static void down_mover(us_type** figure, us_type size){
    for (int i=0; i<size; i++){
        figure[i][1] += 1;
    }
}

static void left_mover(us_type** figure, us_type size){
    for (int i=0; i<size; i++){
        figure[i][0] -= 1;
    }
}

static void right_mover(us_type** figure, us_type size){
    for (int i=0; i<size; i++){
        figure[i][0] += 1;
    }
}

void figure_mover(Object* obj, ObjectAction action){
    switch (action) {
        case DOWN:
            down_mover(obj->figure, obj->figure_size);
            break;
        case LEFT:
            left_mover(obj->figure, obj->figure_size);
            break;
        case RIGHT:
            right_mover(obj->figure, obj->figure_size);
            break;
        default:
            break;
    }
}

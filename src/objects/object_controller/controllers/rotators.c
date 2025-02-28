#include "../../../../include/object.h"

#include <stdio.h>


void line_figure_rotator(Object* obj){
    us_type f;
    us_type mid = obj->figure_size / 2;
    us_type** inner_f = obj->figure;
    if(obj->is_rotated){
        f = inner_f[mid][1];
        for(int i = 0; i < obj->figure_size; i++){
            inner_f[i][0] = inner_f[i][0] - mid + i;
            inner_f[i][1] = f;
        }
    } else {
        f = inner_f[mid][0];
        for (int i = 0; i < obj->figure_size; i++) {
            inner_f[i][0] = f;
            inner_f[i][1] = inner_f[i][1] - mid + i;
        }
    }
    obj->is_rotated = !obj->is_rotated;
}

void ss_figure_rotator(Object* obj){
}

void sqw_figure_rotator(Object* obj){
    puts("SQW ROTATOR");
}

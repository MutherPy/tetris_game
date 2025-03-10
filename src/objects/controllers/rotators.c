#include "../../../include/object.h"
#include "../../../include/field_manager.h"


static void line_figure_rotator(Object* obj){
    us_type mid = obj->figure_size / 2;
    us_type** inner_f = obj->figure;
    us_type* f = inner_f[mid];
    if(obj->is_rotated){
        for(int i = 0; i < obj->figure_size; i++){
            inner_f[i][0] = inner_f[i][0] - mid + i;
            inner_f[i][1] = f[1];
        }
    } else {
        for (int i = 0; i < obj->figure_size; i++) {
            inner_f[i][0] = f[0];
            inner_f[i][1] = inner_f[i][1] - mid + i;
        }
    }
    obj->is_rotated = !obj->is_rotated;
}

static void ss_figure_rotator(Object* obj){
    us_type** inner_f = obj->figure;
    us_type* f = inner_f[2];
    if (obj->is_rotated){
        for(int i = 0; i < obj->figure_size; i++){
            if (i < 3) {
                inner_f[i][0] = f[0] - 2 + i;
                inner_f[i][1] = f[1];
            } else {
                inner_f[i][0] = f[0] - 3 + i;
                inner_f[i][1] = f[1] - 1;
            }
        }
    } else {
        for(int i = 0; i < obj->figure_size; i++){
            if (i < 3) {
                inner_f[i][0] = f[0];
                inner_f[i][1] = f[1] - 2 + i;
            } else {
                inner_f[i][0] = f[0] + 1;
                inner_f[i][1] = f[1] - 3 + i;
            }
        }
    }
    obj->is_rotated = !obj->is_rotated;
}

static void sqw_figure_rotator(Object* obj){
    obj->is_rotated = !obj->is_rotated;
}

static void iss_figure_rotator(Object* obj){
    us_type** inner_f = obj->figure;
    us_type* f = inner_f[2];
    if (obj->is_rotated){
        for(int i = 0; i < obj->figure_size; i++){
            if (i < 3) {
                inner_f[i][0] = f[0] - 2 + i;
                inner_f[i][1] = f[1];
            } else {
                inner_f[i][0] = f[0] - 3 + i;
                inner_f[i][1] = f[1] + 1;
            }
        }
    } else {
        for(int i = 0; i < obj->figure_size; i++){
            if (i < 3) {
                inner_f[i][0] = f[0] + 1;
                inner_f[i][1] = f[1] - 2 + i;
            } else {
                inner_f[i][0] = f[0] - 1;
                inner_f[i][1] = f[1] - 3 + i;
            }
        }
    }
    obj->is_rotated = !obj->is_rotated;
}


void figure_rotator(Object* obj){
    switch (obj->type) {
        case OBJECT_TYPE_LINE:
            edge_rotator_check(obj, line_figure_rotator);
            break;
        case OBJECT_TYPE_SS:
            edge_rotator_check(obj, ss_figure_rotator);
            break;
        case OBJECT_TYPE_SQW:
            edge_rotator_check(obj, sqw_figure_rotator);
            break;
        case OBJECT_TYPE_iSS:
            edge_rotator_check(obj, iss_figure_rotator);
            break;
        default:
            break;
    }
}

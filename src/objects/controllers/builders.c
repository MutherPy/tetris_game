#include "../../../include/object.h"
#include "../../../include/memory_utils.h"


static void line_figure_builder(Object* obj){
    us_type left = FIELD_COLS / 2 - 2;
    us_type size = obj->figure_size;
    us_type** line = memory_allocator(size, COORD_UNIT_SIZE);
    for (int i = 0; i < size; i++){
        line[i][0] = left + i;
        line[i][1] = 0;
    }
    obj->figure = line;
}

static void ss_figure_builder(Object* obj){
    us_type left = FIELD_COLS / 2 - 3;
    us_type size = obj->figure_size;
    us_type** ss = memory_allocator(size, COORD_UNIT_SIZE);
    us_type h = 1;
    us_type w = 2;
    for (int i = 0; i < size; i++){
        ss[i][0] = left + i;
        ss[i][1] = h;
        if (i == w){
            h--;
            left--;
        }
    }
    obj->figure = ss;
}

static void sqw_figure_builder(Object* obj){
    us_type left = FIELD_COLS / 2 - 1;
    us_type size = obj->figure_size;
    us_type** ss = memory_allocator(size, COORD_UNIT_SIZE);
    us_type h = 0;
    us_type w = 1;
    for (int i = 0; i < size; i++){
        ss[i][0] = left + i;
        ss[i][1] = h;
        if (i == w){
            h++;
            left-=2;
        }
    }
    obj->figure = ss;
}

static void iss_figure_builder(Object* obj){
    us_type left = FIELD_COLS / 2 - 3;
    us_type size = obj->figure_size;
    us_type** ss = memory_allocator(size, COORD_UNIT_SIZE);
    us_type h = 0;
    us_type w = 2;
    for (int i = 0; i < size; i++){
        ss[i][0] = left + i;
        ss[i][1] = h;
        if (i == w){
            h++;
            left--;
        }
    }
    obj->figure = ss;
}


void figure_builder(Object* obj){
    switch (obj->type) {
        case OBJECT_TYPE_LINE:
            line_figure_builder(obj);
            break;
        case OBJECT_TYPE_SS:
            ss_figure_builder(obj);
            break;
        case OBJECT_TYPE_SQW:
            sqw_figure_builder(obj);
            break;
        case OBJECT_TYPE_iSS:
            iss_figure_builder(obj);
            break;
        default:
            break;
    }

}

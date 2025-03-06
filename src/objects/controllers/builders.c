#include "../../../include/object.h"
#include "../../../include/memory_utils.h"


void line_figure_builder(Object* obj){
    us_type left = FIELD_COLS / 2 - 2;
    us_type size = obj->figure_size;
    us_type** line = memory_allocator(size, COORD_UNIT_SIZE);
    for (int i = 0; i < size; i++){
        line[i][0] = left + i;
        line[i][1] = 0;
    }
    obj->figure = line;
}

void ss_figure_builder(Object* obj){
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

void sqw_figure_builder(Object* obj){
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

void iss_figure_builder(Object* obj){
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

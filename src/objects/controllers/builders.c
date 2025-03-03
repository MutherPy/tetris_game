#include "../../../include/object.h"
#include "../../../include/memory_utils.h"


void line_figure_builder(Object* obj){
    us_type left = FIELD_COLS / 2 - 2;
    us_type** line = memory_allocator(LINE_SIZE, COORD_UNIT_SIZE);
    for (int i = 0; i < LINE_SIZE; i++){
        line[i][0] = left + i;
        line[i][1] = 0;
    }
    obj->figure = line;
}

void ss_figure_builder(Object* obj){
    us_type left = FIELD_COLS / 2 - 3;
    us_type** ss = memory_allocator(SS_SIZE, COORD_UNIT_SIZE);
    us_type h = 1;
    us_type w = 2;
    for (int i = 0; i < SS_SIZE; i++){
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
    us_type** ss = memory_allocator(SQW_SIZE, COORD_UNIT_SIZE);
    us_type h = 0;
    us_type w = 1;
    for (int i = 0; i < SQW_SIZE; i++){
        ss[i][0] = left + i;
        ss[i][1] = h;
        if (i == w){
            h++;
            left-=2;
        }
    }
    obj->figure = ss;
}

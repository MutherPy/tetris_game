#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../../include/object.h"
#include "../../include/utils.h"

#define FIELD_FILLER '+'
#define FIGURE_BLOCK '#'

#define FILLED_FIELD_INIT_SIZE 50

// filled_coords = [[x,y], [x,y], ...]
// x - FIELD_COLS
// y - FIELD_ROWS

static us_type** restrict filled_field;
static us_type FILLED_FIELD_LAST_INDEX = 0;


void filled_field_init(){
    filled_field = memory_allocator(FILLED_FIELD_INIT_SIZE, COORD_UNIT_SIZE);
}

// TODO add realocation if overfill
static void save_filled_field(Object* current_object){
    for(int i=0; i<current_object->figure_size; i++){
        for(int j=0; j<COORD_UNIT_SIZE; j++){
            filled_field[i+FILLED_FIELD_LAST_INDEX][j] = current_object->figure[i][j];
        }
    }
    FILLED_FIELD_LAST_INDEX += current_object->figure_size;
}

static bool collision_check(Object* current_obj){
    current_obj->is_collision = false;
    return false;
}

static void edge_control(Object* current_obj){
    us_type** fig = current_obj->figure;
    bool is_movable_left = true, is_movable_right = true, is_movable_down = true;
    for(int i = 0; i < current_obj->figure_size; i++){
        us_type x = fig[i][0];
        us_type y = fig[i][1];

        if (is_movable_left) is_movable_left = (x > 0);
        if (is_movable_right) is_movable_right = (x < FIELD_COLS-1);
        if (is_movable_down) is_movable_down = (y < FIELD_ROWS-1);
    }
    current_obj->is_movable_left = is_movable_left;
    current_obj->is_movable_right = is_movable_right;
    current_obj->is_movable_down = is_movable_down;
}

static us_type** mesh(Object* current_obj, us_type mesh_sum){
    us_type** mesh = memory_allocator(mesh_sum, COORD_UNIT_SIZE);
    int offset = 0;
    memcpy(mesh, filled_field, FILLED_FIELD_INIT_SIZE * sizeof(us_type*));
    offset += FILLED_FIELD_INIT_SIZE;
    memcpy(mesh + offset, current_obj->figure, current_obj->figure_size * sizeof(us_type*));
    return mesh;
}

static void draw_field(us_type** m, us_type sum){
    char row[FIELD_COLS+1] = {[0 ... FIELD_COLS-1] = FIELD_FILLER, '\0'};
    for(int i = 0; i < FIELD_ROWS; i++){
        for(int j = 0; j < FIELD_COLS; j++){
            for(int k=0; k < sum; k++){
                if(m[k][0] == j && m[k][1] == i){
                    row[j]=FIGURE_BLOCK;
                }
            }
        }
        puts(row);
        memset(row, FIELD_FILLER, FIELD_COLS);
    }
}

void manage_field(Object* current_obj){
    edge_control(current_obj);
    bool collision = collision_check(current_obj);
    if (collision)
        save_filled_field(current_obj);
    us_type sum = current_obj->figure_size + FILLED_FIELD_INIT_SIZE;
    us_type** m = mesh(current_obj, sum);
    draw_field(m, sum);
    free(m);
}

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../../include/object.h"
#include "../../include/memory_utils.h"
#include "../../include/gui.h"

// filled_coords = [[x,y], [x,y], ...]
// x - FIELD_COLS
// y - FIELD_ROWS


static us_type** restrict filled_field;

static const us_type FILLED_FIELD_STORE_RESIZE = 50;
static us_type FILLED_FIELD_STORE_SIZE = 50;
static us_type FILLED_FIELD_STORE_LAST_INDEX = 0;


void filled_field_init(){
    filled_field = memory_allocator(FILLED_FIELD_STORE_SIZE, COORD_UNIT_SIZE);
}

static void edge_filled_control(
    us_type current_x,
    us_type current_y,
    bool* is_movable_left_ptr,
    bool* is_movable_right_ptr,
    Object* current_obj
) {
    if (!FILLED_FIELD_STORE_LAST_INDEX) return;
    us_type filled_x, filled_y;
    for (int i = 0; i < FILLED_FIELD_STORE_LAST_INDEX; i++){
        filled_x = filled_field[i][0];
        filled_y = filled_field[i][1];
        if (current_x - 1 == filled_x && current_y == filled_y){
            current_obj->is_movable_left = false;
            *is_movable_left_ptr = false;
            return;
        }
        if (current_x + 1 == filled_x && current_y == filled_y){
            current_obj->is_movable_right = false;
            *is_movable_right_ptr = false;
            return;
        }
    }
}

static void edge_control(Object* current_obj){
    us_type** fig = current_obj->figure;
    bool is_movable_left = true, is_movable_right = true, is_movable_down = true;
    for(int i = 0; i < current_obj->figure_size; i++){
        us_type x = fig[i][0];
        us_type y = fig[i][1];

        edge_filled_control(
                x, y,
                &is_movable_left,
                &is_movable_right,
                current_obj
        );
        if (is_movable_left) is_movable_left = (x > 0);
        if (is_movable_right) is_movable_right = (x < FIELD_COLS-1);
        if (is_movable_down) is_movable_down = (y < FIELD_ROWS-1);
    }
    current_obj->is_movable_left = is_movable_left;
    current_obj->is_movable_right = is_movable_right;
    current_obj->is_movable_down = is_movable_down;
}

static void collision_check(Object* current_obj){
    us_type** fig = current_obj->figure;
    for(int i = 0; i < current_obj->figure_size; i++) {
        us_type y = fig[i][1];
        us_type x = fig[i][0];

        if (y >= FIELD_ROWS-1){
            current_obj->is_collision = true;
            return;
        }

        for(int j = 0; j < FILLED_FIELD_STORE_LAST_INDEX; j++){
            if (x == filled_field[j][0] && y + 1 == filled_field[j][1]){
                current_obj->is_collision = true;
                return;
            }
        }

    }
}

static void save_filled_field(Object* current_object){
    us_type new_filled_index = FILLED_FIELD_STORE_LAST_INDEX + current_object->figure_size;
    while (new_filled_index > FILLED_FIELD_STORE_SIZE) {
        filled_field = memory_reallocator(
                filled_field,
                FILLED_FIELD_STORE_SIZE,
                FILLED_FIELD_STORE_RESIZE,
                COORD_UNIT_SIZE
                );
        FILLED_FIELD_STORE_SIZE += FILLED_FIELD_STORE_RESIZE;
    }
    for(int i = 0; i < current_object->figure_size; i++){
        for(int j = 0; j < COORD_UNIT_SIZE; j++){
            filled_field[i + FILLED_FIELD_STORE_LAST_INDEX][j] = current_object->figure[i][j];
        }
    }
    FILLED_FIELD_STORE_LAST_INDEX = new_filled_index;
}

static us_type** mesh(Object* current_obj, us_type mesh_sum){
    us_type** mesh = memory_allocator(mesh_sum, COORD_UNIT_SIZE);
    int offset = 0;
    memcpy(mesh, filled_field, FILLED_FIELD_STORE_LAST_INDEX * sizeof(us_type*));
    offset += FILLED_FIELD_STORE_LAST_INDEX;
    memcpy(mesh + offset, current_obj->figure, current_obj->figure_size * sizeof(us_type*));
    return mesh;
}

us_type get_mesh_sum(Object* current_obj){
    return current_obj->figure_size + FILLED_FIELD_STORE_LAST_INDEX;
}

us_type** manage_field(Object* current_obj){
    if (current_obj == NULL) return NULL;
    edge_control(current_obj);
    collision_check(current_obj);
    if (current_obj->is_collision)
        save_filled_field(current_obj);
    us_type sum = get_mesh_sum(current_obj);
    return mesh(current_obj, sum);
}

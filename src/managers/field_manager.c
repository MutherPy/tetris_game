#include <string.h>

#include "../../include/object.h"
#include "../../include/memory_utils.h"
#include "../../include/gui.h"
#include "../../include/field_manager_types.h"

// filled_coords = [[x,y], [x,y], ...]
// x - FIELD_COLS
// y - FIELD_ROWS


static us_type** restrict filled_field;

static const us_type FILLED_FIELD_STORE_RESIZE = 50;
static us_type FILLED_FIELD_STORE_SIZE = 50;
static us_type FILLED_FIELD_STORE_LAST_INDEX = 0;


void filled_field_init(){
//    FILLED_FIELD_STORE_SIZE = 70;
    filled_field = memory_allocator(FILLED_FIELD_STORE_SIZE, COORD_UNIT_SIZE);

//    us_type y = 17;
//    int ind = 0;
//    for(int i = 0; i<3; i++){
//        for(us_type j = 0; j<FIELD_COLS-1; j++){
//            filled_field[ind][0]= j;
//            filled_field[ind][1]= y;
//            ind++;
//        }
//        y++;
//    }
//    FILLED_FIELD_STORE_LAST_INDEX = (FIELD_COLS-1) * 3;
}

void filled_field_cleanup(){
    memory_releaser(FILLED_FIELD_STORE_SIZE, filled_field);
    FILLED_FIELD_STORE_LAST_INDEX = 0;
    FILLED_FIELD_STORE_SIZE = 50;
    filled_field_init();
}

static void edge_collision_check(Object* current_obj){
    us_type** fig = current_obj->figure;
    us_type filled_x, filled_y;
    us_type current_x, current_y;

    bool is_movable_left = true, is_movable_right = true;

    static const us_type check_y_amount = FIELD_ROWS - 1;
    static const us_type check_x_amount = FIELD_COLS - 1;

    for(int i = 0; i < current_obj->figure_size; i++) {
        current_x = fig[i][0];
        current_y = fig[i][1];
        if (current_y >= check_y_amount){
            current_obj->collision_stop(current_obj);
            return;
        }
        if (current_x <= 0 && is_movable_left) is_movable_left = false;
        if (current_x >= check_x_amount && is_movable_right) is_movable_right = false;
    }

    for(int i = 0; i < current_obj->figure_size; i++) {
        current_x = fig[i][0];
        current_y = fig[i][1];
        for(int j = 0; j < FILLED_FIELD_STORE_LAST_INDEX; j++){
            filled_x = filled_field[j][0];
            filled_y = filled_field[j][1];
            if (current_x == filled_x && current_y + 1 == filled_y){
                current_obj->collision_stop(current_obj);
                return;
            }
            if (current_x - 1 == filled_x && current_y == filled_y){
                is_movable_left = false;
            }
            if (current_x + 1 == filled_x && current_y == filled_y){
                is_movable_right = false;
            }
        }
    }
    current_obj->is_movable_left = is_movable_left;
    current_obj->is_movable_right = is_movable_right;
}

static bool overfill_field(){
    for(int i = 0; i < FILLED_FIELD_STORE_LAST_INDEX; i++){
        if (filled_field[i][1] == 0) return true;
    }
    return false;
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

static List* filled_lines_to_remove(){
    us_type uniq_keys[FIELD_ROWS] = {0};
    us_type count[FIELD_ROWS] = {0};
    us_type uniq_keys_size = 0;
    us_type current_key;
    bool found;

    for(int i = 0; i < FILLED_FIELD_STORE_LAST_INDEX; i++){
        current_key = filled_field[i][1];
        found = false;
        for(int j = 0; j < uniq_keys_size; j++){
            if (uniq_keys[j] == current_key) {
                count[j]++;
                found = true;
            }
        }
        if (!found){
            uniq_keys[uniq_keys_size] = current_key;
            count[uniq_keys_size] = 1;
            uniq_keys_size++;
        }
    }

    List* list = (List*)malloc(sizeof(List));
    init_list(list);

    for(int j = 0; j < uniq_keys_size; j++){
        if (count[j] >= FIELD_COLS) {
            append(list, uniq_keys[j]);
        }
    }
    return list;
}

static bool handle_remove_lines(List* list){
    us_type* current_filled_pixel;

    us_type current_index = 0;
    bool was_deleted = false;

    while (current_index < list->size){
        us_type to_remove_y = get_val(list, current_index);
        for(int i = 0; i < FILLED_FIELD_STORE_LAST_INDEX; i++){
            current_filled_pixel = filled_field[i];
            if (to_remove_y == current_filled_pixel[1]){
                FILLED_FIELD_STORE_LAST_INDEX--;
                current_filled_pixel[0] = filled_field[FILLED_FIELD_STORE_LAST_INDEX][0];
                current_filled_pixel[1] = filled_field[FILLED_FIELD_STORE_LAST_INDEX][1];
                filled_field[FILLED_FIELD_STORE_LAST_INDEX][0] = 0;
                filled_field[FILLED_FIELD_STORE_LAST_INDEX][1] = 0;
                i--;
                if (!was_deleted) was_deleted = true;
            }
        }
        current_index++;
    }
    return was_deleted;
}

static void move_filled_field_after_remove_lines(List* to_remove_list){
    us_type curr_line_index;
    us_type curr_line;
    for (int i = 0; i < FILLED_FIELD_STORE_LAST_INDEX; i++) {
        curr_line_index = 0;
        while (curr_line_index < to_remove_list->size) {
            curr_line = get_val(to_remove_list, curr_line_index);
            if(filled_field[i][1] < curr_line) {
                filled_field[i][1]++;
            }
            curr_line_index++;
        }
    }
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
    pthread_mutex_lock(&lock);
    edge_collision_check(current_obj);
    if (overfill_field()) return NULL;
    if (current_obj->is_collision) {
        save_filled_field(current_obj);
        List* to_remove_list = filled_lines_to_remove();
        bool was_removed_lines = handle_remove_lines(to_remove_list);
        if (was_removed_lines) move_filled_field_after_remove_lines(to_remove_list);
        free_list(to_remove_list);
    }
    us_type sum = get_mesh_sum(current_obj);
    pthread_mutex_unlock(&lock);
    return mesh(current_obj, sum);
}

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../../include/object.h"

#define FIELD_ROWS 10
#define FIELD_COLS 30

#define FIELD_FILLER '+'
#define FIGURE_BLOCK '#'

#define FILLED_FIELD_INIT_SIZE 50
#define FILLED_FIELD_COORD_SIZE 2

// filled_coords = [[x,y], [x,y], ...]
// x - FIELD_COLS
// y - FIELD_ROWS

static us_type** restrict filled_field;
static us_type FILLED_FIELD_LAST_INDEX = 0;


static us_type** memory_allocator(us_type outer_size, us_type inner_size){
    us_type** cont = (us_type**) malloc(sizeof(us_type*) * outer_size);
    for (int i=0; i < outer_size; i++){
        us_type* inner = (us_type*)calloc(inner_size, sizeof(us_type));
        *(cont+i) = inner;
    }
    return cont;
}

void filled_field_init(){
    filled_field = memory_allocator(FILLED_FIELD_INIT_SIZE, FILLED_FIELD_COORD_SIZE);
}

// TODO add realocation if overfill
static void save_filled_field(Object* current_object){
    for(int i=0; i<current_object->figure_size; i++){
        for(int j=0; j<FILLED_FIELD_COORD_SIZE; j++){
            filled_field[i+FILLED_FIELD_LAST_INDEX][j] = current_object->figure[i][j];
        }
    }
    FILLED_FIELD_LAST_INDEX += current_object->figure_size;
}

static bool collision_check(Object* current_obj){
    current_obj->is_collision = false;
    return false;
}

static us_type** mesh(Object* current_obj, us_type mesh_sum){
    us_type** mesh = memory_allocator(mesh_sum, FILLED_FIELD_COORD_SIZE);
    for(int i = 0; i < current_obj->figure_size; i++){
        for(int j = 0; j < FILLED_FIELD_COORD_SIZE; j++){
            mesh[i][j] = current_obj->figure[i][j];
        }
    }
    for(int i = 0; i < FILLED_FIELD_INIT_SIZE; i++){
        for(int j = 0; j < FILLED_FIELD_COORD_SIZE; j++){
            mesh[i][j] = filled_field[i][j];
        }
    }
    return mesh;
}

// TODO optimisations
//  1) Do not check whole line for collision. check just


void manage_field(Object* current_obj){
    bool collision = collision_check(current_obj);
    if (collision)
        save_filled_field(current_obj);

    us_type sum = current_obj->figure_size + FILLED_FIELD_INIT_SIZE;
    us_type** restrict m = mesh(current_obj, sum);
    char row[FIELD_COLS+1] = {[0 ... FIELD_COLS-1] = FIELD_FILLER, '\0'};
    for(int i = 0; i < FIELD_ROWS; i++){
        for(int j = 0; j < FIELD_COLS; j++) {
            for(int k=0; k < sum; k++){
                if(m[k][0] == j && m[k][1] == i){
                    row[j]=FIGURE_BLOCK;
                }
            }
        }
        puts(row);
        memset(row, FIELD_FILLER, FIELD_COLS);
    }
    free(m);
}

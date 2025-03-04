
#include <stdlib.h>
#include "../../include/object.h"

static us_type* inner_memory_allocator(us_type inner_size){
    us_type* inner = (us_type*)malloc(inner_size * sizeof(us_type));
    inner[0] = 0;
    inner[1] = 0;
    return inner;
}

us_type** memory_allocator(us_type outer_size, us_type inner_size){
    us_type** cont = (us_type**)malloc(sizeof(us_type*) * outer_size);
    for (int i=0; i < outer_size; i++){
        cont[i] = inner_memory_allocator(inner_size);
    }
    return cont;
}

us_type** memory_reallocator(us_type** src, us_type old_outer_size, us_type ext_outer_size, us_type inner_size){
    us_type new_size = old_outer_size+ext_outer_size;
    us_type** cont = (us_type**) realloc(src, new_size * sizeof(us_type*));
    if (cont == NULL) return NULL;
    for (int i = old_outer_size; i < new_size; i++){
        cont[i] = inner_memory_allocator(inner_size);
    }
    return cont;
}

static void memory_releaser(us_type size, us_type** cont){
    if(size==0){
        free(cont[0]);
        return;
    }
    for(int i=0; i<size; i++){
        free(cont[i]);
    }
}

void free_object(Object* current_object){
    memory_releaser(current_object->figure_size, current_object->figure);
    free(current_object);
}

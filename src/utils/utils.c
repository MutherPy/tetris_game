
#include <stdlib.h>
#include "../../include/object.h"

us_type** memory_allocator(us_type outer_size, us_type inner_size){
    us_type** cont = (us_type**)malloc(sizeof(us_type*) * outer_size);
    for (int i=0; i < outer_size; i++){
        us_type* inner = (us_type*)malloc(inner_size * sizeof(us_type));
        cont[i] = inner;
        inner[0] = -1;
        inner[1] = -1;
    }
    return cont;
}

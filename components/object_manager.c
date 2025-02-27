#include <stdio.h>
#include "../components_headers/types.h"

void object_controller(Actions action, Object* current_obj){
    printf("action %i object %p\n", action, current_obj);
}

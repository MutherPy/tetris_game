#include <stdio.h>
#include "../types.h"
#include "../objects/objects.h"

void object_controller(Actions action, Object* current_obj){
    printf("action %i object %p\n", action, current_obj);
}

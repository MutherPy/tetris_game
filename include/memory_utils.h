
#ifndef OBJECT_SET
    #include "object.h"
#endif


#ifndef UTILS_SET
    #define UTILS_SET

    us_type** memory_allocator(us_type outer_size, us_type inner_size);

    us_type** memory_reallocator(us_type** src, us_type old_outer_size, us_type ext_outer_size, us_type inner_size);

    void free_object(Object* current_object);

#endif

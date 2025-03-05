
#ifndef OBJECT_SET
    #include "object.h"
#endif


#ifndef UTILS_SET
    #define UTILS_SET

    us_type** memory_allocator(us_type outer_size, us_type inner_size);

    us_type** memory_reallocator(us_type** src, us_type old_outer_size, us_type ext_outer_size, us_type inner_size);
    void filled_field_cleanup();
    void memory_releaser(us_type size, us_type** cont);
    void free_object(Object* current_object);

#endif

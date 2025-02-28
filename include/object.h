
#ifndef TYPES_SET
#include "types.h"
    #define TYPES_SET
#endif

#ifndef OBJECT_SET
    #define OBJECT_SET
    typedef unsigned short us_type;

    #define COORD_UNIT_SIZE 2

    typedef struct object {
        ObjectType type;

        bool is_rotated;
        bool is_collision;

        ObjectSize figure_size;
        us_type** figure;

        void (*rotate)(struct object*);
        void (*build)(struct object*);
        void (*move)(struct object*, ObjectAction);
    } Object;

    static void object_method_setter(Object* obj);
    Object* create_object(ObjectType t);
    ObjectType generate_type();

#endif

#ifndef TYPES_SET
    #include "types.h"
    #define TYPES_SET
#endif

#ifndef OBJECT_SET
    #define OBJECT_SET
    #define COORD_UNIT_SIZE 2

    typedef struct object {
        ObjectType type;

        bool is_rotated;
        bool is_collision;

        bool is_acted;

        ObjectSize figure_size;
        us_type** figure;

        void (*rotate)(struct object*);
        void (*build)(struct object*);
        void (*move)(struct object*, ObjectAction);

        void (*collision_stop)(struct object*);

    } Object;

    Object* create_object(ObjectType t);

#endif
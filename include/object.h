
#ifndef TYPES_SET
    #include "types.h"
    #define TYPES_SET
#endif

#ifndef OBJECT_SET
#define OBJECT_SET

    #define FIGURE_BLOCK '#'

    typedef struct object {
        Type type;

        char* figure;

        void (*rotate)(struct object*);
        void (*build)(struct object*);
        void (*move)(struct object*, Actions);
    } Object;

    static void object_methods_setter(Object* obj);
    Object* create_object(Type t);
    Type generate_type();

#endif
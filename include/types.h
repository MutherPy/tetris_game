#include <stdbool.h>
#include <pthread.h>

#ifndef TYPES_SET
    #define TYPES_SET

    #define FIELD_ROWS 20
    #define FIELD_COLS 20

    pthread_mutex_t lock;

    typedef short us_type;

    typedef enum act {
        OBJECT_ACTION_LEFT=1,
        OBJECT_ACTION_RIGHT=2,
        OBJECT_ACTION_ROTATE=3,
        OBJECT_ACTION_DOWN=4
    } ObjectAction;


    typedef enum tp {
        OBJECT_TYPE_LINE=1,
        OBJECT_TYPE_SS=2,
        OBJECT_TYPE_SQW=3
    } ObjectType;

    typedef enum sizes {
        OBJECT_SIZE_LINE=5,
        OBJECT_SIZE_SS=6,
        OBJECT_SIZE_SQW=4
    } ObjectSize;

#endif
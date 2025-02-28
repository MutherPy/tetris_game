#include <stdbool.h>

#ifndef TYPES_SET
    #define TYPES_SET

    #define FIELD_ROWS 10
    #define FIELD_COLS 30

    typedef enum act {
        LEFT=1,
        RIGHT=2,
        ROTATE=3,
        DOWN=4
    } ObjectAction;


    typedef enum tp {
        LINE=1,
        SS=2,
        SQW=3
    } ObjectType;

    typedef enum sizes {
        LINE_SIZE=5,
        SS_SIZE=6,
        SQW_SIZE=4
    } ObjectSize;

#endif
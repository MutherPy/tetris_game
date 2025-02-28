
#ifndef TYPES_SET
    #define TYPES_SET

    #include <stdbool.h>

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

#endif
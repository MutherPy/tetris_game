#include <stdlib.h>
#include <stdio.h>

#define FIELD_ROWS 10
#define FIELD_COLS 30

#define FIELD_FILLER '+'

void draw_field(){
    for(int i = 0; i < FIELD_ROWS; i++){
        for(int j = 0; j < FIELD_COLS; j++) {
            putchar(FIELD_FILLER);
        }
        putchar('\0');
        putchar('\n');
    }
}

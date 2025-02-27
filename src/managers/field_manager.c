#include <stdlib.h>
#include <stdio.h>

#define FIELD_ROWS 10
#define FIELD_COLS 31

#define FIELD_FILLER '+'

char** init_fill_field(){
    char** field = (char**)malloc(FIELD_ROWS * sizeof(char*));
    if(field == NULL){
        return NULL;
    }
    for(int i = 0; i < FIELD_ROWS; i++){
        field[i] = (char*)malloc(FIELD_COLS * sizeof(char));
        for(int j = 0; j < FIELD_COLS-1; j++){
            field[i][j] = FIELD_FILLER;
        }
        field[i][FIELD_COLS] = '\0';
    }
    return field;
}

void draw_field(char** field){
    for(int i = 0; i < FIELD_ROWS; i++){
        printf("%s\n", field[i]);
    }
}

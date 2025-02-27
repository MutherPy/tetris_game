
typedef enum actions {
    LEFT=1,
    RIGHT=2,
    ROTATE=3
} Actions;


typedef enum form {
    LINE=1,
    SS=2,
    SQW=3
} Form;


typedef struct object {
    Form type;

    int x_l_u;
    int y_l_u;
    int x_r_d;
    int y_r_d;

    char** figure;

    void (*rotate)(struct object* ob);
} Object;


#define FIGURE_BLOCK '#'
static const char LINE_FIGURE[] = {FIGURE_BLOCK, FIGURE_BLOCK,FIGURE_BLOCK,FIGURE_BLOCK,FIGURE_BLOCK};
static const char SS_FIGURE[][5] = {
        {FIGURE_BLOCK,FIGURE_BLOCK,FIGURE_BLOCK, '\0', '\0'},
        { '\0', '\0', FIGURE_BLOCK,FIGURE_BLOCK,FIGURE_BLOCK}
};
static const char SQW_FIGURE[][2] = {{FIGURE_BLOCK,FIGURE_BLOCK}, {FIGURE_BLOCK,FIGURE_BLOCK}};

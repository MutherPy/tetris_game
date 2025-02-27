
#define FIGURE_BLOCK '#'
static const char LINE_FIGURE[] = {FIGURE_BLOCK, FIGURE_BLOCK,FIGURE_BLOCK,FIGURE_BLOCK, '\0'};
static const char SS_FIGURE[][5] = {
        {FIGURE_BLOCK,FIGURE_BLOCK,FIGURE_BLOCK, '\0', '\0'},
        { '\0', '\0', FIGURE_BLOCK,FIGURE_BLOCK,FIGURE_BLOCK}
};
static const char SQW_FIGURE[][5] = {
        {FIGURE_BLOCK,FIGURE_BLOCK, '\0', '\0', '\0'},
        {FIGURE_BLOCK,FIGURE_BLOCK, '\0', '\0', '\0'}
};

typedef struct object {
    Type type;

    int x_l_u;
    int y_l_u;

    int x_r_d;
    int y_r_d;

    void* figure;

    void (*rotate)(struct object*);
} Object;

Object* create_object(Type t);
Type generate_type();


#define FIGURE_BLOCK '#'

typedef struct object {
    Type type;

    int x_l_u;
    int y_l_u;

    int x_r_d;
    int y_r_d;

    char* figure;

    void (*rotate)(struct object*);
    void (*build)(struct object*);
    void (*move)(struct object*);
} Object;

Object* create_object(Type t);
Type generate_type();

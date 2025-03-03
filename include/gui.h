
#ifndef TYPES_SET
    #include "types.h"
    #define TYPES_SET
#endif

#ifndef TETRIS_GUI_SET
#define TETRIS_GUI_SET

    #include <gtk/gtk.h>

    #define CELL_SIZE 40  // Size of each square in pixels
    #define BORDER_WIDTH 1

    typedef enum {
        BLOCK_TYPE_EMPTY=0,
        BLOCK_TYPE_FILLED=1
    } BlockType;

    // Structure to represent a square
    typedef struct {
        GtkWidget *widget;
        int x, y;         // Grid coordinates (0,0) is top-left
        double color[3];  // RGB color values
    } Square;

    Square squares[FIELD_ROWS][FIELD_COLS]; // Collection of squares

    typedef struct {
        us_type** mesh;
        us_type mesh_len;
    } DrawParams;

    GtkWidget* create_colored_square(int x, int y);
    void update_color(us_type x, us_type y, BlockType block_type);
    gboolean draw_field(void* args);

#endif

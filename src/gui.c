#include "../include/gui.h"


static void set_default_color(double color[3]){
    color[0] = 1.0;
    color[1] = 1.0;
    color[2] = 1.0;
};

static void set_block_color(double color[3]){
    color[0] = 1.0;
    color[1] = 0.5;
    color[2] = 0.6;
}

void update_color(us_type x, us_type y, BlockType block_type) {
    switch (block_type) {
        case BLOCK_TYPE_FILLED:
            set_block_color(squares[y][x].color);
            break;
        case BLOCK_TYPE_EMPTY:
            set_default_color(squares[y][x].color);
            break;
    }
    gtk_widget_queue_draw(squares[y][x].widget);
}

// Redraw function for each square
static gboolean draw_callback(GtkWidget *widget, cairo_t *cr, gpointer data) {
    Square *square = (Square *)data;

    // Set the color
    cairo_set_source_rgb(cr, square->color[0], square->color[1], square->color[2]);
    cairo_paint(cr);
    // Draw border
    cairo_set_source_rgb(cr, 0, 0, 0); // Black border
    cairo_set_line_width(cr, BORDER_WIDTH);
    cairo_rectangle(cr, 0, 0, CELL_SIZE, CELL_SIZE);
    cairo_stroke(cr);
    return FALSE;
}

// Create a square at (x, y)
GtkWidget* create_colored_square(int x, int y) {
    GtkWidget *drawing_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawing_area, CELL_SIZE, CELL_SIZE);

    // Initialize square properties
    squares[y][x].widget = drawing_area;
    squares[y][x].x = x;
    squares[y][x].y = y;
    set_default_color(squares[y][x].color); // Set initial random color

    // Connect draw signal
    g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(draw_callback), &squares[y][x]);
    return drawing_area;
}

gboolean draw_field(void* args){
    DrawParams *dr_par = (DrawParams*) args;
    us_type sum = dr_par->mesh_len;
    us_type** m = dr_par->mesh;
    for(us_type i = 0; i < FIELD_ROWS; i++){
        for(us_type j = 0; j < FIELD_COLS; j++){
            update_color(j, i, BLOCK_TYPE_EMPTY);
            for(int k = 0; k < sum; k++){
                if(m[k][0] == j && m[k][1] == i){
                    update_color(j, i, BLOCK_TYPE_FILLED);
                }
            }
        }
    }
    free(dr_par->mesh);
    return G_SOURCE_REMOVE;
}

#include <stdlib.h>
#include <termios.h>
#include <time.h>
#include <glib.h>

#include "../include/gui.h"

#include "../include/types.h"
#include "../include/object.h"
#include "../include/object_manager.h"
#include "../include/field_manager.h"

#define DOWN_DELAY 500

bool run_game = true;

static gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data) {
    Object** current_obj_ptr = (Object**)user_data;
    switch (event->keyval) {
        case GDK_KEY_Left:
            object_action_manager(OBJECT_ACTION_LEFT, *current_obj_ptr);
            break;
        case GDK_KEY_Right:
            object_action_manager(OBJECT_ACTION_RIGHT, *current_obj_ptr);
            break;
        case GDK_KEY_space:
            object_action_manager(OBJECT_ACTION_ROTATE, *current_obj_ptr);
            break;
    }
    return FALSE; // Return TRUE to stop event propagation
}

static gboolean downer(gpointer args){
    Object** cur_obj_ptr = (Object**)args;
    object_action_manager(OBJECT_ACTION_DOWN, *cur_obj_ptr);
    return TRUE;
}

static void* game_logic(gpointer args){
    Object** current_obj_ptr = (Object**)args;
    DrawParams dr_params;
    while(run_game) {
        us_type** mesh = manage_field(*current_obj_ptr);
        dr_params.mesh = mesh;
        dr_params.mesh_len = get_mesh_sum(*current_obj_ptr);
        g_idle_add(draw_field, &dr_params);
        if ((*current_obj_ptr)->is_collision)
            next_object(current_obj_ptr);
        g_usleep(90000);
    }
    return NULL;
}

int main(int argc, char** argv) {
    srand(time(0));

    Object* current_obj = new_object();
    filled_field_init();

    gtk_init(&argc, &argv);
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Tetris");
    gtk_window_set_default_size(GTK_WINDOW(window), FIELD_COLS * CELL_SIZE, FIELD_ROWS * CELL_SIZE);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    for (int y = 0; y < FIELD_ROWS; y++) {
        for (int x = 0; x < FIELD_COLS; x++) {
            GtkWidget *square = create_colored_square(x, y);
            gtk_grid_attach(GTK_GRID(grid), square, x, y, 1, 1);
        }
    }

    gtk_widget_add_events(window, GDK_KEY_PRESS_MASK);
    g_signal_connect(window, "key-press-event", G_CALLBACK(on_key_press), &current_obj);

    g_timeout_add(DOWN_DELAY, downer, &current_obj);
    g_thread_new("game_logic", game_logic, &current_obj);
    gtk_widget_show_all(window);
    gtk_main();
    run_game = false;
    return 0;
}

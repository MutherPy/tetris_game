#include <stdlib.h>
#include <termios.h>
#include <time.h>
#include <glib.h>

#include "../include/gui.h"

#include "../include/types.h"
#include "../include/object.h"
#include "../include/object_manager.h"
#include "../include/field_manager.h"
#include "../include/memory_utils.h"

#define DOWN_DELAY 300

bool run_game = true;
bool run_inner_game = true;

static gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data) {
    Object** current_obj_ptr = (Object**)user_data;
    switch (event->keyval) {
        case GDK_KEY_Left:
            object_action_manager(OBJECT_ACTION_LEFT, *current_obj_ptr);
            break;
        case GDK_KEY_Right:
            object_action_manager(OBJECT_ACTION_RIGHT, *current_obj_ptr);
            break;
        case GDK_KEY_Down:
            object_action_manager(OBJECT_ACTION_DOWN, *current_obj_ptr);
            break;
        case GDK_KEY_space:
            object_action_manager(OBJECT_ACTION_ROTATE, *current_obj_ptr);
            break;
    }
    return FALSE;
}

static gboolean downer(gpointer args){
    Object** cur_obj_ptr = (Object**)args;
    object_action_manager(OBJECT_ACTION_DOWN, *cur_obj_ptr);
    return TRUE;
}

static void* game_logic(gpointer args){
    GameLogicParams* g_params_ptr = (GameLogicParams*)args;
    Object** current_obj_ptr = g_params_ptr->current_object;

    DrawParams dr_params;
    dr_params.grid_parent = g_params_ptr->parent_grid;

    while (run_inner_game) {
        while (run_game) {
            if (*current_obj_ptr == NULL) continue;
            if (!(*current_obj_ptr)->is_acted) {
                g_usleep(90000);
                continue;
            }
            dr_params.mesh = manage_field(*current_obj_ptr);
            if (dr_params.mesh == NULL){
                break;
            }
            dr_params.mesh_len = get_mesh_sum(*current_obj_ptr);

            g_idle_add(draw_field, &dr_params);

            set_object_as_unacted(*current_obj_ptr);
            if ((*current_obj_ptr)->is_collision)
                next_object(current_obj_ptr);
            g_usleep(90000);
        }
        filled_field_cleanup();
        g_usleep(1000000);
        next_object(current_obj_ptr);
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

    GameLogicParams g_params = {
            .current_object = &current_obj,
            .parent_grid = (GtkContainer* )grid
    };
    gtk_widget_show_all(window);
    g_thread_new("game_logic", game_logic, &g_params);
    g_timeout_add(DOWN_DELAY, downer, &current_obj);
    gtk_main();
    run_game = false;
    run_inner_game = false;
    return 0;
}

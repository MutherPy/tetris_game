#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <termios.h>

#include "components_headers/types.h"

#include "components_headers/field_manager.h"
#include "components_headers/object_manager.h"


void* key_reader(void *args){
    static char key;
    struct termios info;
    tcgetattr(0, &info);          /* get current terminal attirbutes; 0 is the file descriptor for stdin */
    info.c_lflag &= ~ICANON;      /* disable canonical mode */
    info.c_cc[VMIN] = 1;          /* wait until at least one keystroke available */
    info.c_cc[VTIME] = 0;         /* no timeout */
    tcsetattr(0, TCSANOW, &info); /* set immediately */

    char _case;

    Object* current_obj = (Object*)args;

    while (1)
    {
        key = (char)getchar();
        _case = 0;
        if(key == '\033'){
            getchar();
            _case = (char)getchar();
        } else if (key == ' ') {
            _case = ' ';
        }
        switch (_case){
            case 'C':
                object_controller(RIGHT, current_obj);
                break;
            case 'D':
                object_controller(LEFT, current_obj);
                break;
            case ' ':
                object_controller(ROTATE, current_obj);
                break;
            default:
                continue;
        }
    }
}

int main(void) {

    Object* current_obj = NULL;

    static pthread_t thread_id;
    if (!thread_id) {
        pthread_create(&thread_id, NULL, key_reader, current_obj);
    }

    char** field = init_fill_field();
    if(field == NULL){
        return 1;
    }
    while (1) {
        system("clear");
        draw_field(field);
        sleep(2);
    }
    return 0;
}

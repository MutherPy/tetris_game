
#ifndef FIELD_MANAGER_OBJ_SET
#define FIELD_MANAGER_OBJ_SET
    #include "types.h"

    typedef struct node {
        us_type value;
        struct node* next;
    } Node;

    typedef struct list {
        Node* head;
        us_type size;
    } List;

    void init_list(List*);
    void free_list(List*);
    void append(List*, us_type);
    us_type get_val(List*, us_type);

#endif

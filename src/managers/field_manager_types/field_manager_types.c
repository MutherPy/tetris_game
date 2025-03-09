#include "../../../include/field_manager_types.h"
#include <stdlib.h>
#include "assert.h"

void init_list(List* lst){
    lst->size = 0;
    lst->head = NULL;
}

void free_list(List* lst){
    Node* save_next = lst->head;
    Node* next;
    while (save_next != NULL){
        next = save_next->next;
        free(save_next);
        save_next = next;
    }
    free(lst);
}

static Node* set_new_node_val(us_type val){
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->next = NULL;
    new_node->value = val;
    return new_node;
}

void append(List* lst, us_type val){
    if (lst->head == NULL){
        lst->head = set_new_node_val(val);
    } else {
        Node *last_node = lst->head;
        while (last_node->next != NULL) {
            last_node = last_node->next;
        }
        last_node->next = set_new_node_val(val);
    }
    lst->size++;
}

us_type get_val(List* lst, us_type index){
    assert(index <= lst->size);
    us_type current_index = 0;
    Node* current_node = lst->head;
    if (current_node == NULL) assert(current_node);
    while (current_index < index && current_node->next != NULL){
        current_node = current_node->next;
        current_index++;
    }
    return current_node->value;
}

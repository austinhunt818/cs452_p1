#include "lab.h"

list_t *list_init(void (*destroy_data)(void *), int (*compare_to)(const void *, const void *)){
    list_t *list = (list_t *)malloc(sizeof(list_t));
    list->destroy_data = destroy_data;
    list->compare_to = compare_to;
    list->size = 0;
    list->head = (node_t *)malloc(sizeof(node_t));
    list->head->next = list->head;
    list->head->prev = list->head;
    return list;
}

void list_destroy(list_t **list){

}

list_t *list_add(list_t *list, void *data){

    return list;
}

int list_compare_to(const void *a, const void *b){
    return 0;
}

void *list_remove_index(list_t *list, size_t index){

}

int list_indexof(list_t *list, void *data){
    return 0;
}
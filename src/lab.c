#include "lab.h"

list_t *list_init(void (*destroy_data)(void *), int (*compare_to)(const void *, const void *)){
    list_t *list = (list_t *)malloc(sizeof(list_t));
    list->destroy_data = destroy_data;
    list->compare_to = compare_to;
    list->size = 0;
    list->head = (node_t *)malloc(sizeof(node_t));
    list->head->data = NULL;
    list->head->next = list->head;
    list->head->prev = list->head;
    return list;
}

void list_destroy(list_t **list){
    node_t *current = (*list)->head->next;
    while(current != (*list)->head){
        node_t *next = current->next;
        (*list)->destroy_data(current->data);
        free(current);
        current = next;
    }
    free((*list)->head);
    free(*list);
    *list = NULL;
}

list_t *list_add(list_t *list, void *data){

    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    new_node->data = data;
    new_node->next = list->head->next;
    new_node->prev = list->head;
    list->head->next->prev = new_node;
    list->head->next = new_node;
    list->size++;

    return list;
}

void *list_remove_index(list_t *list, size_t index){
    node_t *current = list->head->next;
    if(index < 0 || index >= list->size || list->size == 0){
        return NULL;
    }

    for(size_t i = 0; i < index; i++){
        current = current->next;
    }
    current->prev->next = current->next;
    current->next->prev = current->prev;

    list->size--;
    void* data = current->data;
    free(current);
    
    return data;
    
}

int list_indexof(list_t *list, void *data){
    node_t *current = list->head->next;
    for(int i = 0; i < (int)list->size; i++){
        if(list->compare_to(current->data, data) == 0){
            return i;
        }
        current = current->next;
    }

    return -1;
}
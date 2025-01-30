#include "lab.h"

list_t *list_init(void (*destroy_data)(void *), int (*compare_to)(const void *, const void *)){
    list_t *list = (list_t *)malloc(sizeof(list_t));
    if (list == NULL) {
        return NULL; //return null if allocation fails
    }

    //set callback functions
    list->destroy_data = destroy_data;
    list->compare_to = compare_to;

    //set size and head(sentinel) with a new node
    list->size = 0;
    list->head = (node_t *)malloc(sizeof(node_t));

    //sentinel data should be null
    list->head->data = NULL;
    
    //empty list has sentinel point to itself
    list->head->next = list->head;
    list->head->prev = list->head;

    return list;
}

void list_destroy(list_t **list){

    //iterate through list, destroying the data and freeing each node
    node_t *current = (*list)->head->next;
    while(current != (*list)->head){
        node_t *next = current->next;
        (*list)->destroy_data(current->data);
        free(current);
        current = next;
    }
    
    free((*list)->head); //free the sentinel
    free(*list); //free the list
    *list = NULL;
}

list_t *list_add(list_t *list, void *data){

    //check if list and data are non-null values
    if (list == NULL || data == NULL) {
        return NULL;
    }   

    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    if (new_node == NULL) { //return null if allocation fails
        return NULL;
    }

    //instantiate new node with data, and set the proper next and previous pointers
    new_node->data = data;
    new_node->next = list->head->next;
    new_node->prev = list->head;

    //set the pointers of the surrounding ndoes
    list->head->next->prev = new_node;
    list->head->next = new_node;

    list->size++;

    return list;
}

void *list_remove_index(list_t *list, size_t index){
    
    //validate list
    if(list == NULL || index >= list->size || list->size == 0){
        return NULL;
    }
    node_t *current = list->head->next;

    //iterate through until reaching the index
    for(size_t i = 0; i < index; i++){
        current = current->next;
    }

    //shift surrounding nodes' pointers
    current->prev->next = current->next;
    current->next->prev = current->prev;

    //decrease size and free the removed node
    list->size--;
    void* data = current->data;
    free(current);
    
    return data;
    
}

int list_indexof(list_t *list, void *data){
    //validate list and data
    if (list == NULL || data == NULL) {
        return -1;
    }

    //iterate through, comparing until you find the value
    node_t *current = list->head->next;
    for(int i = 0; i < (int)list->size; i++){
        if(list->compare_to(current->data, data) == 0){
            return i;
        }
        current = current->next;
    }

    return -1;
}
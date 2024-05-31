#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * Basic struct that defines an arraylist. The arraylist is array-backed,
 * containing an array of void pointers. Basic metadata such as size, capacity,
 * and rear index are also included.
*/
typedef struct {
    void **elements;
    uint64_t size;
    uint64_t capacity;
    uint64_t element_size;
} arraylist_t;

/**
 * Basic arraylist functions.
*/
void arraylist_init(arraylist_t *arraylist, uint64_t capacity, uint64_t element_size);
void arraylist_resize(arraylist_t *arraylist, uint64_t newsize);

void arraylist_add_at_index(arraylist_t *arraylist, void *element, uint64_t index);
void* arraylist_remove_at_index(arraylist_t* arraylist, uint64_t index);
void arraylist_enqueue(arraylist_t *arraylist, void *element);
void* arraylist_dequeue(arraylist_t *arraylist);
void arraylist_enqueue_front(arraylist_t *arraylist, void *element);
void* arraylist_dequeue_back(arraylist_t *arraylist);

void arraylist_move_to_index(arraylist_t *arraylist, uint64_t current_index, uint64_t new_index);
void arraylist_swap(arraylist_t *arraylist, uint64_t index_1, uint64_t index_2);

bool arraylist_is_full(arraylist_t *arraylist);
bool arraylist_is_empty(arraylist_t *arraylist);
bool arraylist_contains(arraylist_t *arraylist);

void arraylist_print_info(arraylist_t *arraylist);


#endif
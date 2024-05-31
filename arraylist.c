#include "arraylist.h"

/**
 * Initializes the arraylist to a set capacity. Note that the pointer for the arraylist
 * itself must already be allocated.
 *
 * @param arraylist Pointer to the arraylist you want to initalize (already malloced)
 * @param capacity 64 bit integer that represents the initial capacity for the array
 * @param element_size The size in bytes of an element.
*/
void arraylist_init(arraylist_t *arraylist, uint64_t capacity, uint64_t element_size) {
    if (!arraylist) {
        exit(1);
    }
    if (capacity < 0 || element_size < 0) {
        exit(1);
    }
    if (capacity == 0 || element_size == 0) {
        return;
    }

    arraylist->elements = (void**) malloc(capacity * sizeof(element_size));
    if (!arraylist->elements) {
        exit(1);
    }

    arraylist->size = 0;
    arraylist->capacity = capacity;
    arraylist->element_size = element_size;
}

/**
 * Resizes the arraylist's backing array to a set capacity. Can size up and size down
 * (requires newsize to be greater than or equal to the current size if downsizing).
 *
 * @param arraylist Pointer to the arraylist we are resizing
 * @param newsize Integer representing the new size.
*/
void arraylist_resize(arraylist_t *arraylist, uint64_t newsize) {
    if (!arraylist) {
        exit(1);
    }
    if (!arraylist->elements) {
        exit(1);
    }
    if (newsize < arraylist->size) {
        exit(1);
    }

    arraylist->elements = realloc(arraylist->elements, (size_t) (newsize * arraylist->element_size));
    if (!arraylist->elements) {
        exit(1);
    }

    arraylist->capacity = newsize;
}

/**
 * Adds a specified element to the arraylist at an index. Note that when using this function, the
 * added element must be cast to a void pointer.
 *
 * NOTE: It is up to the programmer to make sure that the element is of proper size. It's cast to a
 * void pointer here, so there is no way to tell.
 *
 * @param arraylist The arraylist we're adding to.
 * @param element The element we want to add.
 * @param index The index that we want to add the element at.
*/
void arraylist_add_at_index(arraylist_t *arraylist, void *element, uint64_t index) {
    if (!arraylist) {
        exit(1);
    }
    if (!element) {
        exit(1);
    }
    if (index < 0 || index > arraylist->size) {
        exit(1);
    }
    if (arraylist->size == arraylist->capacity) {
        exit(1);
    }

    for (uint64_t i = arraylist->size; i > index; i--) {
        arraylist->elements[i] = arraylist->elements[i - 1];
    }
    arraylist->elements[index] = element;

    arraylist->size += 1;
}

/**
 * Removes and returns an element at the specified index. Note that the element will be
 * returned as a void pointer, so the programmer must cast it to its original state.
 *
 * @param arraylist The arraylist.
 * @param index The index we want to remove at.
 * @returns The element (as a void pointer)
*/
void* arraylist_remove_at_index(arraylist_t* arraylist, uint64_t index) {
    if (!arraylist) {
        exit(1);
    }
    if (index < 0 || index >= arraylist->size) {
        exit(1);
    }

    void* element = arraylist->elements[index];
    for (uint64_t i = index; i < arraylist->size - 1; i++) {
        arraylist->elements[i] = arraylist->elements[i + 1];
    }
    arraylist->elements[arraylist->size - 1] = 0;
    arraylist->size -= 1;

    return element;
}

/**
 * Adds an element to the back of the arraylist.
 *
 * @param arraylist The arraylist.
 * @param element The element (void pointer, you must cast it).
*/
void arraylist_enqueue(arraylist_t *arraylist, void *element) {
    if (!arraylist) {
        exit(1);
    }
    arraylist_add_at_index(arraylist, element, arraylist->size);
}

/**
 * Remove and returns the element at the front of the arraylist.
 *
 * @param arraylist The arraylist.
 * @returns The element removed (as a void pointer).
*/
void* arraylist_dequeue(arraylist_t *arraylist) {
    return arraylist_remove_at_index(arraylist, 0);
}

/**
 * Adds an element to the front of the arraylist.
 *
 * @param arraylist The arraylist.
 * @param element The element (void pointer, you must cast it).
*/
void arraylist_enqueue_front(arraylist_t *arraylist, void *element) {
    arraylist_add_at_index(arraylist, element, 0);
}

/**
 * Removes and returns the element at the back of the arraylist.
 *
 * @param arraylist The arraylist.
 * @returns The element removed (as a void pointer).
*/
void* arraylist_dequeue_back(arraylist_t *arraylist) {
    if (!arraylist) {
        exit(1);
    }
    return arraylist_remove_at_index(arraylist, arraylist->size - 1);
}

/**
 * Moves a specified element in the arraylist to a new index.
 *
 * @param arraylist The arraylist.
 * @param current_index The index of the element we want to move.
 * @param new_index The index we want to move it to.
*/
void arraylist_move_to_index(arraylist_t *arraylist, uint64_t current_index, uint64_t new_index) {
    if (!arraylist) {
        exit(1);
    }
    if (current_index < 0 || new_index < 0 || current_index >= arraylist->size || new_index >= arraylist->size) {
        exit(1);
    }

    if (current_index == new_index) {
        return;
    }

    void *current_element = arraylist_remove_at_index(arraylist, current_index);
    arraylist_add_at_index(arraylist, current_element, new_index);
}


/**
 * Swaps the element at index_1 with the element at index_2.
 *
 * @param arraylist The arraylist.
 * @param index_1 Index #1.
 * @param index_2 Index #2.
*/
void arraylist_swap(arraylist_t *arraylist, uint64_t index_1, uint64_t index_2) {
    if (!arraylist) {
        exit(1);
    }
    if (index_1 < 0 || index_2 < 0 || index_1 >= arraylist->size || index_2 >= arraylist->size) {
        exit(1);
    }

    if (index_1 == index_2) {
        return;
    }

    void *element_1 = arraylist->elements[index_1];
    arraylist->elements[index_1] = arraylist->elements[index_2];
    arraylist->elements[index_2] = element_1;
}

/**
 * Checks if the arraylist is full or not.
 *
 * @param arraylist The arraylist.
 * @returns A bool, true if full, false if not.
*/
bool arraylist_is_full(arraylist_t *arraylist) {
    if (!arraylist) {
        exit(1);
    }

    return arraylist->size == arraylist->capacity;
}

/**
 * Checks if arraylist is empty or not.
 *
 * @param arraylist The arraylist.
 * @returns A bool, true if empty, false if not.
*/
bool arraylist_is_empty(arraylist_t *arraylist) {
    if (!arraylist) {
        exit(1);
    }

    return arraylist->size == 0;
}

/**
 * Linearally searches the arraylist to see if it contains the specified element.
 *
 * @param arraylist The arraylist.
 * @param element A void pointer for the element (don't forget to cast this).
 * @returns A bool, true if the element is contained, false if not.
*/
bool arraylist_contains(arraylist_t *arraylist, void* element) {
    if (!arraylist || !element) {
        exit(1);
    }

    for (uint64_t i = 0; i < arraylist->size; i++) {
        if (arraylist->elements[i] == element) {
            return true;
        }
    }
    return false;
}

/**
 * Prints info about the arraylist.
 *
 * @param arraylist The arraylist we are printing, duh.
*/
void arraylist_print_info(arraylist_t *arraylist) {
    if (!arraylist) {
        printf("=====================================================\n\n");
        printf("The Arraylist you are trying to print does not exist!\n\n");
        printf("=====================================================\n");
        return;
    }

    printf("=====================================================\n\n");
    printf("Pointer address: \t 0x%x\n", arraylist);
    printf("Size: \t\t\t\t %d\n", arraylist->size);
    printf("Capacity: \t\t\t %d\n", arraylist->capacity);
    printf("Element Size: \t\t %d\n\n", arraylist->element_size);

    if (!arraylist->elements || arraylist->size == 0) {
        printf("No elements to display.\n");
    } else {
        for (uint64_t i = 0; i < arraylist->size; i++) {
            printf("%d:\t%d\n", i, (uint64_t) arraylist->elements[i]);
        }
    }

    printf("\n=====================================================\n");

}
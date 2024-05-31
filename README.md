# simple-c-arraylist

Super simple arraylist implementation for C11. Originally wrote this because I needed it for a school project.

To create an instance of an arraylist, first allocate for the pointer, then call `arraylist_init()` on that pointer, like so:

```
arraylist_t *my_array = malloc(sizeof(arraylist_t));
arraylist_init(my_array, 4, sizeof(char));   // Initializes the arraylist to hold a max of 4 chars.
```

From here, you can simply call any of the provided functions on your arraylist. Note that when dealing with the individual elements of the array, you must cast them to void pointers.

```
arraylist_enqueue(my_array, (void*) 'a');
arraylist_enqueue(my_array, (void*) 'b');
arraylist_enqueue(my_array, (void*) 'c');

char letter = (char) arraylist_remove_at_index(my_array, 1);
```
Note that in the case of an error (such as an index out of bounds), functions will call `exit(1)` to exit the code with error.

You are responsible for freeing the `arraylist->elements` backing array when finished, as well as any allocated memory that is held in the `elements` backing array.

```
free(my_array->elements);
free(my_array);
```
Happy coding!

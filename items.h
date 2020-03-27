#ifndef ITEMS
#define ITEMS
#include <stdbool.h>

/**
 * Linked List of item. Each node consists of a name and a pointer to the next item. 
 */
struct items {
    char *name;
    struct items *next;
};

typedef struct items Items;

/**
 * Constructor, create a new node in the LinkedList.
 */
Items *items(char *name, Items *next);

/**
 * Delete an item with the name equal to @name from the list.
 */
Items *drop_item(char *name, Items *head);

/**
 * Add a new item with @name to the end of list.
 */
void add_item(char *name, Items *head);

/**
 * Print all the items in the list
 */
void check_item(Items *head);

/**
 * Check if item with @name appear on the list.
 */
bool contains_item(char *name, Items *head);

/**
 * return the number items in the list
 */
int size(Items *head);

/**
 * Clear the list
 */
void item_free(Items *head);
#endif
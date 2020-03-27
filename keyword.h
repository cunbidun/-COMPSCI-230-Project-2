#ifndef __KEYWORD
#define __KEYWORD
#include <stdbool.h>

/**
 * Linked List of commands. Each node consists of a keyword and a pointer to the next commands. 
 */
struct commands {
    char *key;
    struct commands *next;
};

typedef struct commands Commands;

/**
 * Constructor, create a new node in the LinkedList.
 */
Commands *command(char *command, Commands *next);

/**
 * Add a new @command to the end of list @head.
 */
Commands *add_command(char *command, Commands *head);

/**
 * Print all the commands in the list
 */
void lookup_command(Commands *head);

/**
 * Check if list contains a command @command.
 */
bool contains_command(char *command, Commands *head);

/**
 * Clear the list.
 */
void command_free(Commands *head);
#endif
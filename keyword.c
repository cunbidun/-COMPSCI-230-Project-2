#include "keyword.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Commands *command(char *name, Commands *next) {
    Commands *command = (Commands *)malloc(sizeof(Commands));
    assert(command != NULL);
    command->key = strdup(name);
    command->next = next;
    return command;
};

Commands *add_command(char *name, Commands *head) {
    while (head->next != NULL)
        head = head->next;
    head->next = command(name, NULL);
}

void lookup_command(Commands *head) {
    int cnt = 1;
    printf("Table of command:\n");
    while (head->next != NULL) {
        printf("%d. %s\n", cnt++, head->next->key);
        head = head->next;
    }
}

bool contains_command(char *command, Commands *head) {
    while (head->next != NULL) {
        if (strcmp(command, head->next->key) == 0)
            return 1;
        head = head->next;
    }
    return 0;
}

void command_free(Commands *head) {
    if(head == NULL) return;
    command_free(head->next);
    free(head);
    head = NULL;
}

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "items.h"

Items *items(char *name, Items *next) {
    Items *items = (Items *)malloc(sizeof(Items));
    assert(items != NULL);
    items->name = strdup(name);
    items->next = next;
    return items;
}

Items *drop_item(char *name, Items *head) {
    while (head->next != NULL) {
        if (strcmp(head->next->name, name) == 0) {
            Items *dummy = head->next;
            head->next = head->next->next;
            Items *toReturn = items(dummy->name, NULL);
            free(dummy);
            dummy = NULL;
            return toReturn;
        }
        head = head->next;
    }
    return NULL;
}

void add_item(char *name, Items *head) {
    while (head->next != NULL)
        head = head->next;
    head->next = items(name, NULL);
}

void check_item(Items *head) {
    int cnt = 1;
    while (head->next != NULL) {
        printf("%d. %s\n", cnt++, head->next->name);
        head = head->next;
    }
}

bool contains_item(char *name, Items *head) {
    while (head->next != NULL) {
        if (strcmp(name, head->next->name) == 0)
            return 1;
        head = head->next;
    }
    return 0;
}

int size(Items *head) {
    int cnt = 0;
    while (head->next != NULL)
        head = head->next, cnt++;
    return cnt;
}

void item_free(Items *head) {
    if(head == NULL) return;
    item_free(head->next);
    free(head);
    head = NULL;
}

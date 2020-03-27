#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "items.h"
#include "room.h"

Room *room(char *description, Items *items, bool has_omen, bool has_event) {
    Room *room = (Room *)malloc(sizeof(Room));
    assert(room != NULL);
    room->description = description;
    room->items = items;
    room->north = NULL;
    room->east = NULL;
    room->west = NULL;
    room->south = NULL;
    room->up = NULL;
    room->down = NULL;
    room->has_omen = has_omen;
    room->has_event = has_event;
}

void connect_room(Room *current, Room *other, char *dir) {
    if (strcmp(dir, "north") == 0)
        current->north = other;

    if (strcmp(dir, "south") == 0)
        current->south = other;

    if (strcmp(dir, "west") == 0)
        current->west = other;

    if (strcmp(dir, "east") == 0)
        current->east = other;

    if (strcmp(dir, "up") == 0)
        current->up = other;

    if (strcmp(dir, "down") == 0)
        current->down = other;
}

void disconnect_room(Room *current, char *dir) {
    if (strcmp(dir, "north") == 0)
        current->north = NULL;

    if (strcmp(dir, "south") == 0)
        current->south = NULL;

    if (strcmp(dir, "west") == 0)
        current->west = NULL;

    if (strcmp(dir, "east") == 0)
        current->east = NULL;

    if (strcmp(dir, "up") == 0)
        current->up = NULL;

    if (strcmp(dir, "down") == 0)
        current->down = NULL;
}

void room_state(Room *room) {
    printf("%s.\n", room->description);
    int sz = size(room->items);
    if (sz) {
        printf("Room's items:\n");
        check_item(room->items);
    } else
        printf("There are no item in this room!\n");

    if (room->has_omen)
        printf("There is an omen in this room\n");
}
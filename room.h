#ifndef __ROOM
#define __ROOM
#include "items.h"
#include <stdbool.h>

/**
 * room object, a room with its properties.
 */
struct room {
    char *description;
    Items *items;
    struct room *north;
    struct room *south;
    struct room *east;
    struct room *west;
    struct room *up;
    struct room *down;
    bool has_omen;
    bool has_event;
};

typedef struct room Room;

/**
 * Create new Room with description, item list, whether the room has an omen and an event.
 */
Room *room(char *description, Items *items, bool has_omen, bool has_event);

/**
 * Connect room @current in direction @dir with room @other
 */
void connect_room(Room *current, Room *other, char *dir);

/**
 * Disonnect room @current in direction @dir
 */
void disconnect_room(Room *current, char *dir);

/**
 * Print the room state
 */
void room_state(Room *room);
#endif
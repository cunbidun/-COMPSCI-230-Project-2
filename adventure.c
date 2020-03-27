#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "items.h"
#include "keyword.h"
#include "room.h"

/**
 * Add commands to the list and initialize the rooms and permutation.
 */
void init(Commands *cmd, Room *room_list[6], int order[6]) {
    add_command("look", cmd);
    add_command("go", cmd);
    add_command("take", cmd);
    add_command("drop", cmd);
    add_command("inventory", cmd);
    add_command("help", cmd);

    room_list[0] = room("Room 1", items("\0", items("Diamond Pickaxe", NULL)), false, false);
    room_list[1] = room("Room 2", items("\0", items("Obsidian", NULL)), false, false);
    room_list[2] = room("Room 3", items("\0", NULL), true, false);
    room_list[3] = room("Room 4", items("\0", NULL), true, false);
    room_list[4] = room("Room 5", items("\0", NULL), false, true);
    room_list[5] = room("Room 6", items("\0", NULL), false, true);

    srand(time(NULL));
    for (int i = 0; i < 6; i++) {
        int j = rand() % 6;
        int t = order[j];
        order[j] = order[i];
        order[i] = t;
    }
}

/**
 * Clean up the memory when game end.
 */
void clean_up(Room *starting_room, Room *current_room, Room *room_list[6], Items *inven, Commands *command_list) {
    item_free(starting_room->items);
    free(starting_room);
    starting_room = NULL;

    item_free(current_room->items);
    free(current_room);
    current_room = NULL;
    for (int i = 0; i < 6; i++) {
        item_free(room_list[i]->items);
        free(room_list[i]);
        room_list[i] = NULL;
    }
    item_free(inven);
    command_free(command_list);
}

/**
 * Check if the game is ended
 */
bool is_end(Room *current_room, Items *inven, int omen_seen) { return strcmp(current_room->description, "the Starting Room") == 0 && size(inven) == 2 && omen_seen >= 1; }

void look(Room *room) {
    printf("This is ");
    room_state(room);
}

/**
 * Handle event when encouter
 */
int get_event(Room *starting_room) {
    int cnt = 0;
    int event[6];
    if (starting_room->north == NULL)
        event[cnt++] = 0;
    if (starting_room->east == NULL)
        event[cnt++] = 1;
    if (starting_room->south == NULL)
        event[cnt++] = 2;
    if (starting_room->west == NULL)
        event[cnt++] = 3;
    if (starting_room->up == NULL)
        event[cnt++] = 4;
    if (starting_room->down == NULL)
        event[cnt++] = 5;
    if (cnt == 0)
        return 7;
    srand(time(NULL));
    return event[rand() % cnt];
}

/**
 * Move the player in input direction
 */
void go(Room *starting_room, Room **current_room, Items *inven, char *dir, Room *room_list[6], int order[6], int *cur_index, int *omen_seen, Commands *command_list) {
    if (strcmp(dir, "north") == 0) {
        if ((*current_room)->north == NULL) {
            if (*cur_index >= 6) {
                printf("There is no room left to discover! Game over!\n");
                clean_up(starting_room, *current_room, room_list, inven, command_list);
                exit(0);
            }
            Room *next = room_list[order[(*cur_index)++]];
            connect_room(*current_room, next, "north");
            connect_room(next, *current_room, "south");
            *current_room = next;
        } else
            *current_room = (*current_room)->north;
    }

    if (strcmp(dir, "west") == 0) {
        if ((*current_room)->west == NULL) {
            if (*cur_index >= 6) {
                printf("There is no room left to discover! Game over!\n");
                clean_up(starting_room, *current_room, room_list, inven, command_list);
                exit(0);
            }
            Room *next = room_list[order[(*cur_index)++]];
            connect_room(*current_room, next, "west");
            connect_room(next, *current_room, "east");
            *current_room = next;
        } else
            *current_room = (*current_room)->west;
    }

    if (strcmp(dir, "east") == 0) {
        if ((*current_room)->east == NULL) {
            if (*cur_index >= 6) {
                printf("There is no room left to discover! Game over!\n");
                clean_up(starting_room, *current_room, room_list, inven, command_list);
                exit(0);
            }
            Room *next = room_list[order[(*cur_index)++]];
            connect_room(*current_room, next, "east");
            connect_room(next, *current_room, "west");
            *current_room = next;
        } else
            *current_room = (*current_room)->east;
    }

    if (strcmp(dir, "up") == 0) {
        if ((*current_room)->up == NULL) {
            if (*cur_index >= 6) {
                printf("There is no room left to discover! Game over!\n");
                clean_up(starting_room, *current_room, room_list, inven, command_list);
                exit(0);
            }
            Room *next = room_list[order[(*cur_index)++]];
            connect_room(*current_room, next, "up");
            connect_room(next, *current_room, "down");
            *current_room = next;
        } else
            *current_room = (*current_room)->up;
    }

    if (strcmp(dir, "down") == 0) {
        if ((*current_room)->down == NULL) {
            if (*cur_index >= 6) {
                printf("There is no room left to discover! Game over!\n");
                clean_up(starting_room, *current_room, room_list, inven, command_list);
                exit(0);
            }
            Room *next = room_list[order[(*cur_index)++]];
            connect_room(*current_room, next, "down");
            connect_room(next, *current_room, "up");
            *current_room = next;
        } else
            *current_room = (*current_room)->down;
    }

    if ((*current_room)->has_event) {
        int next = get_event(starting_room);
        if (next < 6) {
            printf("There is an event in this room. There room is now moving...\n");
            if ((*current_room)->north != NULL) {
                disconnect_room((*current_room)->north, "south");
                disconnect_room((*current_room), "north");
            }
            if ((*current_room)->south != NULL) {
                disconnect_room((*current_room)->south, "north");
                disconnect_room((*current_room), "south");
            }
            if ((*current_room)->up != NULL) {
                disconnect_room((*current_room)->up, "down");
                disconnect_room((*current_room), "up");
            }
            if ((*current_room)->down != NULL) {
                disconnect_room((*current_room)->down, "up");
                disconnect_room((*current_room), "down");
            }
            if ((*current_room)->east != NULL) {
                disconnect_room((*current_room)->east, "west");
                disconnect_room((*current_room), "east");
            }
            if ((*current_room)->west != NULL) {
                disconnect_room((*current_room)->west, "east");
                disconnect_room((*current_room), "west");
            }

            if (next == 0) {
                connect_room(starting_room, *current_room, "north");
                connect_room(*current_room, starting_room, "south");
            }
            if (next == 1) {
                connect_room(starting_room, *current_room, "east");
                connect_room(*current_room, starting_room, "west");
            }
            if (next == 2) {
                connect_room(starting_room, *current_room, "south");
                connect_room(*current_room, starting_room, "north");
            }
            if (next == 3) {
                connect_room(starting_room, *current_room, "west");
                connect_room(*current_room, starting_room, "east");
            }
            if (next == 4) {
                connect_room(starting_room, *current_room, "up");
                connect_room(*current_room, starting_room, "down");
            }
            if (next == 5) {
                connect_room(starting_room, *current_room, "down");
                connect_room(*current_room, starting_room, "up");
            }
        }
        (*current_room)->has_event = false;
    }
    if ((*current_room)->has_omen) {
        printf("There is an omen in this room!\n");
        (*omen_seen)++;
    }
    
    if (size((*current_room)->items))
        printf("There are some items in this room!\n");

    if (is_end(*current_room, inven, *omen_seen)) {
        printf("You Win!!!\n");
        printf("You mined the Obsidian and found the omen!\n");
        clean_up(starting_room, *current_room, room_list, inven, command_list);
        exit(0);
    }
}

/**
 * Take items from room
 */
void take(Room *current_room, Items *inven, char *to_take) {
    drop_item(to_take, current_room->items);
    add_item(to_take, inven);
}

/**
 * Drop items from inventory
 */
void drop(Room *current_room, Items *inven, char *to_take) {
    add_item(to_take, current_room->items);
    drop_item(to_take, inven);
}

/**
 *  Check if the input direction is valid
 */
bool valid_dir(char *dir) { return strcmp(dir, "north") == 0 || strcmp(dir, "east") == 0 || strcmp(dir, "west") == 0 || strcmp(dir, "up") == 0 || strcmp(dir, "down") == 0; }

/**
 *  Get input when the string has more than 1 words
 */
char *getInput() {
    int tmp = getchar();
    int bytes_read;
    size_t nbytes = 100;
    char *new;
    new = (char *)malloc(nbytes + 1);
    bytes_read = getline(&new, &nbytes, stdin);
    if (new[strlen(new) - 1] == '\n')
        new[strlen(new) - 1] = '\0';
    return new;
}   

int main() {
    Items *inven = items("\0", NULL);
    Commands *command_list = command("\0", NULL);
    Room *starting_room = room("the Starting Room", items("\0", NULL), 0, 0);

    Room *current_room = starting_room;
    Room *room_list[6];
    int order[] = {0, 1, 2, 3, 4, 5};

    int cur_index = 0;

    int omen_seen = 0;
    init(command_list, room_list, order);

    while (1) {
        printf("Input command: ");
        char cmd[20];
        scanf("%s", cmd);
        if(!contains_command(cmd, command_list)) {
            printf("Invalid Commands! Please try again!\n\n");
            continue;
        }

        if (strcmp(cmd, "go") == 0) {
            char dir[20];
            scanf("%s", dir);
            if (!valid_dir(dir))
                printf("Invalid Direction! Please try again!\n");
            else
                go(starting_room, &current_room, inven, dir, room_list, order, &cur_index, &omen_seen, command_list);
            printf("\n");
            continue;
        }

        if (strcmp(cmd, "drop") == 0) {
            if (size(inven) == 0)
                printf("Your inventory is empty!\n");
            else {
                char *item = getInput();
                if (!contains_item(item, inven))
                    printf("You dont have '%s' in your inventory!\n", item);
                else
                    drop(current_room, inven, item);
            }
            printf("\n");
            continue;
        }

        if (strcmp(cmd, "take") == 0) {
            if (size(current_room->items) == 0)
                printf("There is no item in this room!\n");
            else {
                char *item = getInput();
                if (!contains_item(item, current_room->items))
                    printf("There is no '%s' in this room!\n", item);
                else {
                    if (strcmp(item, "Obsidian") == 0 && size(inven) == 0)
                        printf("Cannot take the Obsidian now! You have to find the Diamond Pickaxe first!\n");
                    else
                        take(current_room, inven, item);
                }
            }
            printf("\n");
            continue;
        }

        if (strcmp(cmd, "look") == 0) {
            look(current_room);
            printf("\n");
            continue;
        }

        if (strcmp(cmd, "inventory") == 0) {
            if (size(inven) == 0)
                printf("Your inventory is empty!\n");
            else {
                printf("Your item(s):\n");
                check_item(inven);
            }
            printf("\n");
            continue;
        }

        // add new command
        if (strcmp(cmd, "add") == 0) {
            char *new = getInput();
            if (contains_command(new, command_list))
                printf("There is '%s' command in commands talbe! Please try again!\n", new);
            else {
                printf("Command '%s' added successfully!\n", new);
                add_command(new, command_list);
            }
            printf("\n");
            continue;
        }

        if (strcmp(cmd, "help") == 0) {
            lookup_command(command_list);
            printf("\n");
            continue;
        }

    }
}
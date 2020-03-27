This project is the implementation of Betrayal at House on the Hill.

You can move in any of the following direction:
1. north
2. east
3. west
4. up
5. down

The game consists of 7 rooms, including the starting room. It has 2 events, 2 omens, and 2 items.
1. 2 events will move the rooms contain them to next to the starting room.
2. 2 omen would not do anything, but you need to find at least one to win the game.
3. 2 items are a Diamond Pickaxe and a piece Obsidian. To obtain the Obsidian, you have to fine the Diamond Pickaxe first. And you have to obtain both of the item to win the game.

The last requirment is you have to find a way to the starting room.

Implementation detail: 
1. How rooms are taken from the pile
    First I create an array to store 6 rooms, indexed from 1 to 5.
    I generate a permutation from 0 to 5, and take the room out of the array in that permutation order.
2. How events are handled
    When there is a event, I check how many places next to the starting room is still available. And chose one of them randomly.

Requirements:
1. There are 7 rooms in this game.
2. There is only the starting room at the beginning of the game, and it is empty.
3. There are 2 items, 2 omens, 2 events in this game.
4. Each room has a LinkedList of items.
5. The player has their own LinkedList of items.
6. There is a LinkedList of commands, which consists of:
    1. look
    2. go DIRECTION (north, east, west, up, down)
    3. take ITEM
    4. drop ITEM
    5. inventory
    6. add COMMAND (to add new commands)
    7. help (to look up commands lists)
7. Each situation after moving is handled
8. There is a wining state, when player found 2 items and at least 1 omen, the avatar is in the starting room.
9. There is a losing state, when player tries to discover new room but the pile is already empty.
10. The project is divide to several file:
    1. rooms.c, rooms.h - the source and header file implementing data structures and functions for rooms.
    2. items.c, items.h - the source and header file implementing data structures and functions for items. There are add_item and drop_item function for adding/removing an item to/from a linkedList.
    3. keyword.c, keyword.h - the source and header file implementing data structures and functions for commands. There are funtion to add a command into the table and a function to lookup the commend in the table.
    4. adventure.c - the source file with functions to read user input and interpret commands as well as the main function.
    5. Makefile - the Makefile to use with the make command to build your code.

Additional Information:
1. There is no Global variables
2. Clean up memory before terminate the program.

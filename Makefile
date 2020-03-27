SRC = adventure.c items.c room.c keyword.c
OJB = adventure.o items.o room.o keyword.o
PROG = run

$(PROG): $(OJB) 
	gcc -std=c99 -Wall $(OJB) -o $(PROG)

$(OJB): $(SRC)

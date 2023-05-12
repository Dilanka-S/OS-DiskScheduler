CC = gcc
CFLAGS = -Wall -ansi -pedantic
OBJ = scheduler.o menus.o fileReader.o algorithms.o
EXEC = diskScheduler

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

scheduler.o : scheduler.c menus.h
	$(CC) $(CFLAGS) scheduler.c -c
menus.o : menus.c fileReader.h
	$(CC) $(CFLAGS) menus.c -c
fileReader.o : fileReader.c algorithms.h
	$(CC) $(CFLAGS) fileReader.c -c
algorithms.o : algorithms.c fileReader.h
	$(CC) $(CFLAGS) algorithms.c -c
clean :
	rm -f $(EXEC) $(OBJ)

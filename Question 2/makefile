CC = gcc
CFLAGS = -g -pthread
OBJ = simulator2.o menus.o fileReader.o algorithms.o
EXEC = diskScheduler

$(EXEC) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)

simulator2.o : simulator2.c menus.h algorithms.h scheduler.h
	$(CC) $(CFLAGS) simulator2.c -c
menus.o : menus.c fileReader.h
	$(CC) $(CFLAGS) menus.c -c
fileReader.o : fileReader.c algorithms.h
	$(CC) $(CFLAGS) fileReader.c -c
algorithms.o : algorithms.c fileReader.h
	$(CC) $(CFLAGS) algorithms.c -c
clean :
	rm -f $(EXEC) $(OBJ)

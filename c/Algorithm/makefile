# makefile sample

TARGET= sortalgorithem.out
CC= gcc
CFLAGS= -ansi -g -pedantic
OBJS= sortalgorithem.o Vector.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
	
sortalgorithem.o: sortalgorithem.c ADTDefs.h Vector.h
	$(CC) $(CFLAGS) -c sortalgorithem.c
	
Vector.o: Vector.c ADTDefs.h
	$(CC) $(CFLAGS) -c Vector.c
	
clean:
	rm -f $(TARGET) $(OBJS)

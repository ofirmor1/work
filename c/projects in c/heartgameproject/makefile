#makefile /*HEARTS GAME*/

TARGET = HeartsGame.out
CC = gcc
CFLAGS = -ansi -g -pedantic
OBJS = HeartsGame.o game.o round.o deck.o players.o ui.o  vector.o myitoa.o sortalgorithem.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

ui.o: ui.c ui.h
	$(CC) $(CFLAGS) -c ui.c
	
deck.o: deck.c deck.h
	$(CC) $(CFLAGS) -c deck.c
	
vector.o: vector.c vector.h
	$(CC) $(CFLAGS) -c vector.c	
	
game.o: game.c game.h
	$(CC) $(CFLAGS) -c game.c	
	
HeartsGame.o: HeartsGame.c
	$(CC) $(CFLAGS) -c HeartsGame.c
	
players.o: players.c players.h
	$(CC) $(CFLAGS) -c players.c

round.o: round.c round.h
	$(CC) $(CFLAGS) -c round.c

myitoa.o: myitoa.c myitoa.h
	$(CC) $(CFLAGS) -c myitoa.c
	
sortalgorithem.o: sortalgorithem.c sortalgorithem.h
	$(CC) $(CFLAGS) -c sortalgorithem.c

run: $(TARGET)
		./$(TARGET)
	
clean:
	rm -f $(TARGET) $(OBJS)

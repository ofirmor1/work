#makefile /*EXECUTOR*/

TARGET =  main.out
CC = gcc
CFLAGS = -I ../DS -g3 -pedantic 
OBJS = main.o executor.o task.o time.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) -L../DS -lgen -lm 
	
main.o: main.c 
	$(CC) $(CFLAGS) -c main.c	

executor.o: executor.c executor.h 
	$(CC) $(CFLAGS) -c executor.c 

task.o: task.c task.h
	$(CC) $(CFLAGS) -c task.c	

time.o: time.c time.h
	$(CC) $(CFLAGS) -c time.c	

clean:
	rm -f $(TARGET) $(OBJS)

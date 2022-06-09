#makefile /*EXECUTOR*/

TARGET = executor.out
CC = gcc
CFLAGS = -ansi -pedantic -g3 -Wall
CFLAGS += -fPIC
CFLAGS += -I../genericHeap
OBJS = executor_test.o executor.o task.o time.o
LIB_DIR = ../lib
LDFLAGS = -L$(LIB_DIR) -lDS
LDFLAGS += -rpath=$(CURDIR)/../lib

SRCS=$(OBJS:o=c)

lib: $(LIB_OBJS)

$(TARGET): executor_test.o
	$(CC) -o $(TARGET) executor_test.o $(LDFLAGS)
	
executor.o: executor.c executor.h task.h time.h
	$(CC) $(CFLAGS) executor.c
	
time.o: time.c time.h
	$(CC) $(CFLAGS) my_time.c	
	
task.o: task.c task.h
	$(CC) $(CFLAGS) task.c	

executor_test.o: executor_test.c executor.h task.h time.h 
	$(CC) $(CFLAGS) executor_test.c	
		
run: $(TARGET)
		./$(TARGET)
	
clean:
	rm -f $(TARGET) $(OBJS)

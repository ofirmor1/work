INC_DIR = ../../inc
INL_DIR = ../../inc/inl
SRC_DIR = ../../src

CC := $(CXX)
CXX := g++

CPPFLAGS = -I../inc -I../../inc -I./inc

WARNS = -Wall -Werror -pedantic

CXXFLAGS = -std=c++17 $(WARNS)
CXXFLAGS += -g
LDLIBS   =-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

OBJS   := app.o game.o ball.o brick.o paddle.o
TARGET := app

app.o : game.hpp ball.hpp brick.hpp paddle.hpp

all: $(TARGET)

$(TARGET): $(OBJS)

check: all
	@./$(TARGET) -v

valgrind: $(TARGET)
	valgrind --leak-check=full --track-origins=yes --log-file=logValgrind01.txt ./$(TARGET)
	valgrind --tool=helgrind --log-file=loghelgrind01.txt ./$(TARGET)
	valgrind --tool=drd --log-file=logdrd01.txt ./$(TARGET)

clean:
	$(RM) $(TARGET) $(OBJS) *.txt


.PHONY: all run clean valgrind
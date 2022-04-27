CC := $(CXX)
CXX := g++

WARNS = -Wall -Werror -pedantic

CXXFLAGS = -std=c++17 $(WARNS)
CXXFLAGS += -g

OBJS   := helicopter.o
TARGET := game

all: $(TARGET)

$(TARGET): $(OBJS)

check: all
	@./$(TARGET) -v

valgrind: $(TARGET)
	valgrind --leak-check=full --track-origins=yes --log-file=logValgrind01.txt ./$(TARGET)
	valgrind --tool=helgrind --log-file=loghelgrind01.txt ./$(TARGET)
	valgrind --tool=drd --log-file=logdrd01.txt ./$(TARGET)

clean:
	$(RM) $(TARGET) $(OBJS)


.PHONY: all run clean valgrind
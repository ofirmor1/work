CC := $(CXX)
CXX := g++

WARNS = -Wall -Werror -pedantic

CXXFLAGS = -std=c++03 $(WARNS)
CXXFLAGS += -g
LDLIBS   = -lpthread

OBJS   := utest.o quest.o
TARGET := utest

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
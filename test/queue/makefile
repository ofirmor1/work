CXX = g++
CC = $(CXX)

WARNINGS = -pedantic
WARNINGS += -Wall -Werror

DEBUG = -g3
CXX_STD = c++03

CXXFLAGS = $(WARNINGS) $(DEBUG) -std=$(CXX_STD)

CPPFLAGS = -I$(INC_DIR)

INC_DIR = ../../inc
SRC_DIR = ../../src

TARGET = utest
OBJS = utest.o

$(TARGET): $(OBJS)

utest.o: $(INC_DIR)/queue.hpp

check: $(TARGET)
	./$(TARGET) -v
	
vala:
	valgrind -q --leak-check=full ./${TARGET} -v
	gdb -q ${TARGET}
		
clean:
	@$(RM) $(TARGET) $(OBJS)
	
.PHONY: clean check (edited) 
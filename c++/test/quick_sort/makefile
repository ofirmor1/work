CXX = g++
CC = $(CXX)

WARNINGS = -pedantic
WARNINGS += -Wall -Werror

DEBUG = -g3
CXX_STD = c++03

CXXFLAGS = $(WARNINGS) $(DEBUG) -std=$(CXX_STD)

CPPFLAGS = -I$(INC_DIR)

INC_DIR = ../../inc
INC_SRC = ../../src

TARGET = utest
OBJS = utest.o

$(TARGET): $(OBJS)

# $(INC_DIR)/quick_sort.hpp: $(INC_DIR)/ball.hpp $(INC_DIR)/point.hpp
check: $(TARGET)
	./$(TARGET) -v
	
prod: CXXFLAGS += -02 -DNDEBUG
prod: $(TARGET)
	./$(TARGET) -v
	
debug:
	valgrind -q --leak-check=full ./${TARGET} -v
	gdb -q ${TARGET}
		
clean:
	@$(RM) $(TARGET) $(OBJS)
	
.PHONY: clean check (edited) 
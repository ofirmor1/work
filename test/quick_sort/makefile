CXX = g++
CC = $(CXX)

WARNINGS = -pedantic
WARNINGS += -Wall -Werror

DEBUG = -g3
CXX_STD = c++03

CXXFLAGS = $(WARNINGS) $(DEBUG) -std=$(CXX_STD)

CPPFLAGS = -I$(INC_DIR) -I$(INL_DIR)

INL_DIR = ../../inc/inl
INC_DIR = ../../inc
SRC_DIR = ../../src

TARGET = utest
OBJS = utest.o

$(TARGET): $(OBJS)

utest.o: $(INC_DIR)/quick_sort.hpp $(INL_DIR)/quick_sort.hxx
# $(INC_DIR)/quick_sort.hpp: $(INC_DIR)/ball.hpp $(INC_DIR)/point.hpp
check: $(TARGET)
	./$(TARGET) -v
	
vala:
	valgrind -q --leak-check=full ./${TARGET} -v
	gdb -q ${TARGET}
		
clean:
	@$(RM) $(TARGET) $(OBJS)
	
.PHONY: clean check (edited) 
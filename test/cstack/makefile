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
OBJS = utest.o $(SRC_DIR)/stack_cxx.o

$(TARGET): $(OBJS)

$(SRC_DIR)/stack_cxx.o: $(INC_DIR)/stack.hpp

utest.o: $(INC_DIR)/stack.hpp

check: $(TARGET)
	./$(TARGET) -v
	
clean:
	@$(RM) $(TARGET) $(OBJS)
	
.PHONY: clean check (edited) 
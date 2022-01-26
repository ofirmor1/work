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
OBJS = utest.o $(SRC_DIR)/Rational.o

$(TARGET): $(OBJS)

$(SRC_DIR)/Rational.o: $(INC_DIR)/Rational.hpp

utest.o: $(INC_DIR)/Rational.hpp

check: $(TARGET)
	./$(TARGET) -v

vala:
	valgrind -q --leak-check=full	
	
clean:
	@$(RM) $(TARGET) $(OBJS)
	
.PHONY: clean check (edited) 
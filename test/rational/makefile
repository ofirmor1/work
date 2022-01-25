CXX = g++
CC = $(CXX)

WARNINGS = -pedantic
WARNINGS += -Wall -Werror

DEBUG = -g3
CXX_STD = c++03

CXXFLAGS = $(WARNINGS) $(DEBUG) -std=$(CXX_STD)

CPPFLAGS = -I$(INC_DIR)

INC_DIR = ../../inc

TARGET = utest
OBJS = utest.o ../../src/Rational_cxx.o

$(TARGET): $(OBJS)

../../src/Rational_cxx.o: ../../inc/Rational.hpp

utest.o: ../../inc/Rational.hpp

check: $(TARGET)
	./$(TARGET) -v
	
clean:
	@$(RM) $(TARGET) $(OBJS)
	
.PHONY: clean check (edited) 

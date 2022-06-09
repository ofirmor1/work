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

check: $(TARGET)
	./$(TARGET) -v
	
$(TARGET): $(OBJS)
	
prod: CXXFLAGS += -02 -DNDEBUG
prod: $(TARGET)
	./$(TARGET) -v
	
debug:
	valgrind -q --leak-check=full ./${TARGET} -v
	gdb -q ${TARGET}
		
clean:
	@$(RM) $(TARGET) $(OBJS)
	
.PHONY: clean check (edited) 
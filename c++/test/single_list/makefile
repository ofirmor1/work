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

check: $(TARGET)
	./$(TARGET) -v

$(TARGET): $(OBJS)

utest.o: $(INC_DIR)/single_list.hpp $(INL_DIR)/single_list.hxx

vala:
	valgrind --log-file=V1.log./${TARGET} -v
	valgrind --log-file=V1.log --leak-check=full --track-origins=yes ./${TARGET}

clean:
	@$(RM) $(TARGET) $(OBJS)

.PHONY: clean check (edited)

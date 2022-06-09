CXX = g++
CC = $(CXX)

WARNINGS = -pedantic
# WARNINGS += -Wall -Werror

DEBUG = -g3
CXX_STD = c++03

CXXFLAGS = $(WARNINGS) $(DEBUG) -std=$(CXX_STD)

CPPFLAGS = -I$(INC_DIR) -I$(INL_DIR)

INL_DIR = ../../inc/inl
INC_DIR = ../../inc
SRC_DIR = ../../src

TARGET = utest
OBJS = utest.o $(SRC_DIR)/rational_cxx.o

$(TARGET): $(OBJS)

utest.o: $(INC_DIR)/rational.hpp

check: $(TARGET)
	./$(TARGET) -v

vala:
	valgrind --log-file=V1.log./${TARGET} -v
	valgrind --log-file=V1.log --leak-check=full --track-origins=yes ./${TARGET}
	
clean:
	@$(RM) $(TARGET) $(OBJS)
	
.PHONY: clean check (edited) 
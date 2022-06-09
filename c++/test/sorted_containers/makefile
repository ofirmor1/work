CXX = g++
CC = $(CXX)

WARNINGS = -pedantic
WARNINGS += -Wall -Werror

DEBUG = -g3
CXX_STD = c++03 #c++2a 

CXXFLAGS = $(WARNINGS) $(DEBUG) -std=$(CXX_STD)

CPPFLAGS = -I$(INC_DIR)

INC_DIR = ../../inc
INC_SRC = ../../src

TARGET = utest
OBJS = utest.o

VALGRIND = valgrind --log-file=V3.log --leak-check=full --track-origins=yes -s 

$(TARGET): $(OBJS)

check: $(TARGET)
	./$(TARGET) -v

#CXXFLAGS += -O2 -DNDEBUG
#prod: check
#	$(CXXFLAGS)
#	./$(TARGET) -v

debug: $(TARGET)
	$(VALGRIND) ./$(TARGET) -v

clean:
	@$(RM) $(TARGET) $(OBJS)

.PHONY: clean check debug

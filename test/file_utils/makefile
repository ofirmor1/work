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

check: $(TARGET) book.txt
	./$(TARGET) -v

warnpeace:
	wget https://raw.githubusercontent.com/mmcky/nyu-econ-370/master/notebooks/data/book-war-and-peace.txt

book.txt: warnpeace
	 cat book-war-and-peace.txt| tr -d '[:punct:]' > book.txt

prod: CXXFLAGS += -02 -DNDEBUG
prod: $(TARGET)
	./$(TARGET) -v
	
debug:
	valgrind -q --leak-check=full ./${TARGET} -v
	gdb -q ${TARGET}
		
clean:
	@$(RM) $(TARGET) $(OBJS) book*
	
.PHONY: clean check 
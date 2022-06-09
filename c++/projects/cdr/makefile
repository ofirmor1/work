INC_DIR = ../../inc
INL_DIR = ../../inc/inl
SRC_DIR = ../../src

CC := $(CXX)
CXX := g++

# CPPFLAGS = -I../inc -I../../inc -I./inc

WARNS = -Wall -Werror -pedantic

CXXFLAGS = -std=c++17 $(WARNS)
CXXFLAGS += -g
LDLIBS   = -lpthread

# tcp_server.o tcp_client.o tcp_net.o requests_handle.o

OBJS := utest.o mutex.o cdr_parse.o billing_aggregator.o operator_aggregator.o 
TARGET := utest

# cdr_parse.o : ../inc/mutex.o
# mutex.o: mutex.hpp 

all: $(TARGET)

$(TARGET): $(OBJS)

check: all
	@./$(TARGET) -v

valgrind: $(TARGET)
	valgrind --leak-check=full --track-origins=yes --log-file=logValgrind01.txt ./$(TARGET)
	valgrind --tool=helgrind --log-file=loghelgrind01.txt ./$(TARGET)
	valgrind --tool=drd --log-file=logdrd01.txt ./$(TARGET)

clean:
	$(RM) $(TARGET) $(OBJS)

.PHONY: all run clean valgrind
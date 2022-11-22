SRC_DIR = ../../src
TEST_DIR  = ../../test/tcp_client
INC_DIR = ../../inc

CXX = g++
CC = $(CXX)

WARNINGS = -pedantic
WARNINGS += -Wall -Werror

DEBUG = -g3
CXX_STD = c++17

LDLIBS   = -lpthread

CXXFLAGS = $(WARNINGS) $(DEBUG) -std=$(CXX_STD) $(LDLIBS)


CPPFLAGS = -I$(INC_DIR)

TARGET = utest
OBJS = $(SRC_DIR)/protocol.o $(SRC_DIR)/server.o  $(SRC_DIR)/log.o  $(SRC_DIR)/event_router.o  $(SRC_DIR)/server_manager.o 
OBJS += $(SRC_DIR)/subscribers.o  $(SRC_DIR)/controller_agent.o $(SRC_DIR)/device.o $(SRC_DIR)/temperature_controller.o
OBJS += $(SRC_DIR)/light_controller.o  $(SRC_DIR)/fire_controller.o  $(SRC_DIR)/controllers_loader.o
OBJS += $(SRC_DIR)/alarm_controller.o $(SRC_DIR)/client.o $(SRC_DIR)/utils.o 

$(TARGET):$(OBJS)


check: $(TARGET)
	./$(TARGET) -v

prod: CXXFLAGS += -O2 -DNDEBUG
prod: $(TARGET)
	./$(TARGET) -v

clean:
	@$(RM) $(TARGET) $(OBJS)

.PHONY: check clean

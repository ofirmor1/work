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
OBJS = $(SRC_DIR)/protocol.o $(SRC_DIR)/client.o $(SRC_DIR)/temperature_sensor.o $(SRC_DIR)/light_sensor.o $(SRC_DIR)/fire_sensor.o $(SRC_DIR)/sensor_agent.o 
OBJS += $(SRC_DIR)/utils.o $(SRC_DIR)/controller_agent.o $(SRC_DIR)/device.o $(SRC_DIR)/sensors_loader.o $(SRC_DIR)/sensors_manager.o


$(TARGET):$(OBJS)

protocol.o: protocol.hpp 
client.o: 
temperature_sensor.o: $(INC_DIR)/temperature_sensor.hpp
sensor_agent.o: $(INC_DIR)/sensor_agent.hpp
utils.o: $(INC_DIR)/utils.hpp
controller_agent.o: $(INC_DIR)/controller_agent.hpp $(INC_DIR)/event.hpp $(INC_DIR)/device.hpp





check: $(TARGET)
	./$(TARGET) -v

prod: CXXFLAGS += -O2 -DNDEBUG
prod: $(TARGET)
	./$(TARGET) -v

clean:
	@$(RM) $(TARGET) $(OBJS)

.PHONY: check clean

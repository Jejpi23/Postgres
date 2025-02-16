CXX = g++

CXXFLAGS = -std=c++11 -Wall -Wextra -Idatabase

LDLIBS = -lpq

TARGET = app

SRC_DIR = src
DB_DIR = database

SRCS = $(SRC_DIR)/main.cpp $(DB_DIR)/database.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDLIBS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(DB_DIR)/%.o: $(DB_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
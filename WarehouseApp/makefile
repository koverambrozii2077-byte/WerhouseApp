CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g
TARGET = warehouse.exe

SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del /Q src\*.o $(TARGET) 2>nul

run: $(TARGET)
	$(TARGET)

.PHONY: all clean run
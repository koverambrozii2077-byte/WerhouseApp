CXX = clang++
CXXFLAGS = -std=c++17 -stdlib=libc++ -Wall -Wextra -g
TARGET = warehouse
SRCS = src/main.cpp src/Product.cpp src/Warehouse.cpp src/FileIO.cpp src/Menu.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

rebuild: clean all

.PHONY: all clean run rebuild
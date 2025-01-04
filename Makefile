# Compiler and Flags
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -g

# Project Files
SRCS = main.cpp WorkerPool.cpp
HEADERS = WorkerPool.h
OBJS = $(SRCS:.cpp=.o)

# Output Binary
TARGET = main

# Default Target
all: $(TARGET)

# Linking
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilation
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean Build Files
clean:
	rm -f $(OBJS) $(TARGET)

# Rebuild
rebuild: clean all


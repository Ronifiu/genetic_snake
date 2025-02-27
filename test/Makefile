# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
LDFLAGS = -lraylib

# Source files
SRC = main.cpp neural.cpp genetic.cpp game.cpp agent.cpp
OBJ = $(SRC:.cpp=.o)

# Executable name
TARGET = SnakeGA

# Default rule: Build the executable
all: $(TARGET)

# Link the final executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)

# Compile each source file into an object file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up compiled files
clean:
	rm -f $(OBJ) $(TARGET)

# Define the compiler and flags
CXX = g++
CXXFLAGS = -I header -std=c++11

# Define target executable and source files
TARGET = search
SRC = src/main.cpp src/Node.cpp src/problem.cpp src/PuzzleSolver.cpp

# Rule to build the target executable
$(TARGET): $(SRC) | build
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# Create the build directory if it doesn't exist
build:
	mkdir -p build

# Clean up the build directory
clean:
	rm -f $(TARGET)

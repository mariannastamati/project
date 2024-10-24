# Compiler and flags
CXX = g++
CXXFLAGS = -g3 -O3 -Wall -std=c++11

# Source files
SRCS = $(wildcard *.cpp)

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
TARGET = executable

# Command line arguments for the executable program
ARGS = 

# Command line arguments for Valgrind
VALGRIND_ARGS = --track-origins=yes --leak-check=full --trace-children=yes

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to build object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the executable program
run: $(TARGET)
	./$(TARGET) $(ARGS) >> output.txt

# Run the executable program under Valgrind
val: $(TARGET)
	valgrind $(VALGRIND_ARGS) ./$(TARGET) $(ARGS) >> output.txt

# Clean the build files
clean:
	rm -f $(OBJS) $(TARGET)
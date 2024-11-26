# Compiler and flags
CXX = g++
CXXFLAGS = -g3 -O3 -Wall -std=c++17

# Conditional compilation to run either the program or unit testing
ifeq ($(test),yes)
	SRCS = $(subst main.cpp,,$(wildcard *.cpp))
else
	SRCS = $(subst test.cpp,,$(wildcard *.cpp))
endif

# Object file
OBJS = $(SRCS:.cpp=.o)

# Executable name
TARGET = executable

# Command line arguments for the executable program
ifeq ($(test),yes)
	ARGS =
else
	ARGS = ../datasets2/dummy-data.bin ../datasets2/dummy-queries.bin 1.2 10 70 12 50 60 8 5
endif

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
	./$(TARGET) $(ARGS) 

# Run the executable program and save output
save: $(TARGET)
	./$(TARGET) $(ARGS) >> output.txt

# Run the executable program under Valgrind
val: $(TARGET)
	valgrind $(VALGRIND_ARGS) ./$(TARGET) $(ARGS)

# Clean the build files
clean:
	rm -f $(OBJS) $(TARGET)

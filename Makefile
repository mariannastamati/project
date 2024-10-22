# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++11

# Source files
SRCS = main.cpp graph.cpp readfiles.cpp VamanaIndexing.cpp robustPrune.cpp printGraph.cpp GreedySearch.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
TARGET = executable

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to build object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean the build files
clean:
	rm -f $(OBJS) $(TARGET)

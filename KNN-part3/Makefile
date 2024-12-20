# Compiler and flags
CXX = g++
CXXFLAGS = -g3 -O3 -Wall -std=c++17

# Source files
SRCS = $(wildcard *.cpp)
MAIN_SRCS = $(filter-out test.cpp,$(SRCS))
TEST_SRCS = $(filter-out main.cpp,$(SRCS))

# Object files
MAIN_OBJS = $(MAIN_SRCS:.cpp=.o)
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

# Executable names
MAIN_EXECUTABLE = executable
TEST_EXECUTABLE = test_executable

# Default values for variables (command-line arguments)
dataset ?= ../datasets2/dummy-data.bin
queries ?= ../datasets2/dummy-queries.bin
a ?= 1.2
L ?= 100
R ?= 10
k ?= 50
L_small ?= 80
R_small ?= 13
R_stitched ?= 10
groundtruth ?= groundtruth.txt
graph ?= G_stitched.bin

# Command line arguments for Valgrind
VALGRIND_ARGS = --track-origins=yes --leak-check=full --trace-children=yes

# Rule to build the main executable
$(MAIN_EXECUTABLE): $(MAIN_OBJS)
	$(CXX) $(CXXFLAGS) -o $(MAIN_EXECUTABLE) $(MAIN_OBJS)

# Rule to build the test executable
$(TEST_EXECUTABLE): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $(TEST_EXECUTABLE) $(TEST_OBJS)

# Rule to build object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the main executable for different phases
run-groundtruth: $(MAIN_EXECUTABLE) ## Run groundtruth phase
	./$(MAIN_EXECUTABLE) groundtruth $(dataset) $(queries)

run-filtered: $(MAIN_EXECUTABLE) ## Run filtered vamana phase
	./$(MAIN_EXECUTABLE) filtered $(dataset) $(a) $(L) $(R)

run-stitched: $(MAIN_EXECUTABLE) ## Run stitched vamana phase
	./$(MAIN_EXECUTABLE) stitched $(dataset) $(a) $(L_small) $(R_small) $(R_stitched)

run-greedy: $(MAIN_EXECUTABLE) ## Run greedy phase
	./$(MAIN_EXECUTABLE) greedy $(dataset) $(queries) $(groundtruth) $(L) $(k) $(graph)

# Run all phases
run-all: run-groundtruth run-filtered run-stitched run-greedy ## Run all phases

# Run greedy phase and save output
save-greedy: $(MAIN_EXECUTABLE) ## Run greedy phase and save output (recall) to file
	./$(MAIN_EXECUTABLE) greedy $(dataset) $(queries) $(groundtruth) $(L) $(k) $(graph) >> output.txt

# Run each phase with Valgrind
val-groundtruth: $(MAIN_EXECUTABLE) ## Run groundtruth phase under Valgrind
	valgrind $(VALGRIND_ARGS) ./$(MAIN_EXECUTABLE) groundtruth $(dataset) $(queries)

val-filtered: $(MAIN_EXECUTABLE) ## Run filtered vamana phase under Valgrind
	valgrind $(VALGRIND_ARGS) ./$(MAIN_EXECUTABLE) filtered $(dataset) $(a) $(L) $(R)

val-stitched: $(MAIN_EXECUTABLE) ## Run stitched vamana phase under Valgrind
	valgrind $(VALGRIND_ARGS) ./$(MAIN_EXECUTABLE) stitched $(dataset) $(a) $(L_small) $(R_small) $(R_stitched)

val-greedy: $(MAIN_EXECUTABLE) ## Run greedy phase under Valgrind
	valgrind $(VALGRIND_ARGS) ./$(MAIN_EXECUTABLE) greedy $(dataset) $(queries) $(groundtruth) $(L) $(k) $(graph)

# Run all phases with Valgrind
val-all: val-groundtruth val-filtered val-stitched val-greedy ## Run all phases under Valgrind

# Run the test executable
run-test: $(TEST_EXECUTABLE) ## Run tests
	./$(TEST_EXECUTABLE)

# Run the test executable under Valgrind
val-test: $(TEST_EXECUTABLE) ## Run tests under Valgrind
	valgrind $(VALGRIND_ARGS) ./$(TEST_EXECUTABLE)

# Clean the build files
clean: ## Remove all generated files
	rm -f $(MAIN_OBJS) $(TEST_OBJS) $(MAIN_EXECUTABLE) $(TEST_EXECUTABLE)

# Help target
help: ## Show available commands
	@echo "Available commands:"
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "  %-20s %s\n", $$1, $$2}'
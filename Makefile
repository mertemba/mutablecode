# compile script for gcc using c++11 standard
# just run "make" or "make run"

CC = gcc
CXX = g++
CPPFLAGS = -g -I./include -I./src -std=c++11 -fopenmp -Wall -O2
LDFLAGS = -g
LDLIBS = -lstdc++ -lgomp -lz

HEADERS = include/Interpreter.hpp include/Program.hpp include/Tape.hpp include/Char.hpp include/ProgramLoader.hpp include/Mutator.hpp include/Random.hpp include/Evaluator.hpp include/Compression.hpp include/EntropyEvaluator.hpp
SRCS = src/main.cpp src/Interpreter.cpp src/Program.cpp src/Char.cpp src/Mutator.cpp
BUILDDIR = build
OBJS_TMP = $(subst .cpp,.o,$(SRCS))
OBJS = $(subst src/,$(BUILDDIR)/,$(OBJS_TMP))

BIN = $(BUILDDIR)/mutablecode

all: $(BIN)

run: all
	$(BIN)

debugrun: all
	gdb $(BIN) -ex run -ex quit

$(BIN): $(BUILDDIR)/ $(OBJS)
	$(CXX) $(LDFLAGS) -o $(BIN) $(OBJS) $(LDLIBS)

$(BUILDDIR)/%.o: src/%.cpp $(HEADERS)
	$(CXX) -c $(CPPFLAGS) $(CFLAGS) $< -o $@

clean:
	$(RM) $(OBJS)

dist-clean: clean
	rm -f $(BIN)
	rm -rf $(BUILDDIR)

$(BUILDDIR)/:
	mkdir -p $(BUILDDIR)

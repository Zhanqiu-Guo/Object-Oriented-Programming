# Makefile
# Build rules for EECS 280 Lab 5 poker exercise

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = --std=c++11 -Wall -Werror -pedantic -g

# Run a regression test
test: poker_tests.exe
	./poker_tests.exe

poker_tests.exe: poker_tests.cpp poker.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

# Disable built-in Makefile rules
.SUFFIXES:

clean:
	rm -rvf *.exe *.out.txt *.out.ppm *.dSYM *.stackdump
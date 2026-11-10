CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -O2

SRC := $(wildcard src/*.cpp)
HDR := $(wildcard src/*.hpp)

crypto: $(SRC) $(HDR)
	$(CXX) $(CXXFLAGS) -o $@ $(SRC)

test: crypto
	./tests/run_tests.sh ./crypto

clean:
	rm -f crypto

.PHONY: test clean

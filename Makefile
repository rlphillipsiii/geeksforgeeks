CXX=g++
CXXFLAGS=-std=c++11 -g -DLOCAL

all: src/%

%: src/%.cpp
	$(CXX) $(CXXFLAGS) -DINPUT_FILE='"input/$@.txt"' -o binaries/$@ $<

clean:
	rm -rf binaries/* 2> /dev/null

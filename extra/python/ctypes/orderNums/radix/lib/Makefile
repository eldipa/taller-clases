all: libradix.so

libradix.so: Radix.cpp
	$(CXX) -std=c++11 -fPIC -shared -o $@ $?

test: Radix.cpp
	$(CXX) -std=c++11 -o $@ $?

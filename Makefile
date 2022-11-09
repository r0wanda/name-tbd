main: main.cpp $(wildcard *.cpp) $(wildcard *.hpp)
	g++ -o main main.cpp fileio.cpp util.cpp Observer.cpp Subject.cpp -lcurses -std=c++17 -g

test: test.cpp fileio.hpp fileio.cpp dbg.hpp util.hpp
	g++ -o test test.cpp fileio.cpp util.cpp Observer.cpp Subject.cpp -lcurses -std=c++17
CXXFLAGS=-std=c++11 -O2


all:
		python pyfont.py
		$(CXX) $(CXXFLAGS) pyfont.cpp main.cpp -o font

clean:
		rm font

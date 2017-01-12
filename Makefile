CXXFLAGS=-std=c++11 -O2


all:
		$(CXX) $(CXXFLAGS) pyfont.cpp main.cpp -o font

font: FORCE
		python pyfont.py font.png myTestFont

FORCE:

clean:
		rm font

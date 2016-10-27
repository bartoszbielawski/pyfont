CXXFLAGS=-std=c++11


all:
		python pyfont.py
		$(CXX) $(CXXFLAGS) main.cpp -o font

clean:
		rm font
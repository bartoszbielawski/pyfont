CXXFLAGS=-std=c++11 -O2

OBJS=main.o pyfont.o SDD.o
TARGET=sdd

all: $(OBJS)
		$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

%.o: %.cpp
		$(CXX) $(CXXFLAGS) -c $< -o $@

font: FORCE
		python pyfont.py font.png myTestFont

FORCE:

clean:
		rm -f $(OBJS) $(TARGET)

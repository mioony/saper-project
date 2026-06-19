CXX = g++
CXXFLAGS = -std=c++14 -Wall
LIBS = -lallegro -lallegro_main -lallegro_primitives -lallegro_font -lallegro_image -lallegro_ttf
TARGET = saper_project
OBJS = main.o plansza.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LIBS)

main.o: main.cpp plansza.h
	$(CXX) $(CXXFLAGS) -c main.cpp

plansza.o: plansza.cpp plansza.h
	$(CXX) $(CXXFLAGS) -c plansza.cpp

clean:
	rm -f *.o $(TARGET)
CXX = g++
CXXFLAGS = --std=c++11
GTK_INCLUDE = `pkg-config gtkmm-3.0 --cflags --libs`
SDL_INCLUDE = -lSDL2

all: compile

debug: CXXFLAGS += -g
debug: clean compile

compile: chip8.o emulator.o display.o debug_window.o utilities.o
	$(CXX) $(CXXFLAGS) -o chip8 chip8.o emulator.o display.o debug_window.o utilities.o $(SDL_INCLUDE) $(GTK_INCLUDE)

chip8.o: chip8.cpp
	$(CXX) $(CXXFLAGS) -c chip8.cpp $(SDL_INCLUDE) $(GTK_INCLUDE)

emulator.o: emulator.cpp
	$(CXX) $(CXXFLAGS) -c emulator.cpp

display.o: display.cpp
	$(CXX) $(CXXFLAGS) -c display.cpp $(SDL_INCLUDE)

debug_window.o: debug_window.cpp
	$(CXX) $(CXXFLAGS) -c debug_window.cpp $(SDL_INCLUDE) $(GTK_INCLUDE)

utilities.o: utilities.cpp
	$(CXX) $(CXXFLAGS) -c utilities.cpp

clean:
	rm -f chip8 chip8.exe *.o
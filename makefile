CXX = g++
CXXFLAGS = --std=c++11
GTK_INCLUDE = `pkg-config gtkmm-3.0 --cflags --libs`
SDL_INCLUDE = -lSDL2 -lSDL2_mixer
SOURCE_DIR = src
BUILD_DIR = build

all: compile

debug: CXXFLAGS += -g
debug: clean compile

compile: dir chip8 emulator display debug_window utilities
	$(CXX) $(CXXFLAGS) -o chip8 \
	$(BUILD_DIR)/chip8.o \
	$(BUILD_DIR)/emulator.o \
	$(BUILD_DIR)/display.o \
	$(BUILD_DIR)/debug_window.o \
	$(BUILD_DIR)/utilities.o \
	$(SDL_INCLUDE) $(GTK_INCLUDE)

dir:
	if [ ! -d "build/" ]; then mkdir build; fi

chip8: $(SOURCE_DIR)/chip8.cpp
	$(CXX) $(CXXFLAGS) -c $(SOURCE_DIR)/chip8.cpp -o $(BUILD_DIR)/chip8.o $(SDL_INCLUDE) $(GTK_INCLUDE)

emulator: $(SOURCE_DIR)/emulator.cpp
	$(CXX) $(CXXFLAGS) -c $(SOURCE_DIR)/emulator.cpp -o $(BUILD_DIR)/emulator.o

display: $(SOURCE_DIR)/display.cpp
	$(CXX) $(CXXFLAGS) -c $(SOURCE_DIR)/display.cpp  -o $(BUILD_DIR)/display.o $(SDL_INCLUDE)

debug_window: $(SOURCE_DIR)/debug_window.cpp
	$(CXX) $(CXXFLAGS) -c $(SOURCE_DIR)/debug_window.cpp  -o $(BUILD_DIR)/debug_window.o $(SDL_INCLUDE) $(GTK_INCLUDE)

utilities: $(SOURCE_DIR)/utilities.cpp
	$(CXX) $(CXXFLAGS) -c $(SOURCE_DIR)/utilities.cpp -o $(BUILD_DIR)/utilities.o

clean:
	rm -rf build/ chip8 chip8.exe *.o
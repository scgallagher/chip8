g++ --std=c++11 chip8.cpp emulator.cpp debug_window.cpp utilities.cpp -o chip8 -lSDL2 `pkg-config gtkmm-3.0 --cflags --libs`

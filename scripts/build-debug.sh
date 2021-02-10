g++ chip8.cpp emulator.cpp display.cpp debug_window.cpp utilities.cpp -o chip8 -g -lSDL2 `pkg-config gtkmm-3.0 --cflags --libs`

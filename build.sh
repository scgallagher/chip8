g++ --std=c++11 chip8.cpp emulator.cpp display.cpp utilities.cpp -o chip8 `pkg-config gtkmm-3.0 --cflags --libs`

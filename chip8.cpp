#include <iostream>
#include "emulator.h"

Emulator emulator;

void drawGraphics(){
    std::cout << "Drawing graphics\n";

    for (int y = 0; y < 32; y++) {
        std::cout << "|";
        for (int x = 0; x < 64; x++) {
            if (emulator.gfx[x + y * 64] == 1) {
                std::cout << "*";
            }
            else {
                std::cout << " ";
            }
        }
        std::cout << "|\n";
    }
    emulator.drawFlag = false;
}

int main(int argc, char **argv) {
    initializeGraphics();
    initializeInput();

    emulator.initialize();
    emulator.loadProgram("tetris");

    for(int i = 0; i < 1; i++) {
        emulator.cycle();

        if(emulator.drawFlag) {
            drawGraphics();
        }

        emulator.setKeys();
    }
    return 0;
}
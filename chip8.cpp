#include <iostream>
#include <gtkmm/application.h>
#include <thread>
#include "emulator.h"
#include "display.h"

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

void launchDisplay(int argc, char **argv) {
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

  Display display;

  app->run(display);
}

void Display::on_button_clicked() {
    emulator.cycle();

    if(emulator.drawFlag) {
        //drawGraphics();
    }

    emulator.setKeys();
}

int main(int argc, char **argv) {
    initializeGraphics();
    initializeInput();

    emulator.initialize();
    emulator.loadProgram("tetris");

	// std::thread displayThread(launchDisplay, argc, argv);
    
	// displayThread.join();
    emulator.cycle();

	return 0;
}

#include <iostream>
#include <sstream>
#include <gtkmm/application.h>
#include <thread>
#include "emulator.h"
#include "display.h"
#include "utilities.h"

Emulator emulator;

Utilities utilities;

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
    display.setProgramCounterLabel(utilities.hexToString(emulator.pc));
    display.setIndexLabel(utilities.hexToString(emulator.I));
    display.setStackPointerLabel(utilities.hexToString(emulator.sp));
    display.setDelayTimerLabel(utilities.hexToString(emulator.delay_timer));
    display.setSoundTimerLabel(utilities.hexToString(emulator.sound_timer));
    display.setStackLabels(emulator.stack);
    display.setVLabels(emulator.V);

    app->run(display);
}

void Display::setStackLabels(unsigned short *stack) {
    for (int i = 0; i < 16; i++) {
        Gtk::Label *label = stackLabels[i];
        std::stringstream ss;
        ss << "s[" << std::hex << i << "]: " << utilities.hexToString(stack[i]);
        label->set_text(ss.str());
    }
}

void Display::setVLabels(unsigned char *V) {
    for (int i = 0; i < 16; i++) {
        Gtk::Label *label = vLabels[i];
        std::stringstream ss;
        ss << "V[" << std::hex << i << "]: " << utilities.hexToString(V[i]);
        label->set_text(ss.str());
    }
}

void Display::on_button_clicked() {
    emulator.cycle();

    setProgramCounterLabel(utilities.hexToString(emulator.pc));
    setIndexLabel(utilities.hexToString(emulator.I));
    setStackPointerLabel(utilities.hexToString(emulator.sp));
    setDelayTimerLabel(utilities.hexToString(emulator.delay_timer));
    setSoundTimerLabel(utilities.hexToString(emulator.sound_timer));
    setStackLabels(emulator.stack);
    setVLabels(emulator.V);

    if(emulator.drawFlag) {
        //drawGraphics();
    }

    emulator.setKeys();
}

int main(int argc, char **argv) {
    initializeGraphics();
    initializeInput();

    emulator.initialize();

    std::string romFilePath = "roms/TETRIS";
    if (argc > 1) {
        romFilePath = argv[1];
    }
    emulator.loadProgram(romFilePath);

	std::thread displayThread(launchDisplay, argc, argv);
    
	displayThread.join();
    // while(true) {
    //     try {
    //         emulator.cycle();
    //     }
    //     catch (std:: string opcode) {
    //         std::cout << "ERROR: Unknown opcode " << opcode << std::endl;
    //         return 1;
    //     }
    // }

	return 0;
}

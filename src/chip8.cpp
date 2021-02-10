#include <iostream>
#include <sstream>
#include <gtkmm/application.h>
#include <thread>
#include "emulator.h"
#include "display.h"
#include "debug_window.h"
#include "utilities.h"
#include <SDL2/SDL.h>

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

void launchDebugWindow(int argc, char **argv) {
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

    DebugWindow debugWindow;
    debugWindow.setProgramCounterLabel(utilities.hexToString(emulator.pc));
    debugWindow.setIndexLabel(utilities.hexToString(emulator.I));
    debugWindow.setStackPointerLabel(utilities.hexToString(emulator.sp));
    debugWindow.setDelayTimerLabel(utilities.hexToString(emulator.delay_timer));
    debugWindow.setSoundTimerLabel(utilities.hexToString(emulator.sound_timer));
    debugWindow.setStackLabels(emulator.stack);
    debugWindow.setVLabels(emulator.V);

    app->run(debugWindow);
}

void DebugWindow::setStackLabels(unsigned short *stack) {
    for (int i = 0; i < 16; i++) {
        Gtk::Label *label = stackLabels[i];
        std::stringstream ss;
        ss << "s[" << std::hex << i << "]: " << utilities.hexToString(stack[i]);
        label->set_text(ss.str());
    }
}

void DebugWindow::setVLabels(unsigned char *V) {
    for (int i = 0; i < 16; i++) {
        Gtk::Label *label = vLabels[i];
        std::stringstream ss;
        ss << "V[" << std::hex << i << "]: " << utilities.hexToString(V[i]);
        label->set_text(ss.str());
    }
}

void DebugWindow::on_button_clicked() {
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

unsigned char* getBlankScreen() {
    int bufferSize = 64 * 32;
    unsigned char* buffer = new unsigned char[bufferSize];
    for (int i = 0; i < bufferSize; i++) {
        buffer[i] = 0x0;
    }
    return buffer;
}

int main(int argc, char **argv) {
    initializeGraphics();
    initializeInput();

    emulator.initialize();

    std::string romFilePath = "roms/IBM_LOGO";
    if (argc > 1) {
        romFilePath = argv[1];
    }
    emulator.loadProgram(romFilePath);

	// std::thread debugWindowThread(launchDebugWindow, argc, argv);
    
	// debugWindowThread.join();

    Display* display = new Display();
    try {
        display->initialize();
    } // TODO: make this code throw a class instead of a string
    catch (std::string error) {
        std::cout << "ERROR: Unable to initialize display: " + error << std::endl;
    }

    bool quit = false;
    SDL_Event* event = new SDL_Event();
    while (!quit) {
        while (SDL_PollEvent(event) != 0) {
            if (event->type == SDL_QUIT) {
                quit = true;
            }
        }

        try {
            emulator.cycle();
            display->updateDisplay(emulator.gfx);
        }
        catch (std:: string opcode) {
            std::cout << "ERROR: Unknown opcode " << opcode << std::endl;
            return 1;
        }
    }

	return 0;
}

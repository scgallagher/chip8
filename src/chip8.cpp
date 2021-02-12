#include <iostream>
#include <sstream>
#include <gtkmm/application.h>
#include <thread>
#include "emulator.h"
#include "display.h"
#include "debug_window.h"
#include "utilities.h"
#include <SDL2/SDL.h>
#include <stdlib.h>

Emulator emulator;

Utilities utilities;

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

    emulator.setKeys();
}

Display* initializeDisplay() {
    try {
        Display* display = new Display();
        display->initialize();

        return display;
    } 
    catch (std::string error) {
        std::cout << "ERROR: Unable to initialize display: " + error << std::endl;
        exit(1);
    }
}

bool pollForQuitEvent(SDL_Event* event) {
    while (SDL_PollEvent(event) != 0) {
        if (event->type == SDL_QUIT) {
            return true;
        }
        else if (event->type == SDL_KEYDOWN) {
            int keyPressed = event->key.keysym.sym;
            
            auto keyCode = emulator.keyMap.find(keyPressed);
            if (keyCode != emulator.keyMap.end()) {
                emulator.isKeyPressed = true;
                emulator.keyCodePressed = keyCode->first;
            }
            else {
                std::cout << "WARNING: Key press not recognized: " << keyPressed << std::endl;
            }
        }
    }
    return false;
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

	// // std::thread debugWindowThread(launchDebugWindow, argc, argv);
    
	// // debugWindowThread.join();

    Display* display = initializeDisplay();

    bool quit = false;
    SDL_Event* event = new SDL_Event();
    while (!quit) {
        try {
            emulator.cycle();
            display->updateDisplay(emulator.gfx);
        }
        catch (std:: string opcode) {
            std::cout << "ERROR: Unknown opcode " << opcode << std::endl;
            return 1;
        }

        quit = pollForQuitEvent(event);
    }

	return 0;
}

#include <iostream>
#include <sstream>
#include <gtkmm/application.h>
#include <thread>
#include "emulator.h"
#include "display.h"
#include "debug_window.h"
#include "utilities.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdlib.h>

Emulator emulator;

Utilities utilities;

Display* display;

SDL_Event* event;

void launchDebugWindow(int argc, char **argv) {
    auto app = Gtk::Application::create(argc, argv, "chip8");

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
    try {
        emulator.cycle();

        setProgramCounterLabel(utilities.hexToString(emulator.pc));
        setIndexLabel(utilities.hexToString(emulator.I));
        setStackPointerLabel(utilities.hexToString(emulator.sp));
        setDelayTimerLabel(utilities.hexToString(emulator.delay_timer));
        setSoundTimerLabel(utilities.hexToString(emulator.sound_timer));
        setStackLabels(emulator.stack);
        setVLabels(emulator.V);

        display->updateDisplay(emulator.gfx);

        if (emulator.isSoundTimerActive()) {
            Mix_PlayChannel(-1, display->beep, 0);
        }
    }
    catch (std:: string opcode) {
        std::cout << "ERROR: Unknown opcode " << opcode << std::endl;
        exit(1);
    }
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

void processKeyDown(SDL_Event* event) {
    int keyPressed = event->key.keysym.sym;
            
    auto keyCode = emulator.keyMap.find(keyPressed);
    if (keyCode != emulator.keyMap.end()) {
        emulator.pressKey(keyCode->second);
    }
    else {
        std::cout << "WARNING: Key press not recognized: " << keyPressed << std::endl;
    }
}

bool pollForQuitEvent() {
    while (SDL_PollEvent(event) != 0) {
        if (event->type == SDL_QUIT) {
            return true;
        }
        else if (event->type == SDL_KEYDOWN) {
            processKeyDown(event);
        }
    }
    return false;
}

void runEmulator() {
    bool quit = false;
    while (!quit) {
        try {
            emulator.cycle();
            display->updateDisplay(emulator.gfx);

            if (emulator.isSoundTimerActive()) {
                Mix_PlayChannel(-1, display->beep, 0);
            }
        }
        catch (std:: string opcode) {
            std::cout << "ERROR: Unknown opcode " << opcode << std::endl;
            exit(1);
        }

        quit = pollForQuitEvent();
    }
}

int main(int argc, char **argv) {
    bool isDebugMode = false;

    initializeGraphics();
    initializeInput();

    emulator.initialize();

    display = initializeDisplay();
    event = new SDL_Event();

    std::string romFilePath = "roms/TETRIS";
    if (argc > 1) {
        romFilePath = argv[1];
    }
    emulator.loadProgram(romFilePath);

    if (isDebugMode) {
        std::thread debugWindowThread(launchDebugWindow, argc, argv);
	    debugWindowThread.join();
    }
    else {
        runEmulator();
    }

	return 0;
}

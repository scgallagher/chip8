#include <iostream>
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
  stack0Label.set_text("s[0]: " + utilities.hexToString(stack[0]));
  stack1Label.set_text("s[1]: " + utilities.hexToString(stack[1]));
  stack2Label.set_text("s[2]: " + utilities.hexToString(stack[2]));
  stack3Label.set_text("s[3]: " + utilities.hexToString(stack[3]));
  stack4Label.set_text("s[4]: " + utilities.hexToString(stack[4]));
  stack5Label.set_text("s[5]: " + utilities.hexToString(stack[5]));
  stack6Label.set_text("s[6]: " + utilities.hexToString(stack[6]));
  stack7Label.set_text("s[7]: " + utilities.hexToString(stack[7]));
  stack8Label.set_text("s[8]: " + utilities.hexToString(stack[8]));
  stack9Label.set_text("s[9]: " + utilities.hexToString(stack[9]));
  stack10Label.set_text("s[A]: " + utilities.hexToString(stack[10]));
  stack11Label.set_text("s[B]: " + utilities.hexToString(stack[11]));
  stack12Label.set_text("s[C]: " + utilities.hexToString(stack[12]));
  stack13Label.set_text("s[D]: " + utilities.hexToString(stack[13]));
  stack14Label.set_text("s[E]: " + utilities.hexToString(stack[14]));
  stack15Label.set_text("s[F]: " + utilities.hexToString(stack[15]));
}

void Display::setVLabels(unsigned char *V) {
  v0Label.set_text("V[0]: " + utilities.hexToString(V[0]));
  v1Label.set_text("V[1]: " + utilities.hexToString(V[1]));
  v2Label.set_text("V[2]: " + utilities.hexToString(V[2]));
  v3Label.set_text("V[3]: " + utilities.hexToString(V[3]));
  v4Label.set_text("V[4]: " + utilities.hexToString(V[4]));
  v5Label.set_text("V[5]: " + utilities.hexToString(V[5]));
  v6Label.set_text("V[6]: " + utilities.hexToString(V[6]));
  v7Label.set_text("V[7]: " + utilities.hexToString(V[7]));
  v8Label.set_text("V[8]: " + utilities.hexToString(V[8]));
  v9Label.set_text("V[9]: " + utilities.hexToString(V[9]));
  v10Label.set_text("V[A]: " + utilities.hexToString(V[10]));
  v11Label.set_text("V[B]: " + utilities.hexToString(V[11]));
  v12Label.set_text("V[C]: " + utilities.hexToString(V[12]));
  v13Label.set_text("V[D]: " + utilities.hexToString(V[13]));
  v14Label.set_text("V[E]: " + utilities.hexToString(V[14]));
  v15Label.set_text("V[F]: " + utilities.hexToString(V[15]));
}

void Display::on_button_clicked() {
    emulator.cycle();

    //programCounterLabel.set_text("pc: " + utilities.hexToString(emulator.pc));
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

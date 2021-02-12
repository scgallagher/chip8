#ifndef EMULATOR_H
#define EMULATOR_H

#include <string>
#include "utilities.h"
#include <map>
#include <SDL2/SDL.h>

void initializeGraphics();

void initializeInput();

class Emulator {
    public:
        Emulator();
        void initialize();
        void loadProgram(std::string);
        void cycle();
        void setKeys();

        int drawFlag;

        // opcodes are 2 bytes
        unsigned short opcode;

        // memory is stored in 8-bit increments
        unsigned char memory[4096];

        // General purpose 8-bit registers
        unsigned char V[16];

        // Index register & program counter
        unsigned short I;
        unsigned short pc;

        // Black and white graphics (2048 pixels or 64x32)
        const static unsigned char DISPLAY_WIDTH = 64;
        const static unsigned char DISPLAY_HEIGHT = 32;
        unsigned char gfx[DISPLAY_WIDTH * DISPLAY_HEIGHT];

        unsigned char delay_timer;
        unsigned char sound_timer;

        unsigned short stack[16];
        unsigned short sp;

        unsigned char key[16];

        unsigned char chip8_fontset[80] = { 
            0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
            0x20, 0x60, 0x20, 0x20, 0x70, // 1
            0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
            0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
            0x90, 0x90, 0xF0, 0x10, 0x10, // 4
            0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
            0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
            0xF0, 0x10, 0x20, 0x40, 0x40, // 7
            0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
            0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
            0xF0, 0x90, 0xF0, 0x90, 0x90, // A
            0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
            0xF0, 0x80, 0x80, 0x80, 0xF0, // C
            0xE0, 0x90, 0x90, 0x90, 0xE0, // D
            0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
            0xF0, 0x80, 0xF0, 0x80, 0x80  // F
        };

        std::map<int, unsigned short> keyMap = {
            {SDLK_0, 0x0},
            {SDLK_1, 0x1},
            {SDLK_2, 0x2},
            {SDLK_3, 0x3},
            {SDLK_4, 0x4},
            {SDLK_5, 0x5},
            {SDLK_6, 0x6},
            {SDLK_7, 0x7},
            {SDLK_8, 0x8},
            {SDLK_9, 0x9},
            {SDLK_a, 0xA},
            {SDLK_b, 0xB},
            {SDLK_c, 0xC},
            {SDLK_d, 0xD},
            {SDLK_e, 0xE},
            {SDLK_f, 0xF},
        };

        void (Emulator::*systemOpfunctions[0xEE + 1])();
        void (Emulator::*mainOpfunctions[0xF085 + 1])();
        void (Emulator::*registerOpfunctions[0xE + 1])();
        void (Emulator::*miscOpfunctions[0xA1 + 1])();

        void pressKey(unsigned short);

    private:
        Utilities *utilities;

        unsigned char carryFlagIndex;

        bool includeVyInShift;

        // Hacky message passing for key down event
        bool isKeyPressed;
        unsigned short keyCodePressed;

        void clearRegisters();
        void printInstruction(std::string);

        void executeOperation(void (Emulator::*[])(), unsigned short);

        void executeSystemOperation();
        void jumpToAddress();
        void callSubroutine();
        void skipIfEqual();
        void skipIfNotEqual();
        void skipIfRegistersEqual();
        void loadRegister();
        void addByteToRegister();
        void executeRegisterOperation();
        void skipIfRegistersNotEqual();
        void setIndexRegister();
        void randomAnd();
        void updateGraphicsBuffer();
        void executeMiscOperation();

        void clearDisplay();
        void returnFromSubroutine();

        void copyRegister();
        void bitwiseOr();
        void bitwiseAnd();
        void bitwiseXor();
        void addRegisters();
        void subtractRegisters();
        void shiftRight();
        void shiftLeft();
        void pointToSprite();

        void skipInstructionIfKeyPressed();
        void skipInstructionIfKeyNotPressed();
        void storeDelayTimer();
        void setDelayTimer();
        void addToIndexPointer();
        void storeBinaryCodedDecimal();
        void storeRegistersInRange();
        void loadRegistersInRange();
        void waitForKeyPress();
};

#endif
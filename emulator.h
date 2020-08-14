#ifndef EMULATOR_H
#define EMULATOR_H

#include <string>

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
        unsigned char gfx[64 * 32];

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

    private:
        unsigned char carryFlagIndex;

        void clearRegisters();

        void setIndexRegister();
        void callSubroutine();
        void addRegisters();
        void storeBinaryCodedDecimal();
        void updateGraphicsBuffer();
        void skipInstructionIfKeyPressed();
        void skipInstructionIfKeyNotPressed();

        void printInstruction(std::string);
};

#endif
#include <iostream>
#include "emulator.h"

void initializeGraphics(){
    std::cout << "Initializing graphics\n";
}

void initializeInput(){
    std::cout << "Initializing input\n";
}

void Emulator::setIndexRegister() {
    std::cout << "Executing 0xANNN: Set I to the address NNN\n";

    I = opcode & 0x0FFF;
    std::cout << "  I: 0x" << std::hex << I << "\n";

    pc += 2;
}

void Emulator::callSubroutine() {
    std::cout << "Executing 0x2NNN: Call subroutine at address NNN\n";

    stack[sp] = pc;
    ++sp;

    pc = opcode & 0x0FFF; 
    std::cout << "  PC: 0x" << std::hex << pc << "\n";
}

void Emulator::addRegisters() {
    std::cout << "Executing 0x8XY4: Add value of register Y to register X\n";

    int xRegisterIndex = (opcode & 0x0F00) >> 8;
    int yRegisterIndex = (opcode & 0x00F0) >> 4;

    if (V[yRegisterIndex] > (0xFF - V[xRegisterIndex])) {
        V[carryFlagIndex] = 1; // Set the carry flag
    }
    else {
        V[carryFlagIndex] = 0;
    }

    V[xRegisterIndex] += V[yRegisterIndex];
    std::cout << "  V[X]: " << +V[xRegisterIndex] << "\n";
    std::cout << "  Carry Flag: " << +V[carryFlagIndex] << "\n";

    pc += 2;
}

void Emulator::storeBinaryCodedDecimal() {
    std::cout << "Executing 0xFX33: Store binary-coded decimal representation of VX\n";

    memory[I] = V[(opcode & 0x0F00) >> 8] / 100;
    memory[I + 1] = (V[(opcode & 0x0F00) >> 8] / 10) % 10;
    memory[I + 2] = (V[(opcode & 0x0F00) >> 8] % 10) % 10;

    std::cout << "Stored decimal: " << +memory[I] << +memory[I + 1] << +memory[I + 2] << "\n";
    pc += 2;
}

void Emulator::updateGraphicsBuffer() {
    std::cout << "Executing 0xDXYN: Updating graphics buffer\n";

    unsigned short x = V[(opcode & 0x0F00) >> 8];
    unsigned short y = V[(opcode & 0x00F0) >> 4];
    unsigned short height = opcode & 0x000F;
    unsigned short pixel;

    V[0xF] = 0;
    for (int yline = 0; yline < height; yline++) {
        pixel = memory[I + yline];
        for (int xline = 0; xline < 8; xline++) {
            if ((pixel & (0x80 >> xline)) != 0) {
                if (gfx[(x + xline + ((y + yline) * 64))] == 1) {
                    V[0xF] = 1;
                }
                gfx[x + xline + ((y + yline) * 64)] ^= 1;
            }
        }
    }

    drawFlag = true;
    pc += 2;
}

void Emulator::skipInstructionIfKeyPressed() {
    std::cout << "Executing 0xEX9E: Skip next instruction if key stored in V[X] is pressed\n";

    if (key[V[(opcode & 0x0F00) >> 8]] != 0) {
        pc += 4;
    }
    else {
        pc += 2;
    }
}

void Emulator::skipInstructionIfKeyNotPressed(){
    std::cout << "Executing 0xEX9E: Skip next instruction if key stored in V[X] is NOT pressed\n";

    if (key[V[(opcode & 0x0F00) >> 8]] == 0) {
        pc += 4;
    }
    else {
        pc += 2;
    }
}

void Emulator::cycle() {
    opcode = memory[pc] << 8 | memory[pc + 1];

    // Decode opcode
    switch(opcode & 0xF000) {
        case 0xA000:
            Emulator::setIndexRegister();
        break;
        case 0x2000:
            Emulator::callSubroutine();
        break;
        case 0x8000:
            switch (opcode & 0x000F) {
                case 0x0004:
                    Emulator::addRegisters();
                break;
            }
        break;
        case 0xD000:
            Emulator::updateGraphicsBuffer();
        break;
        case 0xE00:
            case 0x009E:
                Emulator::skipInstructionIfKeyPressed();
            break;
            case 0x00A1:
                Emulator::skipInstructionIfKeyNotPressed();
            break;
        break;
        case 0xF000:
            switch (opcode & 0x00FF) {
                case 0x0033:
                    Emulator::storeBinaryCodedDecimal();       
                break;
            }
        break;
        case 0x0000:
            switch (opcode & 0x000F) {
                case 0x0000:
                    std::cout << "Executing 0x00E0: Clear the screen\n";
                break;
                case 0x000E:
                    std::cout << "Executing 0x00EE: Return from subroutine\n";
                break;
            }
        break;
        default:
            std::cout << "Unknown opcode: 0x" << std::hex << opcode << "\n";
    }

    // Update timers
    if (delay_timer > 0) {
        --delay_timer;
    }
    if (sound_timer > 0) {
        if (sound_timer == 1) {
            std::cout << "BEEP\n";
        }
        --sound_timer;
    }
}

Emulator::Emulator() {
    carryFlagIndex = 0xFF;
}

void Emulator::clearRegisters() {
    for (int i = 0; i < 16; i++) {
        V[i] = 0;
    }
}

void Emulator::initialize() {
    std::cout << "Initializing emulator\n";

    pc = 0x200;
    opcode = 0;
    I = 0;
    sp = 0;

    // Clear display
    // Clear stack
    Emulator::clearRegisters();
    // Clear memory

    // Load fontset
    for (int i = 0; i < 80; ++i) {
        memory[i] = chip8_fontset[i];
    }

    // Reset timers
}

void Emulator::loadProgram(std::string program) {
    std::cout << "Loading program: " << program << "\n";

    unsigned short op = 0xD005;
    memory[pc] = op >> 8 & 0xFF;
    memory[pc + 1] = op & 0xFF;
}

void Emulator::setKeys() {
    std::cout << "Setting keys\n";
}
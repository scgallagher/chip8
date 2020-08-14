#include <iostream>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include "emulator.h"

void initializeGraphics(){
    std::cout << "Initializing graphics\n";
}

void initializeInput(){
    std::cout << "Initializing input\n";
}

std::string hexToString(unsigned short hexCode) {
    std::stringstream ss;
    ss << std::hex << hexCode;
    std::string hexString = ss.str();
    return boost::to_upper_copy<std::string>(hexString);
}

void Emulator::printInstruction(std::string instruction) {
    std::cout << "0x" << hexToString(opcode) << " " << instruction << std::endl;
}

// 0xANNN: Set I to the address NNN
void Emulator::setIndexRegister() {
    I = opcode & 0x0FFF;

    printInstruction("LD I, " + hexToString(I));

    pc += 2;
}

// 0x2NNN: Call subroutine at address NNN
void Emulator::callSubroutine() {
    stack[sp] = pc;
    ++sp;

    unsigned short subroutineAddress = opcode & 0x0FFF;
    pc = subroutineAddress; 

    printInstruction("CALL " + hexToString(subroutineAddress));
}

// 0x8XY4: Add value of register Y to register X
void Emulator::addRegisters() {
    int xRegisterIndex = (opcode & 0x0F00) >> 8;
    int yRegisterIndex = (opcode & 0x00F0) >> 4;

    if (V[yRegisterIndex] > (0xFF - V[xRegisterIndex])) {
        V[carryFlagIndex] = 1; // Set the carry flag
    }
    else {
        V[carryFlagIndex] = 0;
    }

    V[xRegisterIndex] += V[yRegisterIndex];

    std::string instruction =  "ADD V" + hexToString(xRegisterIndex) + ", V" + hexToString(yRegisterIndex);
    printInstruction(instruction);

    pc += 2;
}

// 0xFX33: Store binary-coded decimal representation of VX
void Emulator::storeBinaryCodedDecimal() {
    unsigned short vIndex = (opcode & 0x0F00) >> 8;
    memory[I] = V[vIndex] / 100;
    memory[I + 1] = (V[vIndex] / 10) % 10;
    memory[I + 2] = (V[vIndex] % 10) % 10;

    std::cout << "Stored decimal: " << +memory[I] << +memory[I + 1] << +memory[I + 2] << "\n";
    printInstruction("LD B, V" + hexToString(vIndex));
    pc += 2;
}

// 0xDXYN: Updating graphics buffer
void Emulator::updateGraphicsBuffer() {
    unsigned short xIndex = (opcode & 0x0F00) >> 8;
    unsigned short yIndex = (opcode & 0x00F0) >> 4;
    unsigned short x = V[xIndex];
    unsigned short y = V[yIndex];
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

    std::string instruction = "DRW V" + hexToString(xIndex) + ", V" + hexToString(yIndex) + ", " + hexToString(height);
    printInstruction(instruction);

    drawFlag = true;
    pc += 2;
}

// 0xEX9E: Skip next instruction if key stored in V[X] is pressed
void Emulator::skipInstructionIfKeyPressed() {
    unsigned short index = (opcode & 0x0F00) >> 8;
    if (key[V[index]] != 0) {
        pc += 4;
    }
    else {
        pc += 2;
    }
    
    printInstruction("SKP V" + hexToString(index));
}

// 0xEXA1: Skip next instruction if key stored in V[X] is NOT pressed
void Emulator::skipInstructionIfKeyNotPressed(){
    std::cout << "here" << std::endl;
    unsigned short index = (opcode & 0x0F00) >> 8;
    if (key[V[index]] == 0) {
        pc += 4;
    }
    else {
        pc += 2;
    }

    printInstruction("SKNP V" + hexToString(index));
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
        case 0xE000:
            switch (opcode & 0x00FF) {
                case 0x009E:
                    Emulator::skipInstructionIfKeyPressed();
                break;
                case 0x00A1:
                    Emulator::skipInstructionIfKeyNotPressed();
                break;
            }
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

    unsigned short op = 0xE9A1;
    memory[pc] = op >> 8 & 0xFF;
    memory[pc + 1] = op & 0xFF;
}

void Emulator::setKeys() {

}
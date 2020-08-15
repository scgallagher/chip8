#include <iostream>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include "emulator.h"

void initializeGraphics(){
    // Todo
}

void initializeInput(){
    // Todo
}

std::string hexToString(unsigned short hexCode, bool includePrefix) {
    std::stringstream ss;
    ss << std::hex << hexCode;
    std::string hexString = boost::to_upper_copy<std::string>(ss.str());

    if (includePrefix) {
        hexString = "0x" + hexString;
    }

    return hexString;
}

std::string hexToString(unsigned short hexCode) {
    return hexToString(hexCode, true);
}

void Emulator::printInstruction(std::string instruction) {
    std::cout << hexToString(pc) << ": " << hexToString(opcode) << " " << instruction << std::endl;
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
    printInstruction("CALL " + hexToString(subroutineAddress));
    
    pc = subroutineAddress; 
}

// 0x8XY4: Add value of register Y to register X
void Emulator::addRegisters() {
    int xRegisterIndex = (opcode & 0x0F00) >> 8;
    int yRegisterIndex = (opcode & 0x00F0) >> 4;

    std::string instruction =  "ADD V" + hexToString(xRegisterIndex, false) + ", V" + hexToString(yRegisterIndex, false);
    printInstruction(instruction);

    if (V[yRegisterIndex] > (0xFF - V[xRegisterIndex])) {
        V[carryFlagIndex] = 1; // Set the carry flag
    }
    else {
        V[carryFlagIndex] = 0;
    }

    V[xRegisterIndex] += V[yRegisterIndex];

    pc += 2;
}

// 0xFX33: Store binary-coded decimal representation of VX
void Emulator::storeBinaryCodedDecimal() {
    unsigned short vIndex = (opcode & 0x0F00) >> 8;
    printInstruction("LD B, V" + hexToString(vIndex, false));

    memory[I] = V[vIndex] / 100;
    memory[I + 1] = (V[vIndex] / 10) % 10;
    memory[I + 2] = (V[vIndex] % 10) % 10;

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

    std::string instruction = "DRW V" + hexToString(xIndex, false) + ", V" + hexToString(yIndex, false) + ", " + hexToString(height);
    printInstruction(instruction);
    
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

// 0xEX9E: Skip next instruction if key stored in V[X] is pressed
void Emulator::skipInstructionIfKeyPressed() {
    unsigned short index = (opcode & 0x0F00) >> 8;
    printInstruction("SKP V" + hexToString(index, false));
    
    if (key[V[index]] != 0) {
        pc += 4;
    }
    else {
        pc += 2;
    }
}

// 0xEXA1: Skip next instruction if key stored in V[X] is NOT pressed
void Emulator::skipInstructionIfKeyNotPressed(){
    unsigned short index = (opcode & 0x0F00) >> 8;
    printInstruction("SKNP V" + hexToString(index, false));
    
    if (key[V[index]] == 0) {
        pc += 4;
    }
    else {
        pc += 2;
    }
}

void Emulator::executeRegisterOperation() {
    unsigned short index = (opcode & 0x000F);

    void (Emulator::*opfunction)() = registerOpfunctions[index];

    if (opfunction == nullptr) {
        throw hexToString(opcode);
    }
    else {
        (this->*opfunction)();
    }
}

void Emulator::executeInputOperation() {
    unsigned short index = (opcode & 0x00FF);

    void (Emulator::*opfunction)() = inputOpfunctions[index];

    if (opfunction == nullptr) {
        throw hexToString(opcode);
    }
    else {
        (this->*opfunction)();
    }
}

void Emulator::executeMiscOperation() {
    unsigned short index = (opcode & 0x00FF);

    void (Emulator::*opfunction)() = miscOpfunctions[index];

    if (opfunction == nullptr) {
        throw hexToString(opcode);
    }
    else {
        (this->*opfunction)();
    }
}

void Emulator::cycle() {
    opcode = memory[pc] << 8 | memory[pc + 1];

    unsigned short index = opcode & 0xF000;
    void (Emulator::*opfunction)() = opfunctions[index];

    if (opfunction == nullptr) {
        throw hexToString(opcode);
    }
    else {
        (this->*opfunction)();
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

    for (int i = 0; i < 0xF085; i++) {
        opfunctions[i] == nullptr;
    }

    opfunctions[0xA000] = Emulator::setIndexRegister;
    opfunctions[0x2000] = Emulator::callSubroutine;
    opfunctions[0x8000] = Emulator::executeRegisterOperation;
    opfunctions[0xD000] = Emulator::updateGraphicsBuffer;
    opfunctions[0xE000] = Emulator::executeInputOperation;
    opfunctions[0xF000] = Emulator::executeMiscOperation;

    registerOpfunctions[0x4] = Emulator::addRegisters;

    inputOpfunctions[0x9E] = Emulator::skipInstructionIfKeyPressed;
    inputOpfunctions[0xA1] = Emulator::skipInstructionIfKeyNotPressed;

    miscOpfunctions[0x33] = Emulator::storeBinaryCodedDecimal;
}

void Emulator::clearRegisters() {
    for (int i = 0; i < 16; i++) {
        V[i] = 0;
    }
}

void Emulator::initialize() {
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

    unsigned short op = 0xFA33;
    memory[pc] = op >> 8 & 0xFF;
    memory[pc + 1] = op & 0xFF;
}

void Emulator::setKeys() {

}
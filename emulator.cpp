#include <iostream>
#include <sstream>
#include <fstream>
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

std::string opcodeToString(unsigned short hexCode) {
    std::string instruction = hexToString(hexCode, false);
    if (instruction.length() == 2) {
        instruction = "00" + instruction;
    }
    return "0x" + instruction;
}

void Emulator::printInstruction(std::string instruction) {
    std::cout << hexToString(pc) << ": " << opcodeToString(opcode) << " " << instruction << std::endl;
}

// 0x00EE: Return from subroutine
void Emulator::returnFromSubroutine() {
    printInstruction("RET");

    pc = stack[sp--];
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

// 0x6Xkk: Load the value kk into register VX
void Emulator::loadRegister() {
    unsigned short value = opcode & 0x00FF;
    unsigned short registerIndex = opcode & 0x0F00;

    printInstruction("LD V" + hexToString(false) + ", " + hexToString(value));
    V[registerIndex] = value;

    pc += 2;
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

void Emulator::executeSystemOperation() {
    executeOperation(systemOpfunctions, 0x00FF);
}

void Emulator::executeRegisterOperation() {
    executeOperation(registerOpfunctions, 0x000F);
}

void Emulator::executeMiscOperation() {
    executeOperation(miscOpfunctions, 0x00FF);
}

void Emulator::executeOperation(void (Emulator::*opfunctions[])(), unsigned short mask) {
    unsigned short index = (opcode & mask);

    void (Emulator::*opfunction)() = opfunctions[index];

    if (opfunction == nullptr) {
        throw opcodeToString(opcode);
    }
    else {
        (this->*opfunction)();
    }
}

void Emulator::cycle() {
    opcode = memory[pc] << 8 | memory[pc + 1];

    executeOperation(mainOpfunctions, 0xF000);

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

    mainOpfunctions[0x0000] = &Emulator::executeSystemOperation;
    mainOpfunctions[0xA000] = &Emulator::setIndexRegister;
    mainOpfunctions[0x2000] = &Emulator::callSubroutine;
    mainOpfunctions[0x6000] = &Emulator::loadRegister;
    mainOpfunctions[0x8000] = &Emulator::executeRegisterOperation;
    mainOpfunctions[0xD000] = &Emulator::updateGraphicsBuffer;
    mainOpfunctions[0xE000] = &Emulator::executeMiscOperation;
    mainOpfunctions[0xF000] = &Emulator::executeMiscOperation;

    systemOpfunctions[0xEE] = &Emulator::returnFromSubroutine;
    
    registerOpfunctions[0x4] = &Emulator::addRegisters;

    miscOpfunctions[0x9E] = &Emulator::skipInstructionIfKeyPressed;
    miscOpfunctions[0xA1] = &Emulator::skipInstructionIfKeyNotPressed;
    miscOpfunctions[0x33] = &Emulator::storeBinaryCodedDecimal;
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

void Emulator::loadProgram(std::string romFilePath) {
    std::cout << "Loading program: " << romFilePath << "\n";

    unsigned short op = 0xF933;
    memory[pc] = op >> 8 & 0xFF;
    memory[pc + 1] = op & 0xFF;

    std::ifstream romFile;
    romFile.open(romFilePath, std::ios::in | std::ios::binary | std::ios::ate);
    std::ios::streampos size = romFile.tellg();
    char * fileContents = new char[size];
    romFile.seekg(0, std::ios::beg);

    romFile.read(fileContents, size);

    romFile.close();

    unsigned char *rom = new unsigned char[size];
    rom = (unsigned char*) fileContents;
    
    for (int i = 0; i < size; i++) {
        memory[0x200 + i] = rom[i];
    }
}

void Emulator::setKeys() {

}
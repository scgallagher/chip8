#include <iostream>
#include <sstream>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <stdlib.h>
#include "emulator.h"
#include "utilities.h"

void initializeGraphics(){
    // Todo
}

void initializeInput(){
    // Todo
}

void Emulator::pressKey(unsigned short keyCodePressed) {
    key[keyCodePressed] = 1;

    this->isKeyPressed = true;
    this->keyCodePressed = keyCodePressed;
}

bool Emulator::isSoundTimerActive() {
    return sound_timer > 0;
}

void Emulator::printInstruction(std::string instruction) {
    std::cout << utilities->hexToString(pc) << ": " << utilities->opcodeToString(opcode) << " " << instruction << std::endl;
}

void Emulator::executeSystemOperation() {
    executeOperation(systemOpfunctions, 0x00FF);
}

// 0x1NNN: Jump to location nnn
void Emulator::jumpToAddress() {
    unsigned short address = opcode & 0x0FFF;

    printInstruction("JP " + utilities->hexToString(address));

    pc = address;
}

// 0x2NNN: Call subroutine at address NNN
void Emulator::callSubroutine() {
    stack[sp++] = pc + 2;

    unsigned short subroutineAddress = opcode & 0x0FFF;
    printInstruction("CALL " + utilities->hexToString(subroutineAddress));
    
    pc = subroutineAddress; 
}

// 0x3XKK: Skip next instruction if Vx = kk
void Emulator::skipIfEqual() {
    unsigned short value = opcode & 0x00FF;
    unsigned short registerIndex = (opcode & 0x0F00) >> 8;

    printInstruction("SE V" + utilities->hexToString(registerIndex, false) + ", " + utilities->hexToString(value));
    if (V[registerIndex] == value) {
        pc += 2;
    }

    pc += 2;
}

// 0x4XKK: Skip next instruction if Vx != kk
void Emulator::skipIfNotEqual() {
    unsigned short value = opcode & 0x00FF;
    unsigned short registerIndex = (opcode & 0x0F00) >> 8;

    printInstruction("SNE V" + utilities->hexToString(registerIndex, false) + ", " + utilities->hexToString(value));
    if (V[registerIndex] != value) {
        pc += 2;
    }

    pc += 2;
}

// 0x5XY0
void Emulator::skipIfRegistersEqual() {
    unsigned short xRegisterIndex = (opcode & 0x0F00) >> 8;
    unsigned short yRegisterIndex = (opcode & 0x00F0) >> 4;

    printInstruction("SE V" + utilities->hexToString(xRegisterIndex, false) + ", V" + utilities->hexToString(yRegisterIndex, false));
    if (V[xRegisterIndex] == V[yRegisterIndex]) {
        pc += 2;
    }

    pc += 2;
}

// 0x6Xkk: Load the value kk into register VX
void Emulator::loadRegister() {
    unsigned short value = opcode & 0x00FF;
    unsigned short registerIndex = (opcode & 0x0F00) >> 8;

    printInstruction("LD V" + utilities->hexToString(registerIndex, false) + ", " + utilities->hexToString(value));
    V[registerIndex] = value;

    pc += 2;
}

// 0x7XKK: Adds the value kk to the value of register Vx, then stores the result in Vx
void Emulator::addByteToRegister() {
    unsigned short value = opcode & 0x00FF;
    unsigned short registerIndex = (opcode & 0x0F00) >> 8;

    printInstruction("ADD V" + utilities->hexToString(registerIndex, false) + ", " + utilities->hexToString(value));
    V[registerIndex] += value;

    pc += 2;
}

void Emulator::executeRegisterOperation() {
    executeOperation(registerOpfunctions, 0x000F);
}

// 0x9XY0: Skip next instruction if Vx != Vy.
void Emulator::skipIfRegistersNotEqual() {
    int xRegisterIndex = (opcode & 0x0F00) >> 8;
    int yRegisterIndex = (opcode & 0x00F0) >> 4;

    std::string instruction =  "SNE V" + utilities->hexToString(xRegisterIndex, false) + ", V" + utilities->hexToString(yRegisterIndex, false);
    printInstruction(instruction);

    if (V[xRegisterIndex] != V[yRegisterIndex]) {
        pc += 2;
    }

    pc += 2;
}

// 0xANNN: Set I to the address NNN
void Emulator::setIndexRegister() {
    I = opcode & 0x0FFF;

    printInstruction("LD I, " + utilities->hexToString(I));

    pc += 2;
}

// 0xBNNN: Jump to location NNN + V0
void Emulator::jumpToAddressPlusOffset() {
    unsigned short address = opcode & 0x0FFF;

    printInstruction("JP V0, " + utilities->hexToString(address));

    pc = address + V[0];
}

// 0xCXKK: Set Vx = random byte AND kk
void Emulator::randomAnd() {
    unsigned short value = opcode & 0x00FF;
    unsigned short registerIndex = (opcode & 0x0F00) >> 8;

    printInstruction("RND V" + utilities->hexToString(registerIndex, false) + ", " + utilities->hexToString(value));

    int random = rand() % 256;
    V[registerIndex] = random & value;

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

    std::string instruction = "DRW V" + utilities->hexToString(xIndex, false) + ", V" + utilities->hexToString(yIndex, false) + ", " + utilities->hexToString(height);
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

void Emulator::executeMiscOperation() {
    executeOperation(miscOpfunctions, 0x00FF);
}

// 0x00E0: Clear the display
void Emulator::clearDisplay() {
    printInstruction("CLS");

    for (int i = 0; i < DISPLAY_WIDTH * DISPLAY_HEIGHT; i++) {
        gfx[i] = 0x0;
    }

    pc += 2;
}

// 0x00EE: Return from subroutine
void Emulator::returnFromSubroutine() {
    printInstruction("RET");

    pc = stack[--sp];
}

// 0x8XY0: Set Vx = Vy
void Emulator::copyRegister() {
    int xRegisterIndex = (opcode & 0x0F00) >> 8;
    int yRegisterIndex = (opcode & 0x00F0) >> 4;

    std::string instruction =  "LD V" + utilities->hexToString(xRegisterIndex, false) + ", V" + utilities->hexToString(yRegisterIndex, false);
    printInstruction(instruction);

    V[xRegisterIndex] = V[yRegisterIndex];

    pc += 2;
}

// 0x8XY1: Bitwise OR (Vx = Vx | Vy)
void Emulator::bitwiseOr() {
    int xRegisterIndex = (opcode & 0x0F00) >> 8;
    int yRegisterIndex = (opcode & 0x00F0) >> 4;

    std::string instruction("OR V" + utilities->hexToString(xRegisterIndex, false) + ", V" + utilities->hexToString(yRegisterIndex, false));
    printInstruction(instruction);

    V[xRegisterIndex] |= V[yRegisterIndex];

    pc += 2;
}

// 0x8XY2: Bitwise AND (Vx = Vx & Vy)
void Emulator::bitwiseAnd() {
    int xRegisterIndex = (opcode & 0x0F00) >> 8;
    int yRegisterIndex = (opcode & 0x00F0) >> 4;

    std::string instruction("AND V" + utilities->hexToString(xRegisterIndex, false) + ", V" + utilities->hexToString(yRegisterIndex, false));
    printInstruction(instruction);

    V[xRegisterIndex] &= V[yRegisterIndex];

    pc += 2;
}

// 0x8XY3: Bitwise XOR (Vx = Vx ^ Vy)
void Emulator::bitwiseXor() {
    int xRegisterIndex = (opcode & 0x0F00) >> 8;
    int yRegisterIndex = (opcode & 0x00F0) >> 4;

    std::string instruction("XOR V" + utilities->hexToString(xRegisterIndex, false) + ", V" + utilities->hexToString(yRegisterIndex, false));
    printInstruction(instruction);

    V[xRegisterIndex] ^= V[yRegisterIndex];

    pc += 2;
}

// 0x8XY4: Add value of register Y to register X
void Emulator::addRegisters() {
    int xRegisterIndex = (opcode & 0x0F00) >> 8;
    int yRegisterIndex = (opcode & 0x00F0) >> 4;

    std::string instruction =  "ADD V" + utilities->hexToString(xRegisterIndex, false) + ", V" + utilities->hexToString(yRegisterIndex, false);
    printInstruction(instruction);

    if (V[yRegisterIndex] > (0xFF - V[xRegisterIndex])) {
        V[carryFlagIndex] = 1;
    }
    else {
        V[carryFlagIndex] = 0;
    }

    V[xRegisterIndex] += V[yRegisterIndex];

    pc += 2;
}

// 0x8XY5: Subtract value of register Y from register X
void Emulator::subtractRegisters() {
    int xRegisterIndex = (opcode & 0x0F00) >> 8;
    int yRegisterIndex = (opcode & 0x00F0) >> 4;

    std::string instruction =  "SUB V" + utilities->hexToString(xRegisterIndex, false) + ", V" + utilities->hexToString(yRegisterIndex, false);
    printInstruction(instruction);

    if (V[xRegisterIndex] > V[yRegisterIndex]) {
        V[carryFlagIndex] = 1;
    }
    else {
        V[carryFlagIndex] = 0;
    }

    V[xRegisterIndex] -= V[yRegisterIndex];

    pc += 2;
}

// 0x8XY6: Shift Vx right by 1 byte
void Emulator::shiftRight() {
    int xRegisterIndex = (opcode & 0x0F00) >> 8;

    std::string instruction = "SHR V" + utilities->hexToString(xRegisterIndex, false);
    if (includeVyInShift) {
        int yRegisterIndex = (opcode & 0x00F0) >> 4;
        instruction += ", V" + utilities->hexToString(yRegisterIndex, false);

        V[xRegisterIndex] = V[yRegisterIndex];
    }

    printInstruction(instruction);

    if ((V[xRegisterIndex] & 0x1) == 1) {
        V[carryFlagIndex] = 1;
    }

    V[xRegisterIndex] = V[xRegisterIndex] >> 1;

    pc += 2;
}

// 0x8XY7: Subtract value of register X from register Y
void Emulator::subtractRegistersReversed() {
    int xRegisterIndex = (opcode & 0x0F00) >> 8;
    int yRegisterIndex = (opcode & 0x00F0) >> 4;

    std::string instruction =  "SUBN V" + utilities->hexToString(yRegisterIndex, false) + ", V" + utilities->hexToString(xRegisterIndex, false);
    printInstruction(instruction);

    if (V[yRegisterIndex] > V[xRegisterIndex]) {
        V[carryFlagIndex] = 1;
    }
    else {
        V[carryFlagIndex] = 0;
    }

    V[xRegisterIndex] = V[yRegisterIndex] - V[xRegisterIndex];

    pc += 2;
}

// 0x8XYE: Shift Vx left by 1 byte
void Emulator::shiftLeft() {
    int xRegisterIndex = (opcode & 0x0F00) >> 8;

    std::string instruction = "SHL V" + utilities->hexToString(xRegisterIndex, false);
    if (includeVyInShift) {
        int yRegisterIndex = (opcode & 0x00F0) >> 4;
        instruction += ", V" + utilities->hexToString(yRegisterIndex, false);

        V[xRegisterIndex] = V[yRegisterIndex];
    }

    printInstruction(instruction);

    if ((V[xRegisterIndex] >> 7) == 1) {
        V[carryFlagIndex] = 1;
    }
    else {
        V[carryFlagIndex] = 0;
    }

    V[xRegisterIndex] = V[xRegisterIndex] << 1;

    std::cout << "Result: " << utilities->hexToString(V[xRegisterIndex]) << std::endl;

    pc += 2;
}

// 0xFX07: Set Vx = delay timer value
void Emulator::storeDelayTimer() {
    unsigned short registerIndex = (opcode & 0x0F00) >> 8;

    printInstruction("LD V" + utilities->hexToString(registerIndex, false) + ", DT");

    V[registerIndex] = delay_timer;

    pc += 2;
}

// 0xFX0A: Wait for key press, store value of the key in Vx
void Emulator::waitForKeyPress() {
    unsigned char registerIndex = (opcode & 0x0F00) >> 8;
    
    std::string instruction = "LD V" + utilities->hexToString(registerIndex, false) + ", K";
    printInstruction(instruction);

    if (isKeyPressed) {
        V[registerIndex] = keyCodePressed;
        isKeyPressed = false;
        pc += 2;
    }
}

// 0xFX15: Set delay timer = Vx
void Emulator::setDelayTimer() {
    unsigned short registerIndex = (opcode & 0x0F00) >> 8;

    printInstruction("LD DT, V" + utilities->hexToString(registerIndex, false));

    delay_timer = V[registerIndex];

    pc += 2;
}

// 0xFX18: Set sound timer = Vx
void Emulator::setSoundTimer() {
    unsigned short registerIndex = (opcode & 0x0F00) >> 8;

    printInstruction("LD ST, V" + utilities->hexToString(registerIndex, false));

    sound_timer = V[registerIndex];

    pc += 2;
}

// 0xFX1E: Set I = I + Vx
void Emulator::addToIndexPointer() {
    unsigned short registerIndex = (opcode & 0x0F00) >> 8;

    printInstruction("ADD I, V" + utilities->hexToString(registerIndex, false));

    I += V[registerIndex];

    pc += 2;
}

// 0xFX29: Set I = location of sprite for digit Vx
void Emulator::pointToSprite() {
    unsigned short registerIndex = (opcode & 0x0F00) >> 8;

    printInstruction("LD F, V" + utilities->hexToString(registerIndex, false));

    unsigned short spriteOffset = 5;
    I = V[registerIndex] * spriteOffset;

    pc += 2;
}

// 0xFX33: Store binary-coded decimal representation of VX
void Emulator::storeBinaryCodedDecimal() {
    unsigned short vIndex = (opcode & 0x0F00) >> 8;
    printInstruction("LD B, V" + utilities->hexToString(vIndex, false));

    memory[I] = V[vIndex] / 100;
    memory[I + 1] = (V[vIndex] / 10) % 10;
    memory[I + 2] = (V[vIndex] % 10) % 10;

    pc += 2;
}

// 0xFX55: Store registers V0 through Vx in memory, starting at address I
void Emulator::storeRegistersInRange() {
    unsigned char registerIndex = (opcode & 0x0F00) >> 8;
    unsigned short address = I;

    std::string instruction = "LD [I], V" + utilities->hexToString(registerIndex, false);
    printInstruction(instruction);

    for (int i = 0; i <= registerIndex; i++) {
        memory[address] = V[i];
        address++;
    }

    pc += 2;
}

// 0xFX65: Load registers V0 through Vx from memory, starting at address I
void Emulator::loadRegistersInRange() {
    unsigned char registerIndex = (opcode & 0x0F00) >> 8;
    unsigned short address = I;

    std::string instruction = "LD V" + utilities->hexToString(registerIndex, false) + ", [I]";
    printInstruction(instruction);

    for (int i = 0; i <= registerIndex; i++) {
        V[i] = memory[address];
        address++;
    }

    pc += 2;
}

// 0xEX9E: Skip next instruction if key stored in V[X] is pressed
void Emulator::skipInstructionIfKeyPressed() {
    unsigned short index = (opcode & 0x0F00) >> 8;
    printInstruction("SKP V" + utilities->hexToString(index, false));
    
    unsigned short keyCode = V[index];
    if (key[keyCode] != 0) {
        key[keyCode] = 0;
        pc += 4;
    }
    else {
        pc += 2;
    }
}

// 0xEXA1: Skip next instruction if key stored in V[X] is NOT pressed
void Emulator::skipInstructionIfKeyNotPressed(){
    unsigned short index = (opcode & 0x0F00) >> 8;
    printInstruction("SKNP V" + utilities->hexToString(index, false));
    
    unsigned short keyCode = V[index];
    if (key[keyCode] == 0) {
        pc += 4;
    }
    else {
        key[keyCode] = 0;
        pc += 2;
    }
}

void Emulator::executeOperation(void (Emulator::*opfunctions[])(), unsigned short mask) {
    unsigned short index = (opcode & mask);

    void (Emulator::*opfunction)() = opfunctions[index];

    if (opfunction == nullptr) {
        throw utilities->opcodeToString(opcode);
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
        --sound_timer;
    }

    setKeys();
}

Emulator::Emulator() {
    utilities = new Utilities();

    carryFlagIndex = 0xF;
    includeVyInShift = false;

    mainOpfunctions[0x0000] = &Emulator::executeSystemOperation;
    mainOpfunctions[0x1000] = &Emulator::jumpToAddress;
    mainOpfunctions[0x2000] = &Emulator::callSubroutine;
    mainOpfunctions[0x3000] = &Emulator::skipIfEqual;
    mainOpfunctions[0x4000] = &Emulator::skipIfNotEqual;
    mainOpfunctions[0x5000] = &Emulator::skipIfRegistersEqual;
    mainOpfunctions[0x6000] = &Emulator::loadRegister;
    mainOpfunctions[0x7000] = &Emulator::addByteToRegister;
    mainOpfunctions[0x8000] = &Emulator::executeRegisterOperation;
    mainOpfunctions[0x9000] = &Emulator::skipIfRegistersNotEqual;
    mainOpfunctions[0xA000] = &Emulator::setIndexRegister;
    mainOpfunctions[0xB000] = &Emulator::jumpToAddressPlusOffset;
    mainOpfunctions[0xC000] = &Emulator::randomAnd;
    mainOpfunctions[0xD000] = &Emulator::updateGraphicsBuffer;
    mainOpfunctions[0xE000] = &Emulator::executeMiscOperation;
    mainOpfunctions[0xF000] = &Emulator::executeMiscOperation;

    systemOpfunctions[0xE0] = &Emulator::clearDisplay;
    systemOpfunctions[0xEE] = &Emulator::returnFromSubroutine;
    
    registerOpfunctions[0x0] = &Emulator::copyRegister;
    registerOpfunctions[0x1] = &Emulator::bitwiseOr;
    registerOpfunctions[0x2] = &Emulator::bitwiseAnd;
    registerOpfunctions[0x3] = &Emulator::bitwiseXor;
    registerOpfunctions[0x4] = &Emulator::addRegisters;
    registerOpfunctions[0x5] = &Emulator::subtractRegisters;
    registerOpfunctions[0x6] = &Emulator::shiftRight;
    registerOpfunctions[0x7] = &Emulator::subtractRegistersReversed;
    registerOpfunctions[0xE] = &Emulator::shiftLeft;

    miscOpfunctions[0x07] = &Emulator::storeDelayTimer;
    miscOpfunctions[0x0A] = &Emulator::waitForKeyPress;
    miscOpfunctions[0x15] = &Emulator::setDelayTimer;
    miscOpfunctions[0x18] = &Emulator::setSoundTimer;
    miscOpfunctions[0x1E] = &Emulator::addToIndexPointer;
    miscOpfunctions[0x29] = &Emulator::pointToSprite;
    miscOpfunctions[0x33] = &Emulator::storeBinaryCodedDecimal;
    miscOpfunctions[0x55] = &Emulator::storeRegistersInRange;
    miscOpfunctions[0x65] = &Emulator::loadRegistersInRange;
    miscOpfunctions[0x9E] = &Emulator::skipInstructionIfKeyPressed;
    miscOpfunctions[0xA1] = &Emulator::skipInstructionIfKeyNotPressed;
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

    isKeyPressed = false;

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
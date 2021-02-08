#include "display.h"
#include <SDL2/SDL.h>
#include <iostream>

Display::Display() {

}

bool Display::initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Could not initialize SDL. SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    else {
        window = SDL_CreateWindow("Chip8", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            std::cout << "Could not create window. SDL_Error: " << SDL_GetError() << std::endl;
            return false;
        }
        else {
            screenSurface = SDL_GetWindowSurface(window);
            return true;
        }
    }
}

SDL_Surface* Display::loadFromBuffer(void* buffer) {
    int width = 64;
    int height = 32;

    int depth = 8;
    int pitch = width;

    uint32_t rmask = 0xE0;
    uint32_t gmask = 0x1C;
    uint32_t bmask = 0x03;
    uint32_t amask = 0x0;
    
    return SDL_CreateRGBSurfaceFrom(buffer, width, height, depth, pitch, rmask, gmask, bmask, amask);
}

SDL_Surface* Display::loadSurface(unsigned char* buffer) {
    SDL_Surface* loadedSurface = loadFromBuffer(buffer);

    if (loadedSurface == NULL) {
        std::cout << "Unable to load image. SDL_Error: " << SDL_GetError() << std::endl;
        return NULL;
    }
    else {
        SDL_Surface* optimizedSurface = SDL_ConvertSurface(loadedSurface, screenSurface->format, 0);
        if (optimizedSurface == NULL) {
            std::cout << "Unable to optimize image. SDL_Error: " << SDL_GetError() << std::endl;
        }
        else {
            SDL_FreeSurface(loadedSurface);
        }
        return optimizedSurface;
    }
}

bool Display::loadMedia(unsigned char* buffer) {
    imageSurface = loadSurface(buffer);
    if (imageSurface == NULL) {
        std::cout << "Unable to load surface. SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    else {
        return true;
    }
}

/*
    Converts emulator graphics buffer to color of your choice.
    The emulator's graphics buffer consists only of values 0 and 1 (pixel off or on).
    Left unprocessed, this will display black for off and blue for on.
    The SDL window uses RGB332 format:
        8 bits for red
        8 bits for green
        2 bits for blue
*/
unsigned char* Display::processColor(unsigned char* buffer) {
    int bufferSize = 64 * 32;
    unsigned char* processedBuffer = new unsigned char[bufferSize];

    for (int i = 0; i < bufferSize; i++) {
        // Change to white
        processedBuffer[i] = buffer[i] * 255;
    }

    return processedBuffer;
}

Display::~Display() {
    SDL_FreeSurface(imageSurface);
    imageSurface = NULL;

    SDL_DestroyWindow(window);
    window = NULL;

    SDL_Quit();
}
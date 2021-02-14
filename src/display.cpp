#include "display.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

Display::Display() {
    stretchRect = new SDL_Rect();
    stretchRect->x = 0;
    stretchRect->y = 0;
    stretchRect->w = SCREEN_WIDTH;
    stretchRect->h = SCREEN_HEIGHT;
}

void Display::initialize() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0) {
        std::string error = "Could not initialize. SDL_Error: " + std::string(SDL_GetError());
        throw error;
    }
    else {
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0 ) {
            std::string error = "SDL_mixer could not initialize! SDL_mixer Error:" + std::string(Mix_GetError());
            throw error;
        }

        beep = Mix_LoadWAV("resources/beep.wav");
        if(beep == NULL)
        {
            std::string error = "Failed to load sound! SDL_mixer Error:" + std::string(Mix_GetError());
            throw error;
        }

        window = SDL_CreateWindow("Chip8", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            std::string error = "Could not create window. SDL_Error: " + std::string(SDL_GetError());
            throw error;
        }
        else {
            screenSurface = SDL_GetWindowSurface(window);
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

void Display::updateDisplay(unsigned char* buffer) {
    unsigned char* colorProcessedBuffer = processColor(buffer);
    if (!loadMedia(colorProcessedBuffer)) {
        std::cout << "Failed to load media" << std::endl;
    }
    else {
        SDL_BlitScaled(imageSurface, NULL, screenSurface, stretchRect);
        SDL_UpdateWindowSurface(window);
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

    Mix_FreeChunk(beep);
    beep = NULL;

    Mix_Quit();
    SDL_Quit();
}
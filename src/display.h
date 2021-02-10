#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>

class Display {
    public:
        const int SCREEN_WIDTH = 1280;
        const int SCREEN_HEIGHT = 640;

        SDL_Window* window;
        SDL_Surface* screenSurface;
        SDL_Surface* imageSurface;

        Display();
        virtual ~Display();

        void initialize();
        SDL_Surface* loadFromBuffer(void*);
        SDL_Surface* loadSurface(unsigned char*);
        bool loadMedia(unsigned char*);
        void updateDisplay(unsigned char*);
        unsigned char* processColor(unsigned char*);

    private:
        SDL_Rect* stretchRect;
};

#endif
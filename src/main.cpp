#include "constants.h"

#include <SDL2/SDL.h>

#include <iostream>

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Could not initialise SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Punch Bill Gates!", 
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        Constants::screenWidth, Constants::screenHeight,
        SDL_WINDOW_SHOWN
    );

    if (window == NULL) {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Surface* screenSurface = SDL_GetWindowSurface(window);

    SDL_DestroyWindow(window);
    window = NULL;

    SDL_Quit();
    
    return 0;
}

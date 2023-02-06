#pragma once

#include "constants.h"

#include <SDL2/SDL.h>

#include <cstdlib>
#include <iostream>

class Game
{
    SDL_Window*  m_window;
    SDL_Renderer* m_renderer;
    SDL_Surface* m_screenSurface;

    bool m_isRunning;

public:
    Game();
    ~Game();

    void Run();
    void Stop();
    
};

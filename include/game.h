#pragma once

#include "constants.h"
#include "billgates.h"
#include "hand.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <cstdlib>
#include <iostream>

class Game
{
    SDL_Window*  m_window;
    SDL_Renderer* m_renderer;
    SDL_Surface* m_screenSurface;

    Mix_Music* m_music;

    BillGates m_billGates;
    Hand m_hand;

    bool m_isRunning;

public:
    Game();
    ~Game();

    void Run();
    void Stop();
    
    void Update(float dt);
    void Draw();
};

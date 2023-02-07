#pragma once

#include "constants.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>

#include <cmath>
#include <cstdlib>
#include <iostream>

class Hand
{
    SDL_Renderer* m_renderer;

    int m_textureWidth, m_textureHeight;
    SDL_Texture* m_texture;

    Mix_Chunk* m_punch;

    char m_handFrame;
    float m_punchTimer;
    float m_punchProgress;

    bool m_isPunching;
    bool m_hasPunched;

public:
    Hand();
    ~Hand();
    
    void Load(SDL_Renderer* renderer);
    void Unload();

    void Update(float dt);
    void Draw();

    void Punch();

    bool IsPunching();
};

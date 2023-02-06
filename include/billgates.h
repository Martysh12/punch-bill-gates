#pragma once

#include "constants.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <cmath>
#include <cstdlib>
#include <iostream>

class BillGates
{
    SDL_Renderer* m_renderer;

    int m_textureWidth, m_textureHeight;
    SDL_Texture* m_texture;

    float m_punchTimer;

public:
    BillGates();
    ~BillGates();
    
    void Load(SDL_Renderer* renderer);
    void Unload();

    void Update(float dt);
    void Draw();

    void Punch();
};

#include "game.h"

Game::Game() : m_isRunning(false) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Could not initialise SDL: " << SDL_GetError() << std::endl;
        abort();
    }

    m_window = SDL_CreateWindow(
        "Punch Bill Gates!", 
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        Constants::screenWidth, Constants::screenHeight,
        SDL_WINDOW_SHOWN
    );

    if (m_window == NULL) {
        std::cerr << "Could not create window: " << SDL_GetError() << std::endl;
        abort();
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (m_renderer == NULL) {
        std::cerr << "Could not create renderer: " << SDL_GetError() << std::endl;
        abort();
    }

    m_screenSurface = SDL_GetWindowSurface(m_window);
}

Game::~Game() {
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Game::Run() {
    m_isRunning = true;

    SDL_Event e;

    while (m_isRunning) {
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            case SDL_QUIT:
                Stop();
            }
        }

        SDL_RenderClear(m_renderer);
        SDL_SetRenderDrawColor(m_renderer, 15, 18, 38, 255);

        SDL_RenderFillRect(m_renderer, NULL);

        SDL_RenderPresent(m_renderer);
    }
}

void Game::Stop() {
    m_isRunning = false;
}

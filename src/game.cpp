#include "game.h"

Game::Game() : m_isRunning(false) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "Could not initialise SDL: " << SDL_GetError() << std::endl;
        abort();
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Could not open audio: " << Mix_GetError() << std::endl;
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

    m_music = Mix_LoadMUS("assets/music.wav");

    if (m_music == NULL) {
        std::cerr << "Could not load music: " << SDL_GetError() << std::endl;
        abort();
    }

    m_billGates.Load(m_renderer);
}

Game::~Game() {
    Mix_FreeMusic(m_music);

    SDL_DestroyWindow(m_window);
    
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Game::Run() {
    m_isRunning = true;

    Mix_PlayMusic(m_music, -1);

    long long timeNow = SDL_GetPerformanceCounter();
    long long timeLast = 0;
    float dt = 0.0f;

    SDL_Event e;
    while (m_isRunning) {
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            case SDL_QUIT:
                Stop();
                break;
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym) {
                case SDLK_SPACE:
                    if (!e.key.repeat) m_billGates.Punch();
                    break;
                }
                break;
            }
        }

        timeLast = timeNow;
        timeNow = SDL_GetPerformanceCounter();
        dt = static_cast<float>(timeNow - timeLast) / static_cast<float>(SDL_GetPerformanceFrequency());

        Update(dt);
        Draw();
    }
}

void Game::Stop() {
    m_isRunning = false;
}

void Game::Update(float dt) {
    m_billGates.Update(dt);
}

void Game::Draw() {
    SDL_RenderClear(m_renderer);
    SDL_SetRenderDrawColor(m_renderer, 15, 18, 38, 255);

    SDL_RenderFillRect(m_renderer, NULL);

    m_billGates.Draw();

    SDL_RenderPresent(m_renderer);
}

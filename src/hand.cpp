#include "hand.h"

Hand::Hand() : m_handFrame(0), m_punchTimer(0.f), m_punchProgress(0.f), m_isPunching(false), m_hasPunched(false)  {
}

Hand::~Hand() {
    Unload();
}

void Hand::Load(SDL_Renderer* renderer){
    m_renderer = renderer;

    SDL_Surface* temporarySurface = IMG_Load("assets/spritesheet.png");

    if (temporarySurface == NULL) {
        std::cerr << "Couldn't load hand: " << IMG_GetError() << std::endl;
        abort();
    }

    SDL_SetColorKey(temporarySurface, SDL_TRUE, SDL_MapRGB(temporarySurface->format, 0x00, 0xFF, 0xFF));

    m_texture = SDL_CreateTextureFromSurface(m_renderer, temporarySurface);

    if (m_texture == NULL) {
        std::cerr << "Couldn't load hand texture: " << SDL_GetError() << std::endl;
        abort();
    }

    m_punch = Mix_LoadWAV("assets/punch.wav");

    if (m_punch == NULL) {
        std::cerr << "Couldn't load punch sound: " << SDL_GetError() << std::endl;
        abort();
    }

    m_textureWidth = temporarySurface->w;
    m_textureHeight = temporarySurface->h;

    SDL_FreeSurface(temporarySurface);
}

void Hand::Unload() {
    if (m_texture != NULL) SDL_DestroyTexture(m_texture);
    if (m_punch != NULL) Mix_FreeChunk(m_punch);
}

void Hand::Update(float dt) {
    if      (m_punchTimer > 0) m_punchTimer -= dt;
    else if (m_punchTimer < 0) m_punchTimer = 0;

    m_punchProgress = m_punchTimer / Constants::handPunchDuration;

    if (m_punchProgress == 0)
        m_handFrame = 0;
    else if (m_punchProgress > 0.75) {
        m_handFrame = static_cast<int>((1.f - m_punchProgress) * (1 / (1 - 0.75)) * 4);
        m_hasPunched = false;
    }
    else if (m_punchProgress < 0.25)
        m_handFrame = static_cast<int>(m_punchProgress * (1 / 0.25) * 4);
    else {
        m_handFrame = 3;

        if (!m_hasPunched) {
            m_isPunching = true;
            m_hasPunched = true;
        }
    }
}

void Hand::Draw() {
    int rightHandY;

    if (m_punchProgress == 0)
        rightHandY = Constants::screenHeight - (42 * 2);
    else if (m_punchProgress > 0.9)
        rightHandY = std::lerp(
            Constants::screenHeight - (42 * 2),
            Constants::screenHeight - (42 * 2) + 30,
            (1.f - m_punchProgress) * (1 / (1 - 0.85))
        );
    else if (m_punchProgress < 0.15)
        rightHandY = std::lerp(
            Constants::screenHeight - (42 * 2),
            Constants::screenHeight - (42 * 2) + 30,
            m_punchProgress * (1 / 0.1)
        );
    else
        rightHandY = Constants::screenHeight - (42 * 2) + 30;


    SDL_Rect rightHandSrcQuad = {28, 98, 113, 42};
    SDL_Rect rightHandDstQuad = {
        Constants::screenWidth - (113 * 2) - 50,
        rightHandY,
        113 * 2,
        42 * 2
    };

    SDL_Rect leftHandSrcQuad;
    SDL_Rect leftHandDstQuad;

    switch (m_handFrame) {
    case 1:
        leftHandSrcQuad = {144, 99, 80, 41};
        leftHandDstQuad = {50, Constants::screenHeight - (41 * 2), 80 * 2, 41 * 2};
        break;
    case 2:
        leftHandSrcQuad = {227, 88, 107, 52};
        leftHandDstQuad = {50, Constants::screenHeight - (52 * 2), 107 * 2, 52 * 2};
        break;
    case 3:
        leftHandSrcQuad = {337, 64, 147, 76};
        leftHandDstQuad = {50, Constants::screenHeight - (76 * 2), 147 * 2, 76 * 2};
        break;
    }

    SDL_RenderCopy(m_renderer, m_texture, &rightHandSrcQuad, &rightHandDstQuad);

    if (m_handFrame != 0)
        SDL_RenderCopy(m_renderer, m_texture, &leftHandSrcQuad, &leftHandDstQuad);
}

void Hand::Punch() {
    m_punchTimer = Constants::handPunchDuration;
}

bool Hand::IsPunching() {
    if (m_isPunching) {
        Mix_PlayChannel(-1, m_punch, 0);
        m_isPunching = false;
        return true;
    } else {
        return false;
    }
}

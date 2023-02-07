#include "billgates.h"

BillGates::BillGates() : m_punchTimer(0.f) {
}

BillGates::~BillGates() {
    Unload();
}

void BillGates::Load(SDL_Renderer* renderer) {
    m_renderer = renderer;

    SDL_Surface* temporarySurface = IMG_Load("assets/billgates.png");

    if (temporarySurface == NULL) {
        std::cerr << "Couldn't load Bill Gates: " << IMG_GetError() << std::endl;
        abort();
    }

    SDL_SetColorKey(temporarySurface, SDL_TRUE, SDL_MapRGB(temporarySurface->format, 0x00, 0xFF, 0xFF));

    m_texture = SDL_CreateTextureFromSurface(m_renderer, temporarySurface);

    if (m_texture == NULL) {
        std::cerr << "Couldn't load Bill Gates's texture: " << SDL_GetError() << std::endl;
        abort();
    }

    m_textureWidth = temporarySurface->w;
    m_textureHeight = temporarySurface->h;

    SDL_FreeSurface(temporarySurface);
}

void BillGates::Unload() {
    if (m_texture != NULL) SDL_DestroyTexture(m_texture);
}

void BillGates::Update(float dt) {

    if      (m_punchTimer > 0) m_punchTimer -= dt;
    else if (m_punchTimer < 0) m_punchTimer = 0;
}

void BillGates::Draw() {
    float punchTimerProgress = m_punchTimer / Constants::billGatesPunchDuration;

    SDL_SetTextureColorMod(
        m_texture,
        255,
        std::lerp(255, 64, punchTimerProgress),
        std::lerp(255, 64, punchTimerProgress)
    );

    SDL_Rect renderQuad = {static_cast<int>(sin(20 * M_PI * punchTimerProgress) * punchTimerProgress * 8), 0, m_textureWidth, m_textureHeight};
    SDL_RenderCopy(m_renderer, m_texture, NULL, &renderQuad);
}

void BillGates::Punch() {
    m_punchTimer = Constants::billGatesPunchDuration;
}

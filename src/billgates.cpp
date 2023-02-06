#include "billgates.h"

BillGates::BillGates() {
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
        std::cerr << "Couldn't load Bill Gates's Texture: " << SDL_GetError() << std::endl;
        abort();
    }

    m_textureWidth = temporarySurface->w;
    m_textureHeight = temporarySurface->h;

    SDL_FreeSurface(temporarySurface);
}

void BillGates::Unload() {
    if (m_texture != NULL) SDL_DestroyTexture(m_texture);
}

void BillGates::Update() {

}

void BillGates::Draw() {
    SDL_Rect renderQuad = {0, 0, m_textureWidth, m_textureHeight};
    SDL_RenderCopy(m_renderer, m_texture, NULL, &renderQuad);
}

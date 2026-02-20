#pragma once
#include "SDL.h"

class Spritesheet
{
public:
    Spritesheet(SDL_Renderer* pRenderer, char const* path, int pImageWidth, int pImageHeight, int pNumRows, int pNumColumns);
    ~Spritesheet() = default;

    void SelectSprite(const char pChar);
    void SelectSprite(int pRow, int pColumn);
    void DrawSelectedSprite(SDL_Renderer* pRenderer, SDL_Rect* pDestRect);
    void GetSpriteIndices(const char c, int& pX, int& pY);

private:
    int mGlyphHorizontalCropPixels;
    int mWidth;
    int mHeight;
    SDL_Rect     m_clip;
    SDL_Texture* m_spritesheet_image;
};
#pragma once

#include "draw.h"

void draw_rect(SDL_Renderer* r, SDL_Rect rect, SDL_Color color)
{
    SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(r, color.r, color.g, color.b, color.a);
    SDL_RenderDrawRect(r, &rect);
    SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_NONE);
    SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
}

void draw_filled(SDL_Renderer* r, SDL_Rect rect, SDL_Color color)
{
    SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(r, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(r, &rect);
    SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_NONE);
    SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
}

void get_text_texture( //
    SDL_Renderer* renderer,
    char*         text,
    TTF_Font*     font,
    SDL_Color     color,
    SDL_Texture** texture,
    Uint32*       height,
    Uint32*       width)
{
    SDL_Surface* surface;
    surface  = TTF_RenderText_Solid(font, text, color);
    *texture = SDL_CreateTextureFromSurface(renderer, surface);
    *width   = surface->w;
    *height  = surface->h;
    SDL_FreeSurface(surface);
}

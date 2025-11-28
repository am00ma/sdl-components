#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void draw_rect(SDL_Renderer* r, SDL_Rect rect, SDL_Color color);
void draw_filled(SDL_Renderer* r, SDL_Rect rect, SDL_Color color);

/* @brief Draw text and get resulting texture and bounds.
 *
 *      x, y: upper left corner.
 *      texture, rect: outputs.
 */
void draw_text( //
    SDL_Renderer* renderer,
    int           x,
    int           y,
    char*         text,
    TTF_Font*     font,
    SDL_Texture** texture,
    SDL_Rect*     rect);

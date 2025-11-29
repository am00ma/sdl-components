#pragma once

#include "sdlx/types.h" // IWYU pragma: keep

void draw_rect(SDL_Renderer* r, SDL_Rect rect, SDL_Color color);
void draw_filled(SDL_Renderer* r, SDL_Rect rect, SDL_Color color);
void draw_text(SDL_Renderer* r, FC_Font* font, char* text, SDL_Rect rect, SDL_Color bg);

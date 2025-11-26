/** @file window.h
 *  @brief Manages main SDL window, holds ref to renderer
 */
#pragma once

#include "types.h" // IWYU pragma: keep

typedef struct
{
    bool quit; ///< Flag to exit sdl loop

    SDL_Rect      bounds; ///< Dimensions of screen
    SDL_Window*   win;    ///< SDL window
    SDL_Renderer* rnd;    ///< SDL renderer

} sdlx_window_t;

int  sdlx_window_open(sdlx_window_t** wp, u32 width, u32 height);
void sdlx_window_close(sdlx_window_t* w);
void sdlx_window_dump(sdlx_window_t* w);

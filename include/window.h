/** @file window.h
 *  @brief Manages main SDL window, holds ref to renderer
 */
#pragma once

#include "types.h" // IWYU pragma: keep

typedef struct
{

    SDL_Renderer* bounds;

} sdlx_window_t;

int  sdlx_window_open(sdlx_window_t** wp);
void sdlx_window_close(sdlx_window_t* w);
void sdlx_window_dump(sdlx_window_t* w);

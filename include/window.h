/** @file window.h
 *  @brief Manages main SDL window, holds ref to renderer
 */
#pragma once

#include "component.h"

typedef struct
{
    bool quit; ///< Flag to exit sdl loop

    u32           width;  ///< Width of screen
    u32           height; ///< Height of screen
    SDL_Window*   win;    ///< SDL window
    SDL_Renderer* rnd;    ///< SDL renderer

    struct
    {
        FC_Font* normal;     ///< Font: normal style
        FC_Font* italic;     ///< Font: italic style
        FC_Font* bold;       ///< Font: bold style
        FC_Font* bolditalic; ///< Font: bold italic style

    } fonts;

    sdlx_component_t c;

    // User data to pass to components
    void* data;

} sdlx_window_t;

int  sdlx_window_init(sdlx_window_t* w, u32 width, u32 height, void* data);
void sdlx_window_destroy(sdlx_window_t* w);
void sdlx_window_dump(sdlx_window_t* w);

void sdlx_window_update(sdlx_component_t*, SDL_Event, void*);
void sdlx_window_render(sdlx_component_t* c, SDL_Renderer* r, void*);

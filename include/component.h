/** @file component.h
 *  @brief Generic component with layout, actions
 */
#pragma once

#include "style.h"

typedef struct sdlx_component_t sdlx_component_t;

typedef struct sdlx_component_t
{

    // Layout
    SDL_Rect     bounds;
    sdlx_style_t style;

    // Children
    sdlx_component_t* children;
    isize             num_children;

    // User data
    void* data;

} sdlx_component_t;

int  sdlx_component_open(sdlx_component_t** tp, SDL_Rect bounds, sdlx_style_t style);
void sdlx_component_close(sdlx_component_t* t);
void sdlx_component_dump(sdlx_component_t* t);

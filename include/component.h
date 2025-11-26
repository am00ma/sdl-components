/** @file component.h
 *  @brief Generic component with layout, actions
 */
#pragma once

#include "style.h"

typedef struct sdlx_component_t sdlx_component_t;

typedef struct sdlx_component_t
{
    // User data
    void* data;

    // Layout
    SDL_Rect     bounds;
    sdlx_style_t style;

    // Children
    sdlx_component_t* children;
    isize             num_children;

    // Focus
    bool  can_focus;
    bool  has_focus;
    isize focussed_child;

} sdlx_component_t;

void sdlx_component_init(sdlx_component_t* t, SDL_Rect bounds, sdlx_style_t style);
void sdlx_component_dump(sdlx_component_t* t);

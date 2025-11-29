/** @file component.h
 *  @brief Generic component with layout, actions
 */
#pragma once

#include "sdlx/style.h"

typedef struct sdlx_component_t sdlx_component_t;

typedef void (*UpdateCallback)(sdlx_component_t* c, SDL_Event e, void* data);
typedef void (*RenderCallback)(sdlx_component_t* c, SDL_Renderer* r, void* data);

typedef struct sdlx_component_t
{
    // Link to parent component
    void* p; ///< Parameters
    void* s; ///< State

    // Interaction
    UpdateCallback update;
    RenderCallback render;

    // Layout
    SDL_Rect     bounds;
    sdlx_style_t style;

    // Component tree
    sdlx_component_t* parent;
    sdlx_component_t* children;
    isize             num_children;

    // Focus
    bool  can_focus;
    bool  has_focus;
    isize focussed_child;

} sdlx_component_t;

void sdlx_component_init(sdlx_component_t* t, SDL_Rect bounds, sdlx_style_t style);
void sdlx_component_dump(sdlx_component_t* t);

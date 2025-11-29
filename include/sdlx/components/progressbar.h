/** @file progressbar.h
 *  @brief Progress bar with max and current value.
 */
#pragma once

#include "sdlx/component.h"

typedef struct
{
    float max;
    float min;

} sdlx_progressbar_params_t;

typedef struct
{
    float val;

} sdlx_progressbar_state_t;

typedef struct
{
    sdlx_component_t c; ///< 'Base' class

    sdlx_progressbar_params_t p; ///< Constants
    sdlx_progressbar_state_t  s; ///< Variables

} sdlx_progressbar_t;

void sdlx_progressbar_update(sdlx_component_t* c, SDL_Event e, void* data);
void sdlx_progressbar_render(sdlx_component_t* c, SDL_Renderer* r, void* data);

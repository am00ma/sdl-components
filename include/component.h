#pragma once

#include "SDL2/SDL.h"

typedef struct {

  SDL_Rect bounds;

} sdlc_component_t;

int sdlc_component_open(sdlc_component_t **tp);
int sdlc_component_close(sdlc_component_t *t);

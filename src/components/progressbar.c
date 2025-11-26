#include "components/progressbar.h"
#include "draw.h"

void sdlx_progressbar_update(sdlx_component_t*, SDL_Event, void*)
{
    // Does not respond to keys, so nop
}

void sdlx_progressbar_render(sdlx_component_t* c, SDL_Renderer* r, void*)
{
    draw_rect(r, c->bounds, c->style.background);
}

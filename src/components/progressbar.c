#include "sdlx/components/progressbar.h"
#include "sdlx/draw.h"

void sdlx_progressbar_update(sdlx_component_t* c, SDL_Event, void*)
{
    sdlx_progressbar_params_t* p = c->p;
    sdlx_progressbar_state_t*  s = c->s;

    s->val = (s->val + 1.0) > p->max ? 0.0 : (s->val + 1.0);
}

void sdlx_progressbar_render(sdlx_component_t* c, SDL_Renderer* r, void*)
{
    sdlx_progressbar_params_t* p = c->p;
    sdlx_progressbar_state_t*  s = c->s;

    u32 x, y, w, h;

    x = c->bounds.x;
    y = c->bounds.y;
    w = (float)c->bounds.w * s->val / p->max;
    h = c->bounds.h;

    draw_filled(r, (SDL_Rect){x, y, w, h}, c->style.background);
}

#include "component.h"

int sdlx_component_open(sdlx_component_t** tp, SDL_Rect bounds, sdlx_style_t style)
{
    int err;

    sdlx_component_t* t;

    t   = calloc(1, sizeof(sdlx_component_t));
    err = t == nullptr ? -ENOMEM : 0;
    Goto(err, __close, "Failed: calloc sdlx_component_t* t");

    t->bounds = bounds;
    t->style  = style;

    *tp = t;

    return 0;

__close:
    sdlx_component_close(t);
    return err;
}

void sdlx_component_close(sdlx_component_t* t)
{
    if (!t) return;
    Free(t);
}

void sdlx_component_dump(sdlx_component_t* t)
{
    p_info("  bounds (xyhw): %d, %d, %d, %d", t->bounds.x, t->bounds.y, t->bounds.h, t->bounds.w);
    p_info("  style  (bg)  : %d, %d, %d, %d", //
           t->style.background.r, t->style.background.g, t->style.background.b, t->style.background.a);
}

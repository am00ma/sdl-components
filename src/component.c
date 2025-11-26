#include "component.h"

void sdlx_component_init(sdlx_component_t* t, SDL_Rect bounds, sdlx_style_t style)
{
    t->bounds = bounds;
    t->style  = style;
}

void sdlx_component_dump(sdlx_component_t* t)
{
    p_info("  bounds (xywh): %d, %d, %d, %d", t->bounds.x, t->bounds.y, t->bounds.w, t->bounds.h);
    p_info("  style  (bg)  : %d, %d, %d, %d", //
           t->style.background.r, t->style.background.g, t->style.background.b, t->style.background.a);
}

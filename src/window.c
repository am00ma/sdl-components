#include "window.h"

int sdlx_window_init(sdlx_window_t* w, u32 width, u32 height)
{
    int err;

    w->quit   = false;
    w->bounds = (SDL_Rect){0, 0, width, height};

    err = SDL_Init(SDL_INIT_VIDEO);
    Goto(err, __close, "Failed: SDL_Init");

    SDL_ShowCursor(0);

    w->win = SDL_CreateWindow("SDLX", 100, 100, w->bounds.w, w->bounds.h, SDL_WINDOW_SHOWN);
    err    = -(!w->win);
    Goto(err, __close, "Failed: SDL_CreateWindow");

    w->rnd = SDL_CreateRenderer(w->win, -1, SDL_RENDERER_ACCELERATED);
    err    = -(!w->rnd);
    Goto(err, __close, "Failed: SDL_CreateRenderer");

    SDL_RendererInfo info;
    SDL_GetRendererInfo(w->rnd, &info);
    p_info("Renderer: %s", info.name);

    return 0;

__close:
    sdlx_window_destroy(w);
    return err;
}

void sdlx_window_destroy(sdlx_window_t* w)
{
    if (!w) return;

    if (w->rnd) SDL_DestroyRenderer(w->rnd);
    if (w->win) SDL_DestroyWindow(w->win);
    SDL_Quit();
}

void sdlx_window_dump(sdlx_window_t* w) { p_info("  size (wh): %d, %d", w->bounds.w, w->bounds.h); }

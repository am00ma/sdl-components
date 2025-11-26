#include "window.h"

int sdlx_window_open(sdlx_window_t** wp, u32 width, u32 height)
{
    int err;

    sdlx_window_t* w;
    w   = calloc(1, sizeof(sdlx_window_t));
    err = w == nullptr ? -ENOMEM : 0;
    Goto(err, __close, "Failed: calloc sdlx_window_t* t");

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

    *wp = w;

    return 0;

__close:
    sdlx_window_close(w);
    return err;
}

void sdlx_window_close(sdlx_window_t* w)
{
    if (!w) return;

    if (w->rnd) SDL_DestroyRenderer(w->rnd);
    if (w->win) SDL_DestroyWindow(w->win);
    SDL_Quit();

    Free(w);
}

void sdlx_window_dump(sdlx_window_t* w) { p_info("  size (wh): %d, %d", w->bounds.w, w->bounds.h); }

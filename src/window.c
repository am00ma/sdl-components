#include "window.h"
#include "component.h"
#include "constants.h"
#include "draw.h"
#include "style.h"
#include <SDL2/SDL_ttf.h>

int sdlx_window_init(sdlx_window_t* w, u32 width, u32 height, void* data)
{
    int err;

    w->quit   = false;
    w->width  = width;
    w->height = height;
    w->data   = data;

    err = SDL_Init(SDL_INIT_VIDEO);
    Goto(err, __close, "Failed: SDL_Init");

    SDL_ShowCursor(0);

    w->win = SDL_CreateWindow("SDLX", 100, 100, w->width, w->height, SDL_WINDOW_SHOWN);
    err    = -(!w->win);
    Goto(err, __close, "Failed: SDL_CreateWindow");

    w->rnd = SDL_CreateRenderer(w->win, -1, SDL_RENDERER_ACCELERATED);
    err    = -(!w->rnd);
    Goto(err, __close, "Failed: SDL_CreateRenderer");

    SDL_RendererInfo info;
    SDL_GetRendererInfo(w->rnd, &info);
    p_info("Renderer: %s", info.name);

    err = TTF_Init();
    Goto(err, __close, "Failed: TTF_Init");

    w->fonts.normal = TTF_OpenFont("/usr/share/fonts/TTF/IosevkaNerdFont-Medium.ttf", 24);
    err             = -(!w->fonts.normal);
    Goto(err, __close, "Failed: TTF_OpenFont: normal");

    w->fonts.italic = TTF_OpenFont("/usr/share/fonts/TTF/IosevkaNerdFont-Italic.ttf", 24);
    err             = -(!w->fonts.italic);
    Goto(err, __close, "Failed: TTF_OpenFont: italic");

    w->fonts.bold = TTF_OpenFont("/usr/share/fonts/TTF/IosevkaNerdFont-Bold.ttf", 24);
    err           = -(!w->fonts.bold);
    Goto(err, __close, "Failed: TTF_OpenFont: bold");

    w->fonts.bolditalic = TTF_OpenFont("/usr/share/fonts/TTF/IosevkaNerdFont-BoldItalic.ttf", 24);
    err                 = -(!w->fonts.bolditalic);
    Goto(err, __close, "Failed: TTF_OpenFont: bold");

    w->c = (sdlx_component_t){
        .update         = sdlx_window_update,
        .render         = sdlx_window_render,
        .bounds         = {0, 0, w->width, w->height},
        .style          = {.background = DARK_GREEN, .text = WHITE},
        .parent         = nullptr,
        .children       = nullptr,
        .num_children   = 0,
        .can_focus      = true,
        .has_focus      = true,
        .focussed_child = -1,
    };

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

    if (w->fonts.normal) TTF_CloseFont(w->fonts.normal);
    if (w->fonts.italic) TTF_CloseFont(w->fonts.italic);
    if (w->fonts.bold) TTF_CloseFont(w->fonts.bold);
    if (w->fonts.bolditalic) TTF_CloseFont(w->fonts.bolditalic);

    TTF_Quit();
    SDL_Quit();
}

void sdlx_window_dump(sdlx_window_t* w) { p_info("  size (wh): %d, %d", w->width, w->height); }

void sdlx_window_update(sdlx_component_t*, SDL_Event event, void* data)
{
    sdlx_window_t* w = data;

    switch (event.type)
    {
    case SDL_QUIT: w->quit = true; break;
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE: w->quit = true; break;
        }
    }

    if (w->c.num_children)
    {
        RANGE(i, w->c.num_children) { w->c.children[i].update(&w->c.children[i], event, w->data); }
    }
}

void sdlx_window_render(sdlx_component_t* c, SDL_Renderer* r, void* data)
{
    sdlx_window_t* w = data;

    draw_filled(r, c->bounds, c->style.background);

    if (w->c.num_children)
    {
        RANGE(i, w->c.num_children) { w->c.children[i].render(&w->c.children[i], w->rnd, w->data); }
    }
}

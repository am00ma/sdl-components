/** @file test_window.c
 *  @brief Check how long it takes window to load
 *
 *  NOTE: Takes 3.1 secs :(
 *        Apparently the delay is because of nvidia driver
 *
 */
#include "sdlx/components/progressbar.h" // sdlx_progressbar_t
#include "sdlx/constants.h"              // FPS, WIDTH, HEIGHT
#include "sdlx/window.h"

int main()
{
    int err;

    sdlx_window_t w;
    err = sdlx_window_init(&w, WIDTH, HEIGHT, 0);
    Goto(err, __close, "Failed: calloc sdlx_window_t* t");

    sdlx_progressbar_t progress = {
        .c =
            {
                .update         = sdlx_progressbar_update,
                .render         = sdlx_progressbar_render,
                .bounds         = w.c.bounds,
                .style          = {.background = DARK_RED, .text = WHITE},
                .parent         = &w.c,
                .children       = nullptr,
                .num_children   = 0,
                .can_focus      = true,
                .has_focus      = true,
                .focussed_child = -1,
            },
        .p = {.min = 0.0, .max = 100.0},
        .s = {.val = 50.0},
    };
    progress.c.p = &progress.p;
    progress.c.s = &progress.s;

    w.c.num_children = 1;
    w.c.children     = &progress.c;

    sdlx_window_dump(&w);

    u32 frame_period = (1000 / FPS);
    u32 frame_start;
    u32 frame_stop;

    while (!w.quit)
    {
        frame_start = SDL_GetTicks();

        SDL_Event event = {};

        sdlx_window_update(&w.c, event, &w); // Make sure it runs every frame

        // Actually respond to keys -> only happens on key, not on 'idle'
        while (SDL_PollEvent(&event)) { sdlx_window_update(&w.c, event, &w); }

        sdlx_window_render(&w.c, w.rnd, &w);

        SDL_RenderPresent(w.rnd);

        frame_stop = SDL_GetTicks() - frame_start;
        if (frame_stop < frame_period) SDL_Delay(frame_period - frame_stop);
    }

    sdlx_window_destroy(&w);

    return 0;

__close:
    sdlx_window_destroy(&w);
    return err;
}

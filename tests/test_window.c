/** @file test_window.c
 *  @brief Check how long it takes window to load
 *
 *  NOTE: Takes 3.1 secs :(
 *        Apparently the delay is because of nvidia driver
 *
 */
#include "sdlx/constants.h" // FPS, WIDTH, HEIGHT
#include "sdlx/draw.h"
#include "sdlx/window.h"

int main()
{
    int err;

    sdlx_window_t w;
    err = sdlx_window_init(&w, WIDTH, HEIGHT, 0);
    Goto(err, __close, "Failed: calloc sdlx_window_t* t");

    sdlx_window_dump(&w);

    u32 frame_period = (1000 / FPS);
    u32 frame_start;
    u32 frame_stop;

    while (!w.quit)
    {
        frame_start = SDL_GetTicks();

        SDL_Event event;
        while (SDL_PollEvent(&event)) { sdlx_window_update(&w.c, event, &w); }

        sdlx_window_render(&w.c, w.rnd, &w);

        draw_text(w.rnd, w.fonts.bolditalic, "hello", (SDL_Rect){100, 100, 200, 100}, WHITE);
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

/** @file test_progressbar.c
 *  @brief progressbar
 */
#include "components/progressbar.h"
#include "constants.h" // FPS, WIDTH, HEIGHT
#include "window.h"

int main()
{
    int err;

    sdlx_window_t w;
    err = sdlx_window_init(&w, WIDTH, HEIGHT);
    Goto(err, __close, "Failed: calloc sdlx_window_t* t");

    sdlx_window_dump(&w);

    u32 frame_period = (1000 / FPS);
    u32 frame_start;
    u32 frame_stop;

    while (!w.quit)
    {
        frame_start = SDL_GetTicks();

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT: w.quit = true; break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE: w.quit = true; break;
                }
            }
        }

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

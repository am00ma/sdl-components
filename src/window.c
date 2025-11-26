#include "window.h"

int sdlx_window_open(sdlx_window_t** wp)
{
    int err;

    sdlx_window_t* w;

    w   = calloc(1, sizeof(sdlx_window_t));
    err = w == nullptr ? -ENOMEM : 0;
    Goto(err, __close, "Failed: calloc sdlx_window_t* t");

    *wp = w;

    return 0;

__close:
    sdlx_window_close(w);
    return err;
}

void sdlx_window_close(sdlx_window_t* w)
{
    if (!w) return;

    Free(w);
}

void sdlx_window_dump(sdlx_window_t* w) { p_info("Window: %p", (void*)w); }

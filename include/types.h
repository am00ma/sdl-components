/** @file types.h
 *  @brief Type aliases and macros to make code readable.
 */
#pragma once

#define DEBUG

/* ---------------------------------------------------------------------------
 * Common includes
 * ------------------------------------------------------------------------- */
#include <common-types.h> // IWYU pragma: keep
#include <errno.h>        // IWYU pragma: keep

#include <SDL2/SDL.h>       // IWYU pragma: keep
#include <SDL2/SDL_image.h> // IWYU pragma: keep
#include <SDL2/SDL_ttf.h>   // IWYU pragma: keep

#include "SDL_FontCache.h" // IWYU pragma: keep

typedef enum
{

    FONT_NORMAL = 0,
    FONT_ITALIC,
    FONT_BOLD,
    FONT_BOLDITALIC,

} sdlx_fontstyle_t;

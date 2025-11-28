/** @file list.h
 *  @brief List with multiple selection.
 */
#pragma once

#include "component.h"
#include "types.h" // IWYU pragma: keep

typedef void (*sdlx_list_item_to_text_fn)( //
    void*             item,
    char*             text,
    isize*            len,
    SDL_Color*        color,
    sdlx_fontstyle_t* fontstyle);

typedef struct
{

    void* items;

    sdlx_list_item_to_text_fn item_to_text;

    SDL_Texture** textures;
    u32*          widths;
    u32*          heights;

    isize num_items;
    isize items_per_page;
    isize num_pages;

} sdlx_list_params_t;

typedef struct
{

    isize current_item;
    isize current_page;

} sdlx_list_state_t;

typedef struct
{
    sdlx_component_t c; ///< 'Base' class

    sdlx_list_params_t p; ///< Constants
    sdlx_list_state_t  s; ///< Variables

} sdlx_list_t;

int  sdlx_list_init(sdlx_list_t* li, void* items, isize num_items, isize items_per_page);
void sdlx_list_destroy(sdlx_list_t* lp);

void sdlx_list_update(sdlx_component_t* c, SDL_Event e, void* data);
void sdlx_list_render(sdlx_component_t* c, SDL_Renderer* r, void* data);

#include "components/list.h"

int sdlx_list_init(sdlx_list_t* li, void* items, isize num_items, isize items_per_page)
{

    li->p.items          = items;
    li->p.num_items      = num_items;
    li->p.items_per_page = items_per_page;

    //

    return 0;
}

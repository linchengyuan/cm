#include "mpool/mpool.h"
#include <stdlib.h>

void pool_init(mpool *pool, int item_bytes, int items_per_block, int alignment)
{
    if(alignment > sizeof(VOID*))
    {
        pool->align_bytes = alignment;
    }
    else
    {
        pool->align_bytes = sizeof(VOID*);
    }

    pool->item_bytes = ((item_bytes - 1) / pool->align_bytes + 1) * pool->align_bytes;
    pool->items_per_block = items_per_block;

    pool->first_block = (VOID**)
        malloc(pool->items_per_block * pool->item_bytes +
               sizeof(VOID*) + pool->align_bytes);
    *(pool->first_block) = NULL;
    pool_restart(pool);
}

void pool_restart(mpool *pool)
{
    unsigned long long ptr;

    pool->items = 0;
    pool->max_items = 0;

    pool->cur_block = pool->first_block;
    ptr = (unsigned long long)(pool->cur_block + 1);
    pool->next_item = (VOID*)
        (ptr + (unsigned long long)pool->align_bytes -
        (ptr % (unsigned long long)pool->align_bytes));
    pool->unallocate_items = pool->items_per_block;
    pool->dead_item_stack = NULL;
}

void pool_zero(mpool *pool)
{
    pool->first_block = NULL;
    pool->cur_block = NULL;
    pool->next_item = NULL;
    pool->dead_item_stack = NULL;
    pool->path_block = NULL;
    pool->path_item = NULL;
    pool->align_bytes = 0;
    pool->item_bytes = 0;
    pool->items_per_block = 0;
    pool->items = 0;
    pool->max_items = 0;
    pool->unallocate_items = 0;
    pool->path_item_left = 0;
}

VOID *pool_alloc(mpool *pool)
{
    VOID *res;
    VOID **newblock;
    unsigned long long ptr;

    if(pool->dead_item_stack != NULL)
    {
        res = pool->dead_item_stack;
        pool->dead_item_stack = *(VOID **)(pool->dead_item_stack);
    }
    else
    {
        if(pool->unallocate_items == 0)
        {
            if(*(pool->cur_block) == NULL)
            {
                newblock = (VOID **)
                    malloc(pool->items_per_block * pool->item_bytes +
                           sizeof(VOID *) + pool->align_bytes);
                *(pool->cur_block) = (VOID *)newblock;
                *newblock = NULL;
            }

            pool->cur_block = (VOID **)*(pool->cur_block);
            ptr = (unsigned long long)(pool->cur_block + 1);
            pool->next_item = (VOID *)
                (ptr + (unsigned long long)pool->align_bytes -
                (ptr % (unsigned long long)pool->align_bytes));
            pool->unallocate_items = pool->items_per_block;
        }

        res = pool->next_item;
        pool->next_item = (VOID *)((char *)(pool->next_item) + pool->item_bytes);
        pool->unallocate_items--;
        pool->max_items++;
    }

    pool->items++;
    return res;
}

void pool_dealloc(mpool *pool, int *item)
{
    *((VOID **)item) = pool->dead_item_stack;
    pool->dead_item_stack = item;
    pool->items--;
}

void pool_free(mpool *pool)
{
    while(pool->first_block != NULL)
    {
        pool->cur_block = (VOID **)*(pool->first_block);
        free(pool->first_block);
        pool->first_block = pool->cur_block;
    }
}

void pool_traversal_init(mpool *pool)
{
    unsigned long long ptr;

    pool->path_block = pool->first_block;
    ptr = (unsigned long long)(pool->path_block + 1);
    pool->path_item = (VOID *)
        (ptr + (unsigned long long)pool->align_bytes -
        (ptr % (unsigned long long)pool->align_bytes));
    pool->path_item_left = pool->items_per_block;
}

int *pool_traverse(mpool *pool)
{
    VOID *res;
    unsigned long long ptr;

    if(pool->path_item == pool->next_item)
    {
        return NULL;
    }

    if(pool->path_item_left == 0)
    {
        pool->path_block = (VOID **)*(pool->path_block);
        ptr = (unsigned long long)(pool->path_block + 1);
        pool->path_item = (VOID *)
            (ptr + (unsigned long long)pool->align_bytes -
            (ptr % (unsigned long long)pool->align_bytes));
        pool->path_item_left = pool->items_per_block;
    }

    res = pool->next_item;
    pool->next_item = (VOID *)((char *)pool->next_item + pool->item_bytes);
    pool->path_item_left--;
    return res;
}

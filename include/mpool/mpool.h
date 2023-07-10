#ifndef MPOOL_H
#define MPOOL_H

#include "types.h"


typedef struct mpool
{
    VOID **first_block, **cur_block;
    VOID *next_item;
    VOID *dead_item_stack;
    VOID **path_block;
    VOID *path_item;

    long long items, max_items;
    int item_bytes;
    int items_per_block;
    int align_bytes;
    int unallocate_items;
    int path_item_left;
} mpool;

void pool_zero(mpool *pool);
void pool_init(mpool *pool, int item_bytes, int items_per_block, int alignment);
VOID *pool_alloc(mpool *pool);
void pool_dealloc(mpool *pool, VOID* item);
void pool_free(mpool *pool);
void pool_restart(mpool *pool);
void pool_traversal_init(mpool *pool);
VOID *pool_traverse(mpool *pool);


#endif // MPOOL_H

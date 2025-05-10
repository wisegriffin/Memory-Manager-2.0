#include "free_list_manager.h"


static header_t *free_list[MAX_ORDER + 1] = {NULL};

header_t *get_head(size_t order)
{
    if (order > MAX_ORDER) return NULL;
    return free_list[order];
}

void set_head(header_t *block, size_t order)
{
    if (order > MAX_ORDER) return;
    free_list[order] = block;
}

header_t *get_smallest_fit(size_t size)
{
    header_t* current;
    
    for (size_t i = 0; i <= MAX_ORDER; i++)
    {
        current = get_head(i);
        if (!current) continue;
        if (size + sizeof(header_t) <= (1 << i)) return current;
    }
    
    if (!current) return NULL;
}

int remove_block(header_t *block, size_t order)
{
    if (block == NULL) return 1;
    
    header_t *current = get_head(order);
    header_t *previous = NULL;
    
    if (current == NULL) 
        return 1;
        
    while (current != NULL && current != block)
    {
        previous = current;
        current = current->next;
    }
    
    if (current != block) return 1;
    
    if (!previous)
    {
        set_head(current->next, order);
    }
    else 
    {
        previous->next = current->next;
    }
    return 0;
}

int add_block(header_t *block, size_t order)
{
    if (block == NULL) return 1;
    
    block->next = get_head(order);
    set_head(block, order);
    return 0;
}

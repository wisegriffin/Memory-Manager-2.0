#include "buddy.h"
#include "free_list_manager.h"
#include "stdint.h"

int split(header_t *father, size_t order)
{
    if (!father) return 1;
    
    if (remove_block(father, order) != 0)  return 1;
    
    uintptr_t father_addr = (uintptr_t)father;
    uintptr_t buddy_addr = father_addr ^ (1 << (order - 1));
    header_t *buddy = (header_t*)buddy_addr;
    
    father->size = (1 << (order - 1)) - sizeof(header_t);
    buddy->size = (1 << (order - 1)) - sizeof(header_t);
    
    add_block(father, order - 1);
    add_block(buddy, order - 1);
    return 0;
}

void merge(header_t *children, size_t order)
{
    uintptr_t buddy_addr = (uintptr_t)children ^ (1 << order);
    header_t* buddy = (header_t*)buddy_addr;
    
    if (remove_block(children, order) != 0) return;
    
    if (remove_block(buddy, order) != 0)
    {
        add_block(children, order);
        return;
    }
    children->size = (1 << (order + 1)) - sizeof(header_t);
    add_block(children, order + 1);
    merge(children, order + 1);
}


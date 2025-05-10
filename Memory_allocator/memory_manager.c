#include "memory_manager.h"
#include "buddy.h"
#include "header_t.h"
#include <math.h>
#include <stdio.h>

static unsigned char memory[MEMORY_SIZE];
static int initialized = 0;

void init_memory()
{
    header_t *root = (header_t *)memory;
    root->next = NULL;
    root->size = (1 << MAX_ORDER) - sizeof(header_t);
    set_head(root, MAX_ORDER);
}

void print_free_memory()
{
    
    printf("\n==| FREE MEMORY MAP |==\n\n");
    for (size_t i = 0; i <= MAX_ORDER; i++)
    {
        header_t *current = get_head(i);
        printf("Order %ld: ", i);
        while (current != NULL)
        {
            printf("Block %p ;", current);
            current = current->next;
        }
        printf("\n");
    }
    printf("\n");
}

void *m_malloc(size_t size)
{
    if (initialized == 0)
    {
        init_memory();
        initialized = 1;
    }
    
    header_t *block = get_smallest_fit(size);
    if (!block) return NULL;
    
    size_t order = log2(block->size + sizeof(header_t));
    while (size + sizeof(header_t) < block->size)
    {
        split(block, order);
        order--;
    }
    
    if (!block) return NULL;
    void *data = (void*)(block + 1);
    remove_block(block, order);
    return data;
}

void m_free(void *ptr)
{
    if (!ptr) return;
    
    header_t *block = ((header_t*)ptr) - 1;
    
    if (!block) return;
    
    size_t order = log2(block->size + sizeof(header_t));
    add_block(block, order);
    merge(block, order);
}

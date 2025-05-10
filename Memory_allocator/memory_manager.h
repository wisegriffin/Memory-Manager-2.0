#pragma once
#include "free_list_manager.h"

#define MEMORY_SIZE (1 << MAX_ORDER)

void init_memory();
void print_free_memory();
void *m_malloc(size_t size);
void m_free(void *ptr);

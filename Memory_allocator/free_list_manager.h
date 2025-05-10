#pragma once
#include "header_t.h"

#define MAX_ORDER 10

header_t *get_head(size_t order);
header_t *get_smallest_fit(size_t size);
void set_head(header_t *block, size_t order);
int remove_block(header_t *block, size_t order);
int add_block(header_t *block, size_t order);
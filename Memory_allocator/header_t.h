#pragma once
#include <stdint.h>
#include <stddef.h>

typedef struct header_t {
    struct header_t *next;
    size_t size;
} header_t;
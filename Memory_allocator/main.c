#include <stdio.h>
#include "memory_manager.h"

int main()
{
    char *palavra = m_malloc(50);
    print_free_memory();
    m_free(palavra);
    print_free_memory();
    return 0;
}
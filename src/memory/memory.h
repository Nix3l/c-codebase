#ifndef MEMORY_MANAGEMENT_H
#define MEMORY_MANAGEMENT_H

#include <stdlib.h>
#include "base.h"

// NOTE(nix3l): for now, use the std provided heap allocation functions,
// in case we want to replace with our own allocation interface
// at some point for whatever reason
#define mem_alloc(_bytes) malloc((_bytes))
#define mem_realloc(_buffer, _bytes) realloc((_buffer), (_bytes))
#define mem_free(_ptr) free((_ptr))

typedef struct {
    // amount of data reserved
    usize capacity;
    // amount of data committed, serves as the memory position
    usize size;

    void* data;

    // NOTE(nix3l): does this need to be const?
    // there isnt any situation i can think of where an arena
    // would change this variable other than at creation.
    // can always change later if needed
    const bool expandable;
} arena_s;

// create an arena with an immutable fixed size
arena_s arena_create(usize capacity);
// create an arena that expands as its contents do
arena_s arena_create_expandable(usize capacity);

void* arena_push(arena_s* arena, usize bytes);
void arena_pop(arena_s* arena, usize bytes);

// clear all the used memory in the arena. does not destroy the arena itself
void arena_clear(arena_s* arena);
// frees and destroys the arena. arena can not be used afterwards
void arena_free(arena_s* arena);

#endif

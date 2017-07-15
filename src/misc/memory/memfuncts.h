#pragma once
#include <stddef.h>
#include <stdint.h>

///Copy a memory block with length len from src to dest
void memcpy(void* src, void* dest, size_t len);

//Set a block at dest with the value val for len bytes
void memset(void* dest, uint8_t val, size_t len);

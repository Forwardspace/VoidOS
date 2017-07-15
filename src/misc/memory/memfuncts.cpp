#include "memfuncts.h"

///Copy a memory block with length len from src to dest
void memcpy(void* src, void* dest, size_t len) {
	for (size_t i = 0; i < len; i++) {
		((uint8_t*)dest)[i] = ((uint8_t*)src)[i];
	}
}

//Set a block at dest with the value val for len bytes
void memset(void* dest, uint8_t val, size_t len) {
	for (size_t i = 0; i < len; i++) {
		((uint8_t*)dest)[i] = val;
	}
}

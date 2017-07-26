#pragma once
#include <stddef.h>
#include <stdint.h>

namespace heap {
	extern uint32_t start;
	extern uint32_t end;

	void* malloc(uint16_t size);
	void* mallocPageAligned(uint32_t page_num);

	void* realloc(void* p, uint16_t size);

	void free(void* ptr);
}

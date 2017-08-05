#pragma once
#include <stddef.h>
#include <stdint.h>

namespace heap {
	extern uint32_t start;
	extern uint32_t end;

	extern uint32_t pageMemStart;
	extern uint32_t pageMemEnd;

	void init();

	void* malloc(uint16_t size);

	void* getPage();
	void* pageAlloc(uint32_t num_pages);
	void freePage(void* p);

	void* realloc(void* p, uint16_t size);

	void free(void* ptr);
}

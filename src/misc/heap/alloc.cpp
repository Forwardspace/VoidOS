#include "alloc.h"
#include "../memory/memfuncts.h"

namespace heap {
	uint32_t start = 10/*MB*/ * 1000/*kB*/ * 1000/*B*/;;
	uint32_t end = 0xFFFFFFF0;

	uint32_t mallocCounter = 0;

	//Allocate an size-sized block of memory
	void* malloc(uint16_t size) {
		mallocCounter++;
		void* addr = NULL;
		uint32_t count = 0;

		//The header is two bytes long
		uint32_t fullsize = size + 2;

		for (void* curr = (void*)start; curr < (void*)end; curr++) {
			if (*(uint16_t*)curr == 0) {
				if (addr == NULL) {
					addr = curr;
				}
				count++;
			}
			else {
				curr += *(uint16_t*)curr + 2;

				count = 0;
				addr = NULL;
			}

			if (count == fullsize) {
				if (addr != NULL) {
					*(uint16_t*)addr = size;
					addr += 2;
					break;
				}
			}
		}
		return addr;
	}

	//Allocate page_num page aligned 4096 bytes wide blocks of memory
	/* 					OUT OF ORDER
	void* mallocPageAligned(uint32_t page_num) {
		mallocCounter++;
		void* addr = NULL;
		uint32_t count = 0;

		//The header is two bytes long
		uint32_t fullsize = page_num * 4096 + 2;

		for (void* curr = (void*)start; curr < (void*)end; curr++) {
			if (*(uint16_t*)curr == 0) {
				if (addr == NULL && !((uint32_t)addr % 4098)) {
					addr = curr;
				}
				count++;
			}
			else {
				curr += *(uint16_t*)curr;

				count = 0;
				addr = NULL;
			}

			if (count == fullsize) {
				if (addr != NULL) {
					*(uint16_t*)addr = size;
					addr += 2;
					break;
				}
			}
		}
		return addr;
	}*/

	void* realloc(void* p, uint16_t size) {
		//Get the size stored in front of the data
		uint16_t p_size = *(uint16_t*)(p - 2);

		void* newptr = NULL;

		if (size < p_size) {
			//If the requested size is smaller than current
			//one, just set the size in front to be that
			*(uint16_t*)(p - 2) = size;
			return p;
		}
		else {
			newptr = malloc(size);

			if (newptr != NULL) {
				memcpy(newptr, p, p_size);
				free(p);
			}
		}

		return newptr;
	}

	void free(void* ptr) {
		if (ptr > (void*)start && ptr < (void*)end) {
			//Just fill the space with zeroes
			uint16_t size = *(uint16_t*)ptr - 2;
			memset(ptr - 2, 0, size + 2);
		}
	}
}

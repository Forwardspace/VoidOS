#include "alloc.h"
#include "../memory/memfuncts.h"
#include "../../drivers/vga/simplevga.h"
#include "../lib/vector"

extern uint32_t startprog;
extern uint32_t endprog;

namespace heap {
	uint32_t start;
	uint32_t end;

	uint32_t pageMemStart;
	uint32_t pageMemEnd;

	std::vector<uint8_t> pageVec;

	void init() {
		pageMemStart = ((uint32_t)&endprog + 0x1000) - ((uint32_t)&endprog % 0x1000); //Was: 0x1234, is: 0x2000. Was: 0x23432, is: 0x24000
		pageMemEnd = pageMemStart + 0x1000 * 0x1000; //16 megabytes
		start = pageMemEnd + 0x2;
		end = 0xFFFFFF00;

		pageVec.resize(0x1000);
		memset(pageVec.data(), 0, 0x1000);
	}

	//Allocate a size-sized block of memory
	void* malloc(uint16_t size) {
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

	void* getPage() {
		for (uint32_t i = 0; i < 0x1000/* pageVec's size */; i++) {
			if (!pageVec.data()[i]) {
				pageVec.data()[i] = 1;
				return (void*)(i * 0x1000 + pageMemStart);
			}
		}
		smpvga::print("\nCRITICAL ERROR: out of page memory, halting.\n");
		asm("cli; hlt");
	}

	void freePage(void* p) {
		pageVec.data()[(uint32_t)(p - pageMemStart) / 0x1000] = 0;
	}

	void* pageAlloc(uint32_t num_pages) {
		void* p = getPage();
		for (int i = 0; i < num_pages - 1; i++) {
			getPage();
		}
		return p;
	}

	void* realloc(void* p, uint16_t size) {
		//Get the size stored in front of the data
		volatile void* vp = p;
		volatile uint16_t p_size = *(uint16_t*)(vp - 2);

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
				//free(p);
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

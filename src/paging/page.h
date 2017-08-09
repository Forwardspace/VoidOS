#pragma once
#include <stddef.h>
#include <stdint.h>

#include "../misc/heap/alloc.h"
#include "../drivers/vga/simplevga.h"

#define PAGE_SUPERVISOR_ACCESS 0x4
#define PAGE_USER_ACCESS 0x0
#define PAGE_WRITABLE 0x2
#define PAGE_PRESENT 0x1

namespace paging {
	struct Page {
		uint32_t present    : 1;   //Present
		uint32_t rw         : 1;   //If it's writable, 1
		uint32_t user       : 1;   //If supervisor only, 0
		uint32_t accessed   : 1;   //Was it read since refresh?
		uint32_t dirty      : 1;   //Was it written to since refresh?
		uint32_t unused     : 7;   //Unused; don't touch
		uint32_t frame      : 20;  //Address >> 12
	} __attribute__((packed));

	using PageTable = Page*;

	using PageDir = PageTable*;

	//Extended page directory, has some more
	//useful information
	struct PageDirExt {
		PageDir virt;
		PageDir phys;
		PageDirExt* physAddr = this;
	} __attribute__((packed));

	void init();
	void setModeIdentity();
}

extern "C" {
	void ISR14CPP();
}

#include "page.h"
#include "../drivers/pit/pit.h"

extern "C" void setPageDir(uint32_t addr);
extern "C" void enablePaging();
extern "C" void disablePaging();

namespace paging {
	PageDirExt curr;
	PageDirExt* currptr;

	void init() {
		setModeIdentity();
	}

	void setModeIdentity() {
		disablePaging();

		PageDir dir;
		dir = (PageDir)heap::getPage();

		//Set 20 page tables
		for (int i = 0; i < 20; i++) {
			PageTable tab = (PageTable)heap::getPage();
			dir[i] = (PageTable)((uint32_t)tab | PAGE_USER_ACCESS | PAGE_WRITABLE | PAGE_PRESENT);

			for (int j = 0; j < 1024; j++) {
				tab[j] = {1, 1, 1, 0, 0, 0, (i * 0x400000 + j * 0x1000) >> 12};
			}
		}

		//The rest are not present
		for (int i = 20; i < 1024; i++) {
			dir[i] = (PageTable)(PAGE_USER_ACCESS | PAGE_WRITABLE);
		}

		curr.phys = dir;
		curr.virt = dir;

		currptr = &curr;
		setPageDir((uint32_t)curr.phys);
		enablePaging();
	}
}

extern "C" {
	void ISR14CPP() {
		smpvga::print("Page fault handler called!");
		asm("cli; hlt");
	}
}
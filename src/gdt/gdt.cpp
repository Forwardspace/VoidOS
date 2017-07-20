#include "gdt.h"

namespace gdt {
	Descriptor getDescriptor(uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
		//Taken from wiki.osdev.com, great learning resource!

		Descriptor desc;
	 
		desc.base_low = (base & 0xFFFF);
		desc.base_middle = (base >> 16) & 0xFF;
		desc.base_high = (base >> 24) & 0xFF;

		desc.limit_low = (limit & 0xFFFF);
		desc.granularity = (limit >> 16) & 0x0F;
 
		desc.granularity |= gran & 0xCF; //WAS-F0 IS-0xCF
		desc.access = access;

		return desc;
	}

	void init() {
		setDefault();
	}

	Pointer defpointer;
	GDT defgdt;

	Descriptor descriptors[5];

	void setDefault() {
		defgdt = descriptors;

		//Has to be set to size - 1,
		//because REASONS!
		defpointer.size = (sizeof(Descriptor) * 5) - 1;
		defpointer.address = (uint32_t)defgdt;

		//There has to be one null descriptor
		descriptors[0] = getDescriptor(0x0, 0x0, 0x0, 0x0);

		//Code descriptor for kernel
		descriptors[1] = getDescriptor(0x0, 0xFFFFFFFF, 0x9A, 0xCF);

		//Data desc. for kernel
		descriptors[2] = getDescriptor(0x0, 0xFFFFFFFF, 0x92, 0xCF);

		//Code desc. for user mode
		descriptors[3] = getDescriptor(0x0, 0xFFFFFFFF, 0xFA, 0xCF);

		//Data desc. for user mode
		descriptors[4] = getDescriptor(0x0, 0xFFFFFFFF, 0xF2, 0xCF);

		set(&defpointer);
	}

	void set(Pointer* p) {
		gdtSet((uint32_t)p);
	}
}
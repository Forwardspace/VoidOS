#pragma once
#include <stddef.h>
#include <stdint.h>

//NOTE: works only in 32 bit mode

extern "C" void gdtSet(uint32_t ptr);

namespace gdt {
	struct Descriptor {
   		uint16_t limit_low;           // The lower 16 bits of the limit.
   		uint16_t base_low;            // The lower 16 bits of the base.
   		uint8_t  base_middle;         // The next 8 bits of the base.
   		uint8_t  access;              // Access flags, determine what ring this segment can be used in.
  		uint8_t  granularity;
  		uint8_t  base_high;           // The last 8 bits of the base.
	} __attribute__((packed));

	struct Pointer {
		uint16_t size;
		uint32_t address;
	} __attribute__((packed));

	using GDT = Descriptor*;

	Descriptor getDescriptor(uint32_t base, uint32_t limit, uint16_t flags);
	void set(Pointer* p);
	void setDefault();
	void init();
}

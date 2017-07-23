#pragma once
#include <stddef.h>
#include <stdint.h>

extern "C" void loadIDT(uint32_t addr);

namespace idt {
	struct Attributes {
		unsigned int GateType : 4;	//Type
		unsigned int S : 1;			//Storage segment, 0 for interrupt and trap gates
		unsigned int DPL : 2;		//Privilege level (00 - just supervisor, 11 - anyone can access)
		unsigned int P : 1;			//Present - set 1 if it is present
	} __attribute__((packed));

	struct Descriptor {
		uint16_t offset_1;	//Address low bits
		uint16_t selector;	//GDT (or LDT) offset
		uint8_t zero = 0; 	//Reserved
		Attributes at;		//Attributes
		uint16_t offset_2;	//Address high bits
	} __attribute__((packed));

	enum GType {
		PModeTypeInt = 0xE,	//CPU stays in protected mode
		RModeTypeInt = 0x6,	//CPU switches to real mode

		PModeTypeTrap = 0xF,
		RModeTypeTrap = 0x7,

		//NOTE: only for task gates:
		IDTTask = 0x5
	};

	struct Pointer {
		uint16_t size; // - 1, again
		uint32_t addr;
	} __attribute__((packed));

	using IDT = Descriptor*;

	extern IDT defIDT;
	extern Pointer defP;

	extern Descriptor darray[256];

	Descriptor getDescriptor(uint32_t address, GType GateType, uint8_t privilege);
	void setDefault();
	void init();
	void remapPICs();
	void EOI(uint16_t intnum);
}

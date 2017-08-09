#include "idt.h"
#include "../misc/os_specific/oss.h"
#include "../misc/memory/memfuncts.h"

extern "C" void genericISR();
extern "C" void ISR8ASM();
extern "C" void ISR13ASM();
extern "C" void ISR1ASM();
extern "C" void ISR0ASM();
extern "C" void ISR14ASM();

#define PIC_PRIMARY_OFFSET 0x20
#define PIC_SECONDARY_OFFSET 0x28

namespace idt {
	IDT defIDT;
	Pointer defP;

	Descriptor darray[256];

	void init() {
		setDefault();
		remapPICs();
		
		asm("sti");
	}

	void setDefault() {
		defIDT = darray;

		memset(defIDT, 0x0, sizeof(Descriptor) * 256);

		defP.size = (sizeof(Descriptor) * 256) - 1;
		defP.addr = (uint32_t)defIDT;

		//Set all descriptors
		for (int i = 0; i < 256; i++) {
			switch (i) {
				case (0 + PIC_PRIMARY_OFFSET):
					defIDT[i] = getDescriptor((uint32_t)ISR0ASM, PModeTypeInt, 0);
					break;
				case (1 + PIC_PRIMARY_OFFSET):
					defIDT[i] = getDescriptor((uint32_t)ISR1ASM, PModeTypeInt, 0);
					break;
				case (8 + PIC_PRIMARY_OFFSET):
				case (8):
					defIDT[i] = getDescriptor((uint32_t)ISR8ASM, PModeTypeInt, 0);
					break;
				case (13 + PIC_PRIMARY_OFFSET):
				case (13):
					defIDT[i] = getDescriptor((uint32_t)ISR13ASM, PModeTypeInt, 0);
					break;
				case (14 + PIC_PRIMARY_OFFSET):
				case (14):
					defIDT[i] = getDescriptor((uint32_t)ISR14ASM, PModeTypeInt, 0);
					break;

				default:
					defIDT[i] = getDescriptor((uint32_t)genericISR, PModeTypeInt, 0);
			}
		}

		loadIDT((uint32_t)&defP);
	}

	Descriptor getDescriptor(uint32_t address, GType GateType, uint8_t privilege) {
		Descriptor d;

		//Low bits
		d.offset_1 = address & 0xFFFF;
		//high bits
		d.offset_2 = (address >> 16) & 0xFFFF;

		d.selector = (!privilege)? 0x8 : 0x18; //Code selector for kernel : user mode

		Attributes att;
		att.GateType = GateType;
		att.P = 1;
		att.DPL = privilege;
		att.S = (GateType != IDTTask)? 0 : 1;

		d.at = att;

		return d;
	}

	void remapPICs() {
		//Not even going to *pretend* I know the 8259 PIC specification
		//What I do know: this remaps the PIC chips' interrupts 0x20 & 0x28 ints further
		outb(0x20, 0x11);
  		outb(0xA0, 0x11);
  		outb(0x21, PIC_PRIMARY_OFFSET);	//Primary offset
  		outb(0xA1, PIC_SECONDARY_OFFSET);	//Secondary offset
  		outb(0x21, 0x04);
  		outb(0xA1, 0x02);
  		outb(0x21, 0x01);
  		outb(0xA1, 0x01);
  		outb(0x21, 0x0);
  		outb(0xA1, 0x0);
	}

	//Must be called at the end of an interrupt
	void EOI(uint16_t intnum) {
		outb(0x20,0x20);
		if (intnum >= 8) {
			 outb(0xa0,0x20);
		}
	}
}
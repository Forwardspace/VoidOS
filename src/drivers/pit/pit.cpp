#include "pit.h"
#include "../../misc/os_specific/oss.h"

#define PIT_BASE 1193180
#define PIT_COMMAND 0x43
#define PIT_TIMER1 0x40

//Interrupt 0 handler is in isrs.cpp

namespace pit {
	uint64_t timer;

	//Initializes the PIT timer, freq in hertz
	void init(uint32_t freq) {
		uint16_t divisor = PIT_BASE / freq;

		outb(PIT_COMMAND, 0x36);

		//The divisor must be split into two bytes
		uint8_t div_lower = divisor & 0xFF;
		uint8_t div_higher = (divisor >> 8) & 0xFF;

		//Send the bytes
		outb(PIT_TIMER1, div_lower);
		outb(PIT_TIMER1, div_higher);
	}
}

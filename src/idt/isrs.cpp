#include "../drivers/vga/simplevga.h"
#include "../misc/strings/stringfuncts.h"
#include "../misc/os_specific/oss.h"
#include "../drivers/pit/pit.h"
#include "../drivers/keyb/keyb.h"
#include "idt.h"

void screenCenter(int rowoff, int columnoff) {
	smpvga::terminal_row = (smpvga::HEIGHT / 2) - 1 + rowoff;
	smpvga::terminal_column = (smpvga::WIDTH / 2) - 1 + columnoff;
}

void setScreenModeError() {
	smpvga::terminal_color = smpvga::makeCol(smpvga::VGA_COLOR_WHITE, smpvga::VGA_COLOR_LIGHT_BLUE);
}

extern "C" {
	void ISR0CPP() {
		pit::timer++;
		idt::EOI(0);
	}

	void ISR1CPP() {
		uint8_t scancode = inb(0x60);
		kb::handleKeypress(scancode);
		idt::EOI(1);
	}

	void ISR8CPP(uint32_t err_code) {
		//Print some stuff
		setScreenModeError();
		screenCenter(0, -34);
		smpvga::print("AN ERROR OCCURRED. DETAILS FOLLOW:");
		screenCenter(1, -29);
		smpvga::print("Error: double fault, critical");
		screenCenter(2, -29);
		smpvga::print("Error code (hex): ");
		
		//Print error code
		char buffer[32];
		itoa(err_code, 16, buffer);

		smpvga::print(buffer);

		asm("cli; hlt");
	}

	void ISR13CPP(uint32_t err_code) {
		//Print some stuff
		setScreenModeError();
		screenCenter(0, -34);
		smpvga::print("AN ERROR OCCURRED. DETAILS FOLLOW:");
		screenCenter(1, -41);
		smpvga::print("Error: General protection fault, critical");
		screenCenter(2, -29);
		smpvga::print("Error code (hex): ");
		
		//Aaaaand, print error code
		char buffer[16];
		itoa(err_code, 16, buffer);

		smpvga::print(buffer);

		asm("cli; hlt");
	}

	void genericISRCPP() {
		smpvga::print("\nWarning: unknown interrupt called!\n");
		idt::EOI(10); //Just a random number over 8
	}
}
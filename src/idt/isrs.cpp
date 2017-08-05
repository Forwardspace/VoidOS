#include "../drivers/vga/simplevga.h"
#include "../misc/strings/stringfuncts.h"
#include "../misc/os_specific/oss.h"
#include "../misc/lib/string"
#include "../drivers/pit/pit.h"
#include "../drivers/keyb/keyb.h"
#include "idt.h"

//Just some helper functs:
inline void screenCenter(int rowoff, int columnoff) {
	smpvga::terminal_row = (smpvga::HEIGHT / 2) - 1 + rowoff;
	smpvga::terminal_column = (smpvga::WIDTH / 2) - 1 + columnoff;
}

inline void setScreenModeError() {
	smpvga::terminal_color = smpvga::makeCol(smpvga::VGA_COLOR_WHITE, smpvga::VGA_COLOR_BLUE);
	smpvga::clearScreen();
	smpvga::terminal_color = smpvga::makeCol(smpvga::VGA_COLOR_RED, smpvga::VGA_COLOR_RED);
	//It's not pretty but it works (prints error banner).
	memset(
		smpvga::terminal_const_buffer,
		smpvga::makeEntry(smpvga::terminal_color, ' '),		//Fill the buffer with spaces
		2 * smpvga::WIDTH									//An entry is 2 bytes
	);

	smpvga::terminal_column = smpvga::WIDTH / 2 - 7; //14 is the size of printed string;
	smpvga::terminal_row = 0;

	smpvga::terminal_color = smpvga::makeCol(smpvga::VGA_COLOR_WHITE, smpvga::VGA_COLOR_RED);
	smpvga::print("CRITICAL ERROR");

	smpvga::terminal_color = smpvga::makeCol(smpvga::VGA_COLOR_WHITE, smpvga::VGA_COLOR_BLUE);
}

inline void printAt(int x, int y, std::string msg) {
	smpvga::terminal_column = x - msg.length() / 2;
	smpvga::terminal_row = y;
	smpvga::print(msg.c_str());
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
		setScreenModeError();
		printAt(smpvga::WIDTH / 2, smpvga::HEIGHT / 2 - 1, "Double Fault AKA ");
		printAt(smpvga::WIDTH / 2, smpvga::HEIGHT / 2, "Check Handlers. (Not you, user. I'm talking to you, OS Developer!).");

		asm("cli; hlt");
	}

	void ISR13CPP(uint32_t err_code) {
		//Print some stuff and then print some more stuff
		//Wow, I'm a really good commenter
		setScreenModeError();
		printAt(smpvga::WIDTH / 2, smpvga::HEIGHT / 2 - 1, "General protection Fault AKA Generally your Fault");
		printAt(smpvga::WIDTH / 2, smpvga::HEIGHT / 2, "Just check for NULL pointers.");

		asm("cli; hlt");
	}

	void genericISRCPP() {
		smpvga::print("\nWarning: unknown interrupt called!\n");
		idt::EOI(10); //Just a random number over 8
	}
}
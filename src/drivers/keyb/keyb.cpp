#include "keyb.h"
#include "../vga/simplevga.h"
#include "../../misc/heap/alloc.h"
#include "../../misc/memory/memfuncts.h"

//Just a basic keyboard driver, uses one buffer, nothing special really.

//Default keymap
unsigned char kbdcro[256] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '\'', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'z', 'u', 'i', 'o', 'p', 'š', 'đ', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'č',	/* 39 */
 'ć', 'ž',   0,		/* Left shift */
 '\\', 'y', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '-',   0,				/* Right shift */
  '*', 0, /* Alt */
  ' ',	/* Space bar */
    0, /* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */

	/* SHIFT (OR CAPS LOCK) */

    0,  27, '!', '"', '#', '$', '%', '&', '/', '(',	/* 9 */
  ')', '=', '?', '*', '\b',	/* Backspace */
  '\t',			/* Tab */
  'Q', 'W', 'E', 'R',	/* 19 */
  'T', 'Z', 'U', 'I', 'O', 'P', 'Š', 'Đ', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'Č',	/* 39 */
 'Ć', 'Ž',   0,		/* Left shift */
 '\\', 'Y', 'X', 'C', 'V', 'B', 'N',			/* 49 */
  'M', ';', ':', '_',   0,				/* Right shift */
  '*', 0, /* Alt */
  ' ',	/* Space bar */
    0, /* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0	/* All other keys are undefined */
};	

namespace kb {
	volatile char* buffer;
	volatile uint32_t buff_space;	//Available
	volatile uint32_t buff_size;	//Used

	bool inputRequest = false;

	bool shift = false;
	bool caps_lock = false;

	unsigned char* activeKeymap = kbdcro;

	void init() {
		buff_size = 0;
		buff_space = 32;
		buffer = new char[32];
	}

	//Called by ISR1CPP, basically just puts the char in the buffer
	void handleKeypress(char scancode) {
		if (inputRequest) {
			char c = getKey(scancode);
			if (c != 0 && c != -128) {	//Don't know why it's -128 and not 128, but it works.
				smpvga::putChar(c);
				smpvga::moveCursor(smpvga::terminal_column, smpvga::terminal_row);

				if (buff_size < buff_space) {
					buffer[buff_size] = c;

					buff_size++;
				}
				else {
					buffer = (char*)heap::realloc((void*)buffer, buff_space + 16);
					buff_space += 16;

					buffer[buff_size] = c;

					buff_size++;
				}
			}
		}
	}

	void inputStart() {
		inputRequest = true;
	}

	void inputEnd() {
		inputRequest = false;
		memset((void*)buffer, 0, buff_space);
		buff_size = 0;
	}

	void backspace() {
		if (buff_size != 0) {
			buff_size--;
			buffer[buff_size] = ' ';

			if (smpvga::terminal_column != 0) {
				smpvga::terminal_column--;
			}
			else {
				if (smpvga::terminal_row != 0) {
					smpvga::terminal_row--;
					smpvga::terminal_column = smpvga::WIDTH - 1;
				}
			}

			smpvga::putChar(' ');

			if (smpvga::terminal_column != 0) {
				smpvga::terminal_column--;
			}
			else {
				if (smpvga::terminal_row != 0) {
					smpvga::terminal_row--;
					smpvga::terminal_column = smpvga::WIDTH - 1;
				}
			}

			smpvga::moveCursor(smpvga::terminal_column, smpvga::terminal_row);
		}
	}

	char getKey(char scancode) {
		if (scancode & 0x80) {
			//	    	      (shift)
			if ((scancode & 0x7f) == 42) {
				shift = false;
			}
			return 0;
		}
		else {
			if (scancode == 42) {
				shift = true;
				return 0;
			}
			else if (scancode == 58) {
				caps_lock = !caps_lock;
				return 0;
			}
			//		(backspace )
			else if (scancode == 14) {
				backspace();
				return 128;
			}
			else if (shift || caps_lock) {
				return activeKeymap[(uint32_t)scancode + 90];
			}
			else {
				return activeKeymap[scancode];
			}
		}
	}

	char waitForKeypress() {
		while (buff_size < 1) {}
	}

	char getc() {
		inputStart();

		waitForKeypress();

		char c = buffer[0];

		inputEnd();

		return c;
	}

	char* gets() {
		inputStart();

		while (buffer[buff_size - 1] != '\n') { if (buffer[buff_size - 1] == '\n') { break; } }

		char* str = new char[buff_size + 1];
		memcpy(str, (void*)buffer, buff_size);

		inputEnd();

		return str;
	}
}

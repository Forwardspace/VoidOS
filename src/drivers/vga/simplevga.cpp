#include "simplevga.h"

size_t simpleStrlen(const char* str) {
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

namespace smpvga {
	///Make a color from two color enums
	static inline uint8_t makeCol(color fg, color bg) {
		return fg | bg << 4;
	}

	//Make a VGA entry using a char and an already formulated color
	static inline uint16_t makeEntry(unsigned char uc, uint8_t color) {
		return (uint16_t) uc | (uint16_t) color << 8;
	}

	size_t WIDTH = 80;
	size_t HEIGHT = 25;

	size_t terminal_row = 0;
	size_t terminal_column = 0;
	uint8_t terminal_color = 7; //Color code for light-gray-on-black

	const uint16_t* terminal_const_buffer = (uint16_t*)0xB8000;
	uint16_t* terminal_buffer;

	///Convert X and Y coordinates into linear offset
	inline static size_t XYToLinear(size_t x, size_t y) {
		return (y * WIDTH) + x;
	}

	///Hmph, what could this do?
	void clearScreen() {
		for (size_t y = 0; y < HEIGHT; y++) {
			for (size_t x = 0; x < WIDTH; x++) {
				terminal_buffer[XYToLinear(x, y)] = makeEntry(' ', terminal_color);
			}
		}
	}

	///Inits the driver
	void init() {
		terminal_buffer = (uint16_t*)terminal_const_buffer;

		clearScreen();
	}

	///Prints the character at a specified location with a specified color
	void putCharAt(char c, uint8_t color, size_t x, size_t y) {
		terminal_buffer[XYToLinear(x, y)] = makeEntry(c, color);
	}

	///Prints a character and checks for row and column ends
	void putChar(char c) {
		putCharAt(c, terminal_color, terminal_column, terminal_row);

		if (++terminal_column == WIDTH) {
			terminal_column = 0;
			if (++terminal_row == HEIGHT) {
				terminal_row = 0;
			}
		}
	}

	///Prints a string with a specified length
	void printWithLen(char* str, size_t len) {
		for (size_t s = 0; s < len; s++) {
			putChar(str[s]);
		}
	}

	//Prints a string
	void print(char* str) {
		printWithLen(str, simpleStrlen(str));
	}
}

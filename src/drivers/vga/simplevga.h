#pragma once
#include <stddef.h>
#include <stdint.h>

namespace smpvga {
	//Colors!
	enum color {
		VGA_COLOR_BLACK = 0,
		VGA_COLOR_BLUE = 1,
		VGA_COLOR_GREEN = 2,
		VGA_COLOR_CYAN = 3,
		VGA_COLOR_RED = 4,
		VGA_COLOR_MAGENTA = 5,
		VGA_COLOR_BROWN = 6,
		VGA_COLOR_LIGHT_GREY = 7,
		VGA_COLOR_DARK_GREY = 8,
		VGA_COLOR_LIGHT_BLUE = 9,
		VGA_COLOR_LIGHT_GREEN = 10,
		VGA_COLOR_LIGHT_CYAN = 11,
		VGA_COLOR_LIGHT_RED = 12,
		VGA_COLOR_LIGHT_MAGENTA = 13,
		VGA_COLOR_LIGHT_BROWN = 14,
		VGA_COLOR_WHITE = 15
	};

	extern size_t WIDTH;
	extern size_t HEIGHT;

	extern size_t terminal_row;
	extern size_t terminal_column;
	extern uint8_t terminal_color;

	extern uint16_t* terminal_const_buffer;

	inline uint8_t makeCol(color fg, color bg) {
		return fg | bg << 4;
	}

	static inline uint16_t makeEntry(unsigned char uc, uint8_t color) {
		return (uint16_t) uc | (uint16_t) color << 8;
	}

	inline size_t XYToLinear(size_t x, size_t y);

	void clearScreen();

	void init();

	void moveCursor(uint32_t x, uint32_t y);

	void scrollUpLine();

	void putCharAt(char c, uint8_t color, size_t x, size_t y);

	void putChar(char c);

	void printWithLen(char* str, size_t len);

	void print(char* str);
}

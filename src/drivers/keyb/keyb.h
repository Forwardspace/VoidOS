#pragma once
#include <stddef.h>
#include <stdint.h>

namespace kb {
	extern volatile char* buffer;
	extern bool inputRequest;
	extern unsigned char* activeKeymap;

	void inputStart();
	void inputEnd();

	void init();
	char getKey(char scancode);
	void handleKeypress(char scancode);

	char getc();
	char* gets();
}

#include "../drivers/vga/simplevga.h"
#include "../drivers/pit/pit.h"
#include "../drivers/keyb/keyb.h"
#include "../gdt/gdt.h"
#include "../idt/idt.h"

#include "../misc/heap/alloc.h"

void bootUp();

/// Startup function, calls @ref bootUp to get rid of the C linkage
extern "C" {
	void startUp() {
		bootUp();
	}
}

///Initializes OS modules
void bootUp() {
	//Initialize a simple VGA driver
	smpvga::init();

	//Set up a GDT
	gdt::init();

	//Set up an IDT
	idt::init();

	//Init the PIT timer
	pit::init(50);

	//Keyboard driver
	kb::init();

	//Display a nice message
	smpvga::print("Hello, OS Developer!");

	//Just a test for the keyboard driver
	char* c = kb::gets();
	smpvga::print(c);
	heap::free(c);

	while(true) {asm("nop");}
}
#include "../drivers/vga/simplevga.h"
#include "../drivers/pit/pit.h"
#include "../gdt/gdt.h"
#include "../idt/idt.h"

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

	//Display a nice message
	smpvga::print("Hello, OS Developer!");

	while(true) {asm("nop");}
}
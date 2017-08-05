//#include "icxxabi.h"
#include "../drivers/vga/simplevga.h"
#include "../drivers/pit/pit.h"
#include "../drivers/keyb/keyb.h"
#include "../misc/heap/alloc.h"
#include "../gdt/gdt.h"
#include "../idt/idt.h"
#include "../multiboot/modload.h"

extern "C" void _init();
extern "C" void _fini();

extern "C" {
	void __cxa_atexit() {

	}
}

void bootUp(uint32_t mbinfoaddr);

///Startup function, calls bootUp to get rid of the C linkage
extern "C" {
	void startUp(uint32_t mbinfoaddr) {
		bootUp(mbinfoaddr);
	}
}

///Initializes basic OS parts
void bootUp(uint32_t mbinfoaddr) {
	heap::init();

	//Initialize a simple VGA driver
	smpvga::init();

	//Set up a GDT
	gdt::init();

	//Set up an IDT
	idt::init();

	//Init the PIT timer
	pit::init(50);

	//Mods
	mods::lookForMods(mbinfoaddr);

	//Call global constructors
	_init();

	//Keyboard
	kb::init();

	//Display a nice message
	smpvga::print("Hello, World!\n\n");

	volatile void* p1 = heap::getPage();
	volatile void* p2 = heap::getPage();
	if (p1 != p2) {
		smpvga::print("OK");
	}
	heap::freePage((void*)p1);
	p2 = heap::getPage();
	if (p1 == p2) {
		smpvga::print("\nOK");
	}

	while (true) {asm("nop");}

	//Call global destructors, just in case the
	//compiler optimizes the while (true) loop
	_fini();
}
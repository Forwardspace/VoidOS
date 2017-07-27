#include "icxxabi.h"
#include "../drivers/vga/simplevga.h"
#include "../drivers/pit/pit.h"
#include "../drivers/keyb/keyb.h"
#include "../gdt/gdt.h"
#include "../idt/idt.h"
#include "../multiboot/modload.h"

#include "../misc/lib/string"

void bootUp(uint32_t mbinfoaddr);

/// Startup function, calls bootUp to get rid of the C linkage
extern "C" {
	void startUp(uint32_t mbinfoaddr) {
		bootUp(mbinfoaddr);
	}
}

///Initializes basic OS parts
void bootUp(uint32_t mbinfoaddr) {

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

	//Keyboard
	kb::init();

	std::string s("Wow,");
	s += " is it working?!";
	smpvga::print(s.c_str());

	//Display a nice message
	smpvga::print("Hello, World!\n\n");

	while(true) {asm("nop");}
}
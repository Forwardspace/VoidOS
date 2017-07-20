#include "../drivers/vga/simplevga.h"
#include "../misc/memory/memfuncts.h"
#include "../misc/strings/stringfuncts.h"
#include "../gdt/gdt.h"

void bootUp();

/// Startup function, calls @ref bootUp to get rid of the C linkage
extern "C" {
	void startUp() {
		bootUp();
	}
}

///Initializes critical OS modules
void bootUp() {
	//Initialize a simple VGA driver
	smpvga::init();

	//Set up a GDT
	gdt::init();

	//Display a nice message
	smpvga::print("Hello, OS Developer!");
}
#include "../drivers/vga/simplevga.h"

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

	//Display a nice message
	smpvga::print("Hello, OS Developer!");
}
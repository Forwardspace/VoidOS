#pragma once
#include <stddef.h>
#include <stdint.h>

namespace mods {
	enum Content {
		PROGRAM = 0x0,
		DRIVER = 0x1,
		DATA = 0x2,
		KEYMAP = 0x3
	};

	struct Type {
		Content c : 2;
		unsigned int id : 14;
		char description[14];
	} __attribute__((packed));

	//In total, 20 bytes
	struct VoidModuleHeader {
		uint32_t signature = /* Must be */ 0xED0CDAED;
		Type t;
	} __attribute__((packed));

	extern VoidModuleHeader* vmha;
	extern void* *mod_addrs;
	extern uint32_t* mod_sizes;

	void lookForMods(uint32_t infoaddr);
}

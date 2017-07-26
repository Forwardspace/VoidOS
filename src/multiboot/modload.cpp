#include "modload.h"
#include "multiboot.h"
#include "../misc/memory/memfuncts.h"

namespace mods {
	uint32_t mods_num;
	module_t* mods;

	void* *mod_addrs = NULL;
	uint32_t* mod_sizes = NULL;

	VoidModuleHeader* vmha;

	void lookForMods(uint32_t infoaddr) {
		multiboot_info_t info = *((multiboot_info_t*)infoaddr);

		//Bit three (4th bit) indicates if there are mods-related fields
		if (info.flags & 0x8) {
			mods_num = info.mods_count;
			mods = (module_t*)info.mods_addr;
		}

		if (mods_num != 0) {
			mod_addrs = new void*[mods_num];
			mod_sizes = new uint32_t[mods_num];
			vmha = new VoidModuleHeader[mods_num];

			for (int i = 0; i < mods_num; i++) {
				mod_addrs[i] = (void*)mods[i].mod_start;
				mod_sizes[i] = mods[i].mod_end - mods[i].mod_start;
			}
		}

		//Now parse them for headers
		for (int i = 0; i < mods_num; i++) {
			void* ptr = mod_addrs[i];

 			VoidModuleHeader v = ((VoidModuleHeader*)ptr)[i];

			//Check the signature
			//A little too endian, don't you think?
			if (v.signature != 0xED0CDAED) {
				continue;
			}

			vmha[i] = v;
		}
	}
}

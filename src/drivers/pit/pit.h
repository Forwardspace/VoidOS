#pragma once
#include <stddef.h>
#include <stdint.h>

namespace pit {
	void init(uint32_t freq);

	extern uint64_t timer;
}

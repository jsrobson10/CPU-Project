
#pragma once

#include <cstdint>

namespace Clock
{
	void reg(uint64_t loc);
	uint64_t get_micros();
}


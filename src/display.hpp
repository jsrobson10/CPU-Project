
#pragma once

#include <cstdint>

namespace Display
{
	void setup(uint64_t loc, uint64_t w, uint64_t h);
	void render();
	void enable();
	void disable();
};


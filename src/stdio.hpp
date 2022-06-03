
#pragma once

#include <cstdint>

namespace Stdio
{
	void reg_in(uint64_t loc);
	void reg_out(uint64_t loc);
	void set_out(bool status);
};


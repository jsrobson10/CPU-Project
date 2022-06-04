
#pragma once

#include <cstdint>
#include <string>

namespace Instruction
{
	void init();
	void exit();
	void exit(std::string reason);
	bool is_running();
	void next();
	void cleanup();
};


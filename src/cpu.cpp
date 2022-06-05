
#include <iostream>

#include <unistd.h>

#include "display.hpp"
#include "memory.hpp"
#include "stdio.hpp"
#include "random.hpp"
#include "dynram.hpp"
#include "instruction.hpp"
#include "clock.hpp"
#include "loader.hpp"

static const uint64_t SCREEN_W = 64;
static const uint64_t SCREEN_H = 64;

static uint8_t screen_buff[SCREEN_W*SCREEN_H*3] = {0};
static bool use_screen = false;

static void set_display_mode(uint64_t loc, uint8_t val)
{
	if(val > 0)
	{
		Display::enable();
		Stdio::set_out(false);
	}

	else
	{
		Display::disable();
		Stdio::set_out(true);
	}
}

static uint8_t get_display_mode(uint64_t loc)
{
	return use_screen ? 1 : 0;
}

int main(int argc, const char** argv)
{
	Instruction::init();

	// load program
	uint64_t cpu_speed = 1000000 / std::stoul(argv[1]);
	std::string program = Loader::load(argv[2]);
	
	// program and stack memory
	Dynram::reg(Memory::Ram::GLOB, 0x4000000000000000);
	Memory::Get::reg(Memory::Ram::PROG, program.length(), (const uint8_t*)program.c_str());

	// i/o devices
	Clock::reg(Memory::Ram::IO);
	Random::reg(Memory::Ram::IO + 8, 8);
	Stdio::reg_in(Memory::Ram::IO + 16);
	Stdio::reg_out(Memory::Ram::IO + 18);
	Memory::Set::reg(Memory::Ram::IO + 19, 1, &set_display_mode);
	Memory::Get::reg(Memory::Ram::IO + 19, 1, &get_display_mode);
	Memory::Ram::reg(Memory::Ram::IO + 20, sizeof(screen_buff), screen_buff);

	Display::setup(Memory::Ram::IO + 20, SCREEN_W, SCREEN_H);
	set_display_mode(0, 0);

	// refresh screen at 60Hz
	
	uint64_t micros_d = Clock::get_micros();
	uint64_t micros_i = micros_d;

	while(Instruction::is_running())
	{
		uint64_t micros = Clock::get_micros();

		if(micros - micros_d > 16666)
		{
			micros_d += 16666;

			Display::render();
		}

		else if(micros - micros_i > 10)
		{
			micros_i += 10;

			Instruction::next();
		}

		else
		{
			usleep(1000);
		}
	}

	Display::disable();
	Instruction::cleanup();
}


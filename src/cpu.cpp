
#include <iostream>

#include <unistd.h>

#include "display.hpp"
#include "memory.hpp"
#include "stdio.hpp"
#include "random.hpp"
#include "dynram.hpp"

int main()
{
	Dynram::reg(256, 64*64*3);
	//Random::reg(256, 64*64*3);

	Display::setup(256, 64, 64);
	Display::enable();

	//Stdio::reg_in(1);
	//Stdio::reg_out(1);
	//Random::reg(2, 1);

	for(int x = 0; x < 64; x++)
	{
		for(int y = 0; y < 64; y++)
		{
			int i = x * 64 + y;

			Memory::Set::int8(256 + i*3+0, x * 4);
			Memory::Set::int8(256 + i*3+1, y * 4);
		}
	}
	
	for(;;)
	{
		Display::render();
		usleep(10000);
	}
}


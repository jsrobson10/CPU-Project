
#include <iostream>

#include <signal.h>
#include <termios.h>

#include "display.hpp"
#include "memory.hpp"

static bool enabled = false;
static uint64_t canvas_at;
static uint64_t canvas_len;
static uint64_t canvas_w;
static uint64_t canvas_h;

static void signal_handler(int i)
{
	Display::disable();

	exit(i);
}

void Display::setup(uint64_t loc, uint64_t w, uint64_t h)
{
	canvas_w = w;
	canvas_h = h;
	canvas_at = loc;
	canvas_len = w*h;

	static bool registered_signal = false;
	if(!registered_signal)
	{
		signal(SIGINT, signal_handler);

		registered_signal = true;
	}
}

void Display::enable()
{
	if(!enabled)
	{
		std::cout << "\033(B\033[m\033[H\0332J\033[3J\033[?25l";

		struct termios term;
		tcgetattr(fileno(stdin), &term);

		term.c_lflag |= ICANON;
		term.c_lflag &= ~ECHO;

		tcsetattr(fileno(stdin), 0, &term);

		enabled = true;
	}
}

void Display::disable()
{
	if(enabled)
	{
		std::cout << "\033(B\033[m\033[H\0332J\033[3J\033[?25h";
		
		struct termios term;
		tcgetattr(fileno(stdin), &term);

		term.c_lflag &= ~ICANON;
		term.c_lflag |= ECHO;

		tcsetattr(fileno(stdin), 0, &term);

		enabled = false;
	}
}

void Display::render()
{
	if(!enabled)
	{
		return;
	}
	
	std::cout << "\033[H\033(B\033[m\033";

	for(uint64_t i = 0; i < canvas_len; i++)
	{
		int r = Memory::Get::int8(canvas_at + i*3+0);
		int g = Memory::Get::int8(canvas_at + i*3+1);
		int b = Memory::Get::int8(canvas_at + i*3+2);

		if(i % canvas_w == 0)
		{
			std::cout << "\n";
		}

		std::cout << "\033[48;2;" << r << ";" << g << ";" << b << "m   ";
	}

	std::cout << "\033(B\033[m\n";
}


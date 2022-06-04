
#include <iostream>
#include <thread>
#include <mutex>

#include <unistd.h>

#include "stdio.hpp"
#include "memory.hpp"

static uint8_t queue_in[1024];
static std::mutex queue_in_mtx;
static int64_t queue_in_f = 0;
static int64_t queue_in_e = 0;
static bool do_output = true;

static void printer_setter(uint64_t at, uint8_t val)
{
	if(do_output)
	{
		std::cout.put((char)val);
	}
}

static uint8_t scanner_getter(uint64_t at)
{
	if(at == 0)
	{
		bool queue_empty;

		queue_in_mtx.lock();
		queue_empty = queue_in_f == queue_in_e;
		queue_in_mtx.unlock();
		
		return queue_empty ? 0 : 1;
	}

	else
	{
		int queue_len;
	
		queue_in_mtx.lock();
		
		while(queue_in_f == queue_in_e)
		{
			queue_in_mtx.unlock();
			usleep(1000);
			queue_in_mtx.lock();
		}

		uint8_t queue_c;
	
		queue_c = queue_in[(queue_in_f++) % sizeof(queue_in)];
		queue_in_mtx.unlock();
	
		return queue_c;
	}
}

static void scanner()
{
	int v;

	while((v = std::cin.get()) >= 0)
	{
		queue_in_mtx.lock();

		while(queue_in_e - queue_in_f >= sizeof(queue_in))
		{
			queue_in_mtx.unlock();
			usleep(1000);
			queue_in_mtx.lock();
		}

		if(queue_in_e > sizeof(queue_in) &&
			(queue_in_e % sizeof(queue_in)) -
			(queue_in_f % sizeof(queue_in)) >= 0)
		{
			queue_in_e %= sizeof(queue_in);
			queue_in_f %= sizeof(queue_in);
		}

		queue_in[(queue_in_e++) % sizeof(queue_in)] = (uint8_t)v;
		queue_in_mtx.unlock();
	}
}

void Stdio::reg_out(uint64_t loc)
{
	static bool done = false;

	if(done) return;
	done = true;

	Memory::Set::reg(loc, 1, &printer_setter);
}

void Stdio::reg_in(uint64_t loc)
{
	static bool done = false;

	if(done) return;
	done = true;
	
	Memory::Get::reg(loc, 2, &scanner_getter);

	std::thread th(scanner);

	th.detach();
}

void Stdio::set_out(bool status)
{
	do_output = status;
}



#include <sys/time.h>

#include "clock.hpp"
#include "memory.hpp"

static uint8_t time_bytes[8] = {0};
static uint64_t micros_start = 0;

uint64_t Clock::get_micros()
{
	struct timeval tv;
	gettimeofday(&tv, nullptr);

	return (uint64_t)tv.tv_sec * 1000000 + (uint64_t)tv.tv_usec;
}

static uint8_t getter(uint64_t loc)
{
	return time_bytes[loc];
}

static void setter(uint64_t loc, uint8_t val)
{
	uint64_t micros = Clock::get_micros() - micros_start;

	time_bytes[0] = micros >> 56;
	time_bytes[1] = micros >> 48;
	time_bytes[2] = micros >> 40;
	time_bytes[3] = micros >> 32;
	time_bytes[4] = micros >> 24;
	time_bytes[5] = micros >> 16;
	time_bytes[6] = micros >> 8;
	time_bytes[7] = micros;
}

void Clock::reg(uint64_t loc)
{
	micros_start = Clock::get_micros();

	Memory::Get::reg(loc, 8, &getter);
	Memory::Set::reg(loc, 8, &setter);
}


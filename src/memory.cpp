
#include <list>

#include "memory.hpp"

using namespace Memory;

struct getter
{
	uint64_t min;
	uint64_t max;
	std::function<uint8_t(uint64_t)> func;
};

struct setter
{
	uint64_t min;
	uint64_t max;
	std::function<void(uint64_t, uint8_t)> func;
};

static std::list<getter> getters;
static std::list<setter> setters;

void Get::reg(uint64_t loc, uint64_t len, std::function<uint8_t(uint64_t)> func)
{
	if(len == 0)
	{
		return;
	}

	getter g;

	g.min = loc;
	g.max = loc + len - 1;
	g.func = func;

	getters.push_back(g);
}

void Set::reg(uint64_t loc, uint64_t len, std::function<void(uint64_t, uint8_t)> func)
{
	if(len == 0)
	{
		return;
	}

	setter s;

	s.min = loc;
	s.max = loc + len - 1;
	s.func = func;

	setters.push_back(s);
}

uint8_t Get::int8(uint64_t loc)
{
	for(getter& g : getters)
	{
		if(loc >= g.min && loc <= g.max)
		{
			return g.func(loc - g.min);
		}
	}

	return 0;
}

void Set::int8(uint64_t loc, uint8_t val)
{
	for(setter& s : setters)
	{
		if(loc >= s.min && loc <= s.max)
		{
			return s.func(loc - s.min, val);
		}
	}
}

uint16_t Get::int16(uint64_t loc)
{
	return (((uint16_t)Get::int8(loc+0) << 8) ^
			((uint16_t)Get::int8(loc+1)));
}

uint32_t Get::int32(uint64_t loc)
{
	return (((uint32_t)Get::int8(loc+0) << 24) ^
			((uint32_t)Get::int8(loc+1) << 16) ^
			((uint32_t)Get::int8(loc+2) << 8) ^
			((uint32_t)Get::int8(loc+3)));
}

uint64_t Get::int64(uint64_t loc)
{
	return (((uint64_t)Get::int8(loc+0) << 56) ^
			((uint64_t)Get::int8(loc+1) << 48) ^
			((uint64_t)Get::int8(loc+2) << 40) ^
			((uint64_t)Get::int8(loc+3) << 32) ^
			((uint64_t)Get::int8(loc+4) << 24) ^
			((uint64_t)Get::int8(loc+5) << 16) ^
			((uint64_t)Get::int8(loc+6) << 8) ^
			((uint64_t)Get::int8(loc+7)));
}

float Get::intf(uint64_t loc)
{
	uint32_t v = Get::int32(loc);
	
	return *(float*)&v;
}

double Get::intd(uint64_t loc)
{
	uint64_t v = Get::int64(loc);
	
	return *(double*)&v;
}

void Set::int16(uint64_t loc, uint16_t val)
{
	Set::int8(loc+0, val >> 8);
	Set::int8(loc+1, val);
}

void Set::int32(uint64_t loc, uint32_t val)
{
	Set::int8(loc+0, val >> 24);
	Set::int8(loc+1, val >> 16);
	Set::int8(loc+2, val >> 8);
	Set::int8(loc+3, val);
}

void Set::int64(uint64_t loc, uint64_t val)
{
	Set::int8(loc+0, val >> 56);
	Set::int8(loc+1, val >> 48);
	Set::int8(loc+2, val >> 40);
	Set::int8(loc+3, val >> 32);
	Set::int8(loc+4, val >> 24);
	Set::int8(loc+5, val >> 16);
	Set::int8(loc+6, val >> 8);
	Set::int8(loc+7, val);
}

void Set::intf(uint64_t loc, float val)
{
	Set::int32(loc, *(uint32_t*)&val);
}

void Set::intd(uint64_t loc, double val)
{
	Set::int64(loc, *(uint64_t*)&val);
}

void Ram::reg(uint64_t loc, uint64_t len, uint8_t* buff)
{
	Get::reg(loc, len, [buff](uint64_t at)
	{
		return buff[at];
	});

	Set::reg(loc, len, [buff](uint64_t at, uint8_t val)
	{
		buff[at] = val;
	});
}


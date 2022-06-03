
#include <map>

#include "dynram.hpp"
#include "memory.hpp"

static std::map<uint64_t, uint8_t*> data;
static uint64_t size_chunk = 1024;
static uint64_t size_max = -1;

static uint8_t getter(uint64_t loc)
{
	uint64_t id = loc / size_chunk;
	auto item = data.find(id);

	if(item == data.end())
	{
		return 0;
	}

	else
	{
		return item->second[loc % size_chunk];
	}
}

static void setter(uint64_t loc, uint8_t val)
{
	uint64_t id = loc / size_chunk;
	auto item = data.find(id);
	uint8_t* buff;

	if(item == data.end())
	{
		buff = new uint8_t[size_chunk];
		data[id] = buff;

		for(uint64_t i = 0; i < size_chunk; i++)
		{
			buff[i] = 0;
		}
	}

	else
	{
		buff = item->second;
	}

	buff[loc % size_chunk] = val;
}

void Dynram::reg(uint64_t loc, uint64_t len)
{
	Memory::Get::reg(loc, len, &getter);
	Memory::Set::reg(loc, len, &setter);
}

void Dynram::setup(uint64_t p_size_chunk, uint64_t p_size_max)
{
	size_chunk = p_size_chunk;
	size_max = p_size_max;
}


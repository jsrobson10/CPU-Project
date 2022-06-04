
#include <unordered_map>
#include <iostream>

#include "instruction.hpp"
#include "dynram.hpp"
#include "memory.hpp"

static std::unordered_map<uint64_t, uint8_t*> data;
static uint64_t size_chunk = 1024*1024;
static uint64_t size_max = (uint64_t)1024*1024*1024*4;

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
		if(data.size() * size_chunk >= size_max)
		{
			Instruction::exit("out of memory");

			return;
		}

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
	Memory::Get::reg(loc, len, [loc](uint64_t at) {
		return getter(loc + at);
	});

	Memory::Set::reg(loc, len, [loc](uint64_t at, uint8_t val) {
		setter(loc + at, val);
	});
}

void Dynram::setup(uint64_t p_size_chunk, uint64_t p_size_max)
{
	size_chunk = p_size_chunk;
	size_max = p_size_max;
}


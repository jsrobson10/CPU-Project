
#include "random.hpp"
#include "memory.hpp"

#include <openssl/rand.h>

static uint8_t getter(uint64_t loc)
{
	uint8_t c;

	RAND_bytes(&c, 1);

	return c;
}

void Random::reg(uint64_t loc, uint64_t len)
{
	Memory::Get::reg(loc, len, &getter);
}


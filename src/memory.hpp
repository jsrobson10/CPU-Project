
#pragma once

#include <cstdint>
#include <functional>

namespace Memory
{
	namespace Set
	{
		void reg(uint64_t loc, uint64_t len, std::function<void(uint64_t, uint8_t)> func);
		void reg(uint64_t loc, uint64_t len, uint8_t* buff);

		void int8(uint64_t loc, uint8_t val);
		void int16(uint64_t loc, uint16_t val);
		void int32(uint64_t loc, uint32_t val);
		void int64(uint64_t loc, uint64_t val);
		void intf(uint64_t loc, float val);
		void intd(uint64_t loc, double val);
	};

	namespace Get
	{
		void reg(uint64_t loc, uint64_t len, std::function<uint8_t(uint64_t)> func);
		void reg(uint64_t loc, uint64_t len, const uint8_t* buff);

		uint8_t int8(uint64_t loc);
		uint16_t int16(uint64_t loc);
		uint32_t int32(uint64_t loc);
		uint64_t int64(uint64_t loc);
		float intf(uint64_t loc);
		double intd(uint64_t loc);
	};

	namespace Ram
	{
		void reg(uint64_t loc, uint64_t len, uint8_t* buff);

		const uint64_t ZERO = 0x0000000000000000;
		const uint64_t PROG = 0x4000000000000000;
		const uint64_t GLOB = 0x8000000000000000;
		const uint64_t IO   = 0xc000000000000000;
	};
};


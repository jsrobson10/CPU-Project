
#pragma once

#include <cstdint>
#include <functional>

namespace Memory
{
	namespace Set
	{
		void reg(uint64_t loc, uint64_t len, std::function<void(uint64_t, uint8_t)> func);

		void int8(uint64_t loc, uint8_t val);
		void int16(uint64_t loc, uint16_t val);
		void int32(uint64_t loc, uint32_t val);
		void int64(uint64_t loc, uint64_t val);
	};

	namespace Get
	{
		void reg(uint64_t loc, uint64_t len, std::function<uint8_t(uint64_t)> func);

		uint8_t int8(uint64_t loc);
		uint16_t int16(uint64_t loc);
		uint32_t int32(uint64_t loc);
		uint64_t int64(uint64_t loc);
	};

	namespace Ram
	{
		void init(uint64_t loc, uint64_t len, uint8_t* buff);
	};
};



#include <iostream>
#include <cmath>

#include <signal.h>

#include "instruction.hpp"
#include "memory.hpp"

using namespace Memory;

static bool running = true;
static bool waiting = false;
static uint64_t cursor = Memory::Ram::PROG;
static std::string exit_reason;
static uint64_t reg[255] = {0};

static void signal_handler(int s)
{
	if(waiting)
	{
		waiting = false;

		return;
	}

	Instruction::exit("keyboard interrupt");
}

void Instruction::init()
{
	signal(SIGINT, signal_handler);
}

void Instruction::exit()
{
	running = false;
}

void Instruction::exit(std::string reason)
{
	running = false;
	exit_reason = reason;
}

bool Instruction::is_running()
{
	return running;
}

void Instruction::cleanup()
{
	if(exit_reason.length() > 0)
	{
		std::cout << "\nExit with: " << exit_reason << std::endl;
	}
}

static uint64_t getreg(uint64_t loc)
{
	uint8_t regloc = Get::int8(cursor + loc);

	if(regloc) {
		return reg[regloc - 1];
	} else {
		return 0;
	}
}

static void setreg(uint64_t loc, uint64_t val)
{
	uint8_t regloc = Get::int8(cursor + loc);

	if(regloc) {
		reg[regloc - 1] = val;
	}
}

static bool getregb(uint64_t loc)
{
	return getreg(loc) > 0;
}

static void setregb(uint64_t loc, bool val)
{
	if(val) {
		setreg(loc, 1);
	} else {
		setreg(loc, 0);
	}
}

static double getregd(uint64_t loc)
{
	uint64_t val = getreg(loc);

	return *(double*)&val;
}

static void setregd(uint64_t loc, double val)
{
	setreg(loc, *(uint64_t*)&val);
}

static float getregf(uint64_t loc)
{
	uint32_t val = getreg(loc);

	return *(float*)&val;
}

static void setregf(uint64_t loc, float val)
{
	setreg(loc, *(uint32_t*)&val);
}

template<typename T> T safediv(T a, T b)
{
	if(b == 0)
	{
		Instruction::exit("division by zero");
	}
	
	return a / b;
}

static void inst_goto()
{
	uint64_t loc;
	
	if(getreg(0)) {
		loc = getreg(1);
	} else {
		loc = getreg(2);
	}

	setreg(3, loc + 4);

	if(loc) {
		cursor = loc;
	} else {
		cursor += 4;
	}
}

void Instruction::next()
{
	if(waiting) return;

	uint8_t inst = Get::int8(cursor++);

	//std::cout << "Inst: " << (int)inst << std::endl;

	switch(inst)
	{
		default:
			exit("invalid instruction");
			break;
		case 0:		// EXIT
			exit();
			break;
		case 1:		// BREAK
			waiting = true;
			break;
		case 2:		// GOTO
			inst_goto();
			break;
		case 3:		// EQUAL
			setregb(2, getregb(0) == getregb(1));
			cursor += 3;
			break;

		case 4:		// AND
			setregb(2, getregb(0) && getregb(1));
			cursor += 3;
			break;
		case 5:		// OR
			setregb(2, getregb(0) || getregb(1));
			cursor += 3;
			break;
		case 6:		// XOR
			setregb(2, getregb(0) != getregb(1));
			cursor += 3;
			break;
		case 7:		// NOT
			setregb(1, !getregb(0));
			cursor += 2;
			break;

		case 8:		// U-GTHAN
			setregb(2, getreg(0) > getreg(1));
			cursor += 3;
			break;
		case 9:		// GTHAN
			setregb(2, (int64_t)getreg(0) > (int64_t)getreg(1));
			cursor += 3;
			break;
		case 10:	// U-LTHAN
			setregb(2, getreg(0) < getreg(1));
			cursor += 3;
			break;
		case 11:	// LTHAN
			setregb(2, (int64_t)getreg(0) < (int64_t)getreg(1));
			cursor += 3;
			break;

		case 12:	// U-MUL
			setreg(2, getreg(0) * getreg(1));
			cursor += 3;
			break;
		case 13:	// MUL
			setreg(2, (int64_t)getreg(0) * (int64_t)getreg(1));
			cursor += 3;
			break;
		case 14:	// U-DIV
			setreg(2, safediv<uint64_t>(getreg(0), getreg(1)));
			cursor += 3;
			break;
		case 15:	// DIV
			setreg(2, safediv<int64_t>(getreg(0), getreg(1)));
			cursor += 3;
			break;

		case 16:	// ADD
			setreg(2, getreg(0) + getreg(1));
			cursor += 3;
			break;
		case 17:	// SUB
			setreg(2, getreg(0) - getreg(1));
			cursor += 3;
			break;
		case 18:	// SHIFTR
			setreg(2, getreg(0) >> (int64_t)getreg(1));
			cursor += 3;
			break;
		case 19:	// SHIFTL
			setreg(2, getreg(0) << (int64_t)getreg(1));
			cursor += 3;
			break;

		case 20:	// BIT-AND
			setreg(2, getreg(0) & getreg(1));
			cursor += 3;
			break;
		case 21:	// BIT-OR
			setreg(2, getreg(0) | getreg(1));
			cursor += 3;
			break;
		case 22:	// BIT-XOR
			setreg(2, getreg(0) ^ getreg(1));
			cursor += 3;
			break;
		case 23:	// BIT-NOT
			setreg(1, !getreg(0));
			cursor += 2;
			break;

		case 24:	// SKIP-8
			cursor += 1 + Get::int8(cursor);
			break;
		case 25:	// SKIP-16
			cursor += 2 + Get::int16(cursor);
			break;
		case 26:	// SKIP-32
			cursor += 4 + Get::int32(cursor);
			break;
		case 27:	// SKIP-64
			cursor += 8 + Get::int64(cursor);
			break;

		case 28:	// SLOAD-8
			setreg(0, Get::int8(cursor + 1));
			cursor += 2;
			break;
		case 29:	// SLOAD-16
			setreg(0, Get::int16(cursor + 1));
			cursor += 3;
			break;
		case 30:	// SLOAD-32
			setreg(0, Get::int32(cursor + 1));
			cursor += 5;
			break;
		case 31:	// SLOAD-64
			setreg(0, Get::int64(cursor + 1));
			cursor += 9;
			break;

		case 32:	// LOAD-8
			setreg(0, Get::int8(getreg(1)));
			cursor += 2;
			break;
		case 33:	// LOAD-16
			setreg(0, Get::int16(getreg(1)));
			cursor += 2;
			break;
		case 34:	// LOAD-32
			setreg(0, Get::int32(getreg(1)));
			cursor += 2;
			break;
		case 35:	// LOAD-64
			setreg(0, Get::int64(getreg(1)));
			cursor += 2;
			break;

		case 36:	// STORE-8
			Set::int8(getreg(1), getreg(0));
			cursor += 2;
			break;
		case 37:	// STORE-16
			Set::int16(getreg(1), getreg(0));
			cursor += 2;
			break;
		case 38:	// STORE-32
			Set::int32(getreg(1), getreg(0));
			cursor += 2;
			break;
		case 39:	// STORE-64
			Set::int64(getreg(1), getreg(0));
			cursor += 2;
			break;

		case 40:	// FLOAT-ADD
			setregf(2, getregf(0) + getregf(1));
			cursor += 3;
			break;
		case 41:	// FLOAT-SUB
			setregf(2, getregf(0) - getregf(1));
			cursor += 3;
			break;
		case 42:	// FLOAT-MUL
			setregf(2, getregf(0) * getregf(1));
			cursor += 3;
			break;
		case 43:	// FLOAT-DIV
			setregf(2, getregf(0) / getregf(1));
			cursor += 3;
			break;

		case 44:	// DOUBLE-ADD
			setregd(2, getregd(0) + getregd(1));
			cursor += 3;
			break;
		case 45:	// DOUBLE-SUB
			setregd(2, getregd(0) - getregd(1));
			cursor += 3;
			break;
		case 46:	// DOUBLE-MUL
			setregd(2, getregd(0) * getregd(1));
			cursor += 3;
			break;
		case 47:	// DOUBLE-DIV
			setregd(2, getregd(0) / getregd(1));
			cursor += 3;
			break;
		
		case 48:	// FLOAT-SQRT
			setregf(1, (float)std::sqrt(getregf(0)));
			cursor += 2;
			break;
		case 49:	// FLOAT-EQUAL
			setregb(2, getregf(0) == getregf(1));
			cursor += 3;
			break;
		case 50:	// FLOAT-GTHAN
			setregb(2, getregf(0) > getregf(1));
			cursor += 3;
			break;
		case 51:	// FLOAT-LTHAN
			setregb(2, getregf(0) < getregf(1));
			cursor += 3;
			break;
			
		case 52:	// DOUBLE-SQRT
			setregd(1, (float)std::sqrt(getregd(0)));
			cursor += 2;
			break;
		case 53:	// DOUBLE-EQUAL
			setregb(2, getregd(0) == getregd(1));
			cursor += 3;
			break;
		case 54:	// DOUBLE-GTHAN
			setregb(2, getregd(0) > getregd(1));
			cursor += 3;
			break;
		case 55:	// DOUBLE-LTHAN
			setregb(2, getregd(0) < getregd(1));
			cursor += 3;
			break;

		case 56:	// FLOAT-TO-UINT
			setreg(1, (uint64_t)getregf(0));
			cursor += 2;
			break;
		case 57:	// FLOAT-TO-INT
			setreg(1, (int64_t)getregf(0));
			cursor += 2;
			break;
		case 58:	// UINT-TO-FLOAT
			setregf(1, (float)getreg(0));
			cursor += 2;
			break;
		case 59:	// INT-TO-FLOAT
			setregf(1, (float)(int64_t)getreg(0));
			cursor += 2;
			break;

		case 60:	// DOUBLE-TO-UINT
			setreg(1, (uint64_t)getregd(0));
			cursor += 2;
			break;
		case 61:	// DOUBLE-TO-INT
			setreg(1, (int64_t)getregd(0));
			cursor += 2;
			break;
		case 62:	// UINT-TO-DOUBLE
			setregd(1, (double)getreg(0));
			cursor += 2;
			break;
		case 63:	// INT-TO-DOUBLE
			setregd(1, (double)(int64_t)getreg(0));
			cursor += 2;
			break;

	}
}


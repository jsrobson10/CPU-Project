
#include <iostream>

#include <signal.h>

#include "instruction.hpp"
#include "memory.hpp"

using namespace Memory;

static bool running = true;
static uint64_t cursor = Memory::Ram::PROG;
static std::string exit_reason;
static uint64_t reg[256] = {0};

static void signal_handler(int s)
{
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

static uint64_t p(bool d, uint64_t off)
{
	if(d)
	{
		return Get::int64(Get::int64(cursor + off));
	}

	else
	{
		return Get::int64(cursor + off);
	}
}

template<typename T> T safediv(T a, T b)
{
	if(b == 0)
	{
		Instruction::exit("division by zero");
	}
	
	return a / b;
}

static void inst_goto(bool d)
{
	uint64_t loc_to, loc_store;

	loc_store = p(d,24);

	if(Get::int8(p(d,0))) {
		loc_to = p(d,8);
	} else {
		loc_to = p(d,16);
	}

	if(loc_store) {
		Set::int64(loc_store, cursor + 32);
	}

	if(loc_to) {
		cursor = loc_to;
	} else {
		cursor += 32;
	}
}

void Instruction::next()
{
	uint8_t inst = Get::int8(cursor++);
	bool d = inst % 2 == 1;

//	std::cout << "inst: " << (int)inst << " (" << inst / 2 << "), double: " << d << std::endl;

	switch(inst / 2)
	{
		default:
			exit("invalid instruction");
			break;
		case 255:
			while(running) usleep(1000);
			break;
		case 0:
			exit();
			break;
		case 1:
			inst_goto(d);
			break;
		case 2:
			Set::int8(p(d,16), Get::int8(p(d,0)) + Get::int8(p(d,8)));
			cursor += 24;
			break;
		case 3:
			Set::int16(p(d,16), Get::int16(p(d,0)) + Get::int16(p(d,8)));
			cursor += 24;
			break;
		case 4:
			Set::int32(p(d,16), Get::int32(p(d,0)) + Get::int32(p(d,8)));
			cursor += 24;
			break;
		case 5:
			Set::int64(p(d,16), Get::int64(p(d,0)) + Get::int64(p(d,8)));
			cursor += 24;
			break;
		case 6:
			Set::intf(p(d,16), Get::intf(p(d,0)) + Get::intf(p(d,8)));
			cursor += 24;
			break;
		case 7:
			Set::intd(p(d,16), Get::intd(p(d,0)) + Get::intd(p(d,8)));
			cursor += 24;
			break;
		case 8:
			Set::int8(p(d,16), Get::int8(p(d,0)) - Get::int8(p(d,8)));
			cursor += 24;
			break;
		case 9:
			Set::int16(p(d,16), Get::int16(p(d,0)) - Get::int16(p(d,8)));
			cursor += 24;
			break;
		case 10:
			Set::int32(p(d,16), Get::int32(p(d,0)) - Get::int32(p(d,8)));
			cursor += 24;
			break;
		case 11:
			Set::int64(p(d,16), Get::int64(p(d,0)) - Get::int64(p(d,8)));
			cursor += 24;
			break;
		case 12:
			Set::intf(p(d,16), Get::intf(p(d,0)) - Get::intf(p(d,8)));
			cursor += 24;
			break;
		case 13:
			Set::intd(p(d,16), Get::intd(p(d,0)) - Get::intd(p(d,8)));
			cursor += 24;
			break;
		case 14:
			Set::int8(p(d,16), Get::int8(p(d,0)) * Get::int8(p(d,8)));
			cursor += 24;
			break;
		case 15:
			Set::int16(p(d,16), Get::int16(p(d,0)) * Get::int16(p(d,8)));
			cursor += 24;
			break;
		case 16:
			Set::int32(p(d,16), Get::int32(p(d,0)) * Get::int32(p(d,8)));
			cursor += 24;
			break;
		case 17:
			Set::int64(p(d,16), Get::int64(p(d,0)) * Get::int64(p(d,8)));
			cursor += 24;
			break;
		case 18:
			Set::int8(p(d,16), (int8_t)Get::int8(p(d,0)) * (int8_t)Get::int8(p(d,8)));
			cursor += 24;
			break;
		case 19:
			Set::int16(p(d,16), (int16_t)Get::int16(p(d,0)) * (int16_t)Get::int16(p(d,8)));
			cursor += 24;
			break;
		case 20:
			Set::int32(p(d,16), (int32_t)Get::int32(p(d,0)) * (int32_t)Get::int32(p(d,8)));
			cursor += 24;
			break;
		case 21:
			Set::int64(p(d,16), (int64_t)Get::int64(p(d,0)) * (int64_t)Get::int64(p(d,8)));
			cursor += 24;
			break;
		case 22:
			Set::intf(p(d,16), Get::intf(p(d,0)) * Get::intf(p(d,8)));
			cursor += 24;
			break;
		case 23:
			Set::intd(p(d,16), Get::intd(p(d,0)) * Get::intd(p(d,8)));
			cursor += 24;
			break;
		case 24:
			Set::int8(p(d,16), safediv<uint8_t>(Get::int8(p(d,0)), Get::int8(p(d,8))));
			cursor += 24;
			break;
		case 25:
			Set::int16(p(d,16), safediv<uint16_t>(Get::int16(p(d,0)), Get::int16(p(d,8))));
			cursor += 24;
			break;
		case 26:
			Set::int32(p(d,16), safediv<uint32_t>(Get::int32(p(d,0)), Get::int32(p(d,8))));
			cursor += 24;
			break;
		case 27:
			Set::int64(p(d,16), safediv<uint64_t>(Get::int64(p(d,0)), Get::int64(p(d,8))));
			cursor += 24;
			break;
		case 28:
			Set::int8(p(d,16), safediv<int8_t>(Get::int8(p(d,0)), Get::int8(p(d,8))));
			cursor += 24;
			break;
		case 29:
			Set::int16(p(d,16), safediv<int16_t>(Get::int16(p(d,0)), Get::int16(p(d,8))));
			cursor += 24;
			break;
		case 30:
			Set::int32(p(d,16), safediv<int32_t>(Get::int32(p(d,0)), Get::int32(p(d,8))));
			cursor += 24;
			break;
		case 31:
			Set::int64(p(d,16), safediv<int64_t>(Get::int64(p(d,0)), Get::int64(p(d,8))));
			cursor += 24;
			break;
		case 32:
			Set::intf(p(d,16), Get::intf(p(d,0)) / Get::intf(p(d,8)));
			cursor += 24;
			break;
		case 33:
			Set::intd(p(d,16), Get::intd(p(d,0)) / Get::intd(p(d,8)));
			cursor += 24;
			break;
		case 34:
			Set::int8(p(d,16), Get::int8(p(d,0)) & Get::int8(p(d,8)));
			cursor += 24;
			break;
		case 35:
			Set::int16(p(d,16), Get::int16(p(d,0)) & Get::int16(p(d,8)));
			cursor += 24;
			break;
		case 36:
			Set::int32(p(d,16), Get::int32(p(d,0)) & Get::int32(p(d,8)));
			cursor += 24;
			break;
		case 37:
			Set::int64(p(d,16), Get::int64(p(d,0)) & Get::int64(p(d,8)));
			cursor += 24;
			break;
		case 38:
			Set::int8(p(d,16), Get::int8(p(d,0)) | Get::int8(p(d,8)));
			cursor += 24;
			break;
		case 39:
			Set::int16(p(d,16), Get::int16(p(d,0)) | Get::int16(p(d,8)));
			cursor += 24;
			break;
		case 40:
			Set::int32(p(d,16), Get::int32(p(d,0)) | Get::int32(p(d,8)));
			cursor += 24;
			break;
		case 41:
			Set::int64(p(d,16), Get::int64(p(d,0)) | Get::int64(p(d,8)));
			cursor += 24;
			break;
		case 42:
			Set::int8(p(d,16), Get::int8(p(d,0)) ^ Get::int8(p(d,8)));
			cursor += 24;
			break;
		case 43:
			Set::int16(p(d,16), Get::int16(p(d,0)) ^ Get::int16(p(d,8)));
			cursor += 24;
			break;
		case 44:
			Set::int32(p(d,16), Get::int32(p(d,0)) ^ Get::int32(p(d,8)));
			cursor += 24;
			break;
		case 45:
			Set::int64(p(d,16), Get::int64(p(d,0)) ^ Get::int64(p(d,8)));
			cursor += 24;
			break;
		case 46:
			Set::int8(p(d,8), ~Get::int8(p(d,0)));
			cursor += 16;
			break;
		case 47:
			Set::int16(p(d,8), ~Get::int16(p(d,0)));
			cursor += 16;
			break;
		case 48:
			Set::int32(p(d,8), ~Get::int32(p(d,0)));
			cursor += 16;
			break;
		case 49:
			Set::int64(p(d,8), ~Get::int64(p(d,0)));
			cursor += 16;
			break;
		case 50:
			Set::int8(p(d,16), Get::int8(p(d,0)) << (int8_t)Get::int8(p(d,8)));
			cursor += 24;
			break;
		case 51:
			Set::int16(p(d,16), Get::int16(p(d,0)) << (int8_t)Get::int8(p(d,8)));
			cursor += 24;
			break;
		case 52:
			Set::int32(p(d,16), Get::int32(p(d,0)) << (int8_t)Get::int8(p(d,8)));
			cursor += 24;
			break;
		case 53:
			Set::int64(p(d,16), Get::int64(p(d,0)) << (int8_t)Get::int8(p(d,8)));
			cursor += 24;
			break;
		case 54:
			Set::int8(p(d,16), Get::int8(p(d,0)) >> (int8_t)Get::int8(p(d,8)));
			cursor += 24;
			break;
		case 55:
			Set::int16(p(d,16), Get::int16(p(d,0)) >> (int8_t)Get::int8(p(d,8)));
			cursor += 24;
			break;
		case 56:
			Set::int32(p(d,16), Get::int32(p(d,0)) >> (int8_t)Get::int8(p(d,8)));
			cursor += 24;
			break;
		case 57:
			Set::int64(p(d,16), Get::int64(p(d,0)) >> (int8_t)Get::int8(p(d,8)));
			cursor += 24;
			break;
		case 58:
			Set::int8(p(d,16), (Get::int8(p(d,0)) > 0 && Get::int8(p(d,8)) > 0) ? 1 : 0);
			cursor += 24;
			break;
		case 59:
			Set::int8(p(d,16), (Get::int8(p(d,0)) > 0 || Get::int8(p(d,8)) > 0) ? 1 : 0);
			cursor += 24;
			break;
		case 60:
			Set::int8(p(d,16), ((Get::int8(p(d,0)) > 0) != (Get::int8(p(d,8)) > 0)) ? 1 : 0);
			cursor += 24;
			break;
		case 61:
			Set::int8(p(d,8), Get::int8(p(d,0)) == 0 ? 1 : 0);
			cursor += 16;
			break;
		case 62:
			Set::int8(p(d,16), (Get::int8(p(d,0)) == Get::int8(p(d,8))) ? 1 : 0);
			cursor += 24;
			break;
		case 63:
			Set::int8(p(d,16), (Get::int16(p(d,0)) == Get::int16(p(d,8))) ? 1 : 0);
			cursor += 24;
			break;
		case 64:
			Set::int8(p(d,16), (Get::int32(p(d,0)) == Get::int32(p(d,8))) ? 1 : 0);
			cursor += 24;
			break;
		case 65:
			Set::int8(p(d,16), (Get::int64(p(d,0)) == Get::int64(p(d,8))) ? 1 : 0);
			cursor += 24;
			break;
		case 66:
			Set::int8(p(d,16), (Get::intf(p(d,0)) == Get::intf(p(d,8))) ? 1 : 0);
			cursor += 24;
			break;
		case 67:
			Set::int8(p(d,16), (Get::intd(p(d,0)) == Get::intd(p(d,8))) ? 1 : 0);
			cursor += 24;
			break;
		case 68:
			Set::int8(p(d,16), (Get::int8(p(d,0)) > Get::int8(p(d,8))) ? 1 : 0);
			cursor += 24;
			break;
		case 69:
			Set::int8(p(d,16), (Get::int16(p(d,0)) > Get::int16(p(d,8))) ? 1 : 0);
			cursor += 24;
			break;
		case 70:
			Set::int8(p(d,16), (Get::int32(p(d,0)) > Get::int32(p(d,8))) ? 1 : 0);
			cursor += 24;
			break;
		case 71:
			Set::int8(p(d,16), (Get::int64(p(d,0)) > Get::int64(p(d,8))) ? 1 : 0);
			cursor += 24;
			break;
		case 72:
			Set::int8(p(d,16), ((int8_t)Get::int8(p(d,0)) > (int8_t)Get::int8(p(d,8))) ? 1 : 0);
			cursor += 24;
			break;
		case 73:
			Set::int8(p(d,16), ((int16_t)Get::int16(p(d,0)) > (int16_t)Get::int16(p(d,8))) ? 1 : 0);
			cursor += 24;
			break;
		case 74:
			Set::int8(p(d,16), ((int32_t)Get::int32(p(d,0)) > (int32_t)Get::int32(p(d,8))) ? 1 : 0);
			cursor += 24;
			break;
		case 75:
			Set::int8(p(d,16), ((int64_t)Get::int64(p(d,0)) > (int64_t)Get::int64(p(d,8))) ? 1 : 0);
			cursor += 24;
			break;
		case 76:
			Set::int8(p(d,16), (Get::intf(p(d,0)) > Get::intf(p(d,8))) ? 1 : 0);
			cursor += 24;
			break;
		case 77:
			Set::int8(p(d,16), (Get::intd(p(d,0)) > Get::intd(p(d,8))) ? 1 : 0);
			cursor += 24;
			break;
		case 78:
			Set::int8(p(d,16), (Get::int8(p(d,0)) < Get::int8(p(d,8))) ? 1 : 0);
			cursor += 24;
			break;
		case 79:
			Set::int8(p(d,16), (Get::int16(p(d,0)) < Get::int16(p(d,8))) ? 1 : 0);
			cursor += 24;
			break;
		case 80:
			Set::int8(p(d,16), (Get::int32(p(d,0)) < Get::int32(p(d,8))) ? 1 : 0);
			cursor += 24;
			break;
		case 81:
			Set::int8(p(d,16), (Get::int64(p(d,0)) < Get::int64(p(d,8))) ? 1 : 0);
			cursor += 24;
			break;
		case 82:
			Set::int8(p(d,16), ((int8_t)Get::int8(p(d,0)) < (int8_t)Get::int8(p(d,8))) ? 1 : 0);
			cursor += 24;
			break;
		case 83:
			Set::int8(p(d,16), ((int16_t)Get::int16(p(d,0)) < (int16_t)Get::int16(p(d,8))) ? 1 : 0);
			cursor += 24;
			break;
		case 84:
			Set::int8(p(d,16), ((int32_t)Get::int32(p(d,0)) < (int32_t)Get::int32(p(d,8))) ? 1 : 0);
			cursor += 24;
			break;
		case 85:
			Set::int8(p(d,16), ((int64_t)Get::int64(p(d,0)) < (int64_t)Get::int64(p(d,8))) ? 1 : 0);
			cursor += 24;
			break;
		case 86:
			Set::int8(p(d,16), (Get::intf(p(d,0)) < Get::intf(p(d,8))) ? 1 : 0);
			cursor += 24;
			break;
		case 87:
			Set::int8(p(d,16), (Get::intd(p(d,0)) < Get::intd(p(d,8))) ? 1 : 0);
			cursor += 24;
			break;
		case 88:
			cursor += Get::int8(cursor) + 1;
			break;
		case 89:
			cursor += Get::int16(cursor) + 2;
			break;
		case 90:
			cursor += Get::int32(cursor) + 4;
			break;
		case 91:
			cursor += Get::int64(cursor) + 8;
			break;
			
	}
}


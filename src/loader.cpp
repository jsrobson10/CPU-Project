
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>

#include "loader.hpp"

std::string Loader::load(std::string filename)
{
	std::ifstream in(filename, std::ios::binary);
	std::stringstream ss;

	char buff[1024];
	uint64_t rlen = 1;

	while(rlen)
	{
		in.read(buff, sizeof(buff));
		rlen = in.gcount();

		ss.write(buff, rlen);
	}

	in.close();

	return ss.str();
}


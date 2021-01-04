#include "utility.h"

std::string Util::toLower(const std::string& str)
{
	std::string data = str;
	std::transform(data.begin(), data.end(), data.begin(),
		[](unsigned char c) { return std::tolower(c); });

	return data;
}
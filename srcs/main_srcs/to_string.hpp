#ifndef TO_STRING_HPP
#define TO_STRING_HPP

#include <iostream>
#include <string>

namespace utils {

std::string to_string(int n)
{
	char buffer [12];
	std::string str;

	sprintf(buffer, "%d", n);
	str = buffer;
	return (str);
}

std::string to_string(double n)
{
	char buffer [12];
	std::string str;

	sprintf(buffer, "%f", n);
	str = buffer;
	return (str);
}

std::string to_string(float n)
{
	char buffer [12];
	std::string str;

	sprintf(buffer, "%f", n);
	str = buffer;
	return (str);
}

}

#endif
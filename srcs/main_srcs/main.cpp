// #include "List.hpp"
// #include "Map.hpp"
// #include "Queue.hpp"
// #include "Stack.hpp"
// #include "Vector.hpp"
#include <list>
#include <string>
#include <vector>
#include <iostream>

void test_lists(void);
void test_vector(void);
void	test_map();
void test_queue(void);
void test_stack(void);


void	header(std::string str, std::ostream& output)
{
	std::string tmp(14 + str.length(), '=');
	output << "\t\t" << tmp << std::endl;
	output << "\t\t====== " << str << " ======" << std::endl;
	output << "\t\t" << tmp << std::endl;
}

bool single_digit (const int& value) { return (value<10); }
bool mycomparison (double first, double second)
{ return ( int(first)<int(second) ); }

int main(void)
{
	test_vector();
	test_lists();
	test_map();
	test_queue();
	test_stack();
	std::cout << "\n\n\033[31mTest programm ended\033[0m\n\n";
	return (0);
}
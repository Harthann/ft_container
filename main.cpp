#include "List.hpp"
// #include "Map.hpp"
// #include "Queue.hpp"
// #include "Stack.hpp"
// #include "Vector.hpp"
#include <list>
#include <iostream>

int main(void)
{
	List<int> test;
	std::list<int> test2;

	test.push_front(50);
	test.push_front(45);
	test.push_back(2);
	test.push_back(445);
	test.push_back(56);
	test.push_back(4);
	test.print();


	test2.push_front(50);
	test2.push_front(45);
	test2.push_back(2);
	test2.push_back(445);
	test2.push_back(56);
	test2.push_back(4);
	for (std::list<int>::iterator it = test2.begin(); it != test2.end(); it++)
		std::cout << *it << " --> ";
	std::cout << "\n";
	// List<int>::iterator it;
	// it = test.begin();
	// std::cout << it->data << std::endl;
	// std::cout << test.size() << std::endl;
	// for (std::list<int>::iterator it = test.begin(); it != test.end(); it++)
	// 	std::cout << *it << " -> ";
	// std::cout << std::endl;
	// test.sort();
	// for (std::list<int>::iterator it = test.begin(); it != test.end(); it++)
	// 	std::cout << *it << " -> ";
	// std::cout << "NULL" << std::endl;

	// for(int value : test)
	// 	std::cout << value << " -> ";

	return (0);
}
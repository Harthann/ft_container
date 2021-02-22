#include <iostream>
#include <map>
#include "Map.hpp"


void	test_map()
{
	std::map<char,int> stl;
	ft::map<char, int> ft;

	stl['b'] = 100;
	stl['a'] = 200;
	stl['c'] = 300;

	// show content:
	// for (std::map<char,int>::iterator it=stl.begin(); it!=stl.end(); ++it)
  	// {
	// 	std::cout << it->first << " => " << it->second << '\n';
	// 	std::cout << (*it).first << " => " << (*it).second << '\n';
	// }
	ft.insert(std::pair<char, int> ('f', 200));
	// ft::map<char, int>::iterator it = ft.begin();
	// std::cout << it->first << " => " << it->second << std::endl;

	ft.insert(std::pair<char, int> ('a', 100));
	ft.insert(std::pair<char, int> ('i', 700));
	ft.insert(std::pair<char, int> ('c', 300));
	ft.insert(std::pair<char, int> ('e', 300));

	ft.print();
	// std::cout << "ft  : " << ft.max_size() << std::endl;
	// std::cout << "stl : " << stl.max_size() << std::endl;
}
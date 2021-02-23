#include <iostream>
#include <map>
#include "Map.hpp"


void	test_map()
{
	std::map<char,int> stl;
	ft::map<char, int> ft;

	stl['f'] = 200;
	stl['a'] = 100;
	stl['i'] = 700;
	stl['c'] = 300;
	stl['e'] = 300;
	stl['w'] = 400;
	stl['q'] = 400;
	stl['g'] = 400;
	stl['u'] = 400;
	stl['l'] = 400;

	// show content:
	std::cout << "STL:\n";
	for (std::map<char,int>::iterator it=stl.begin(); it!=stl.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	std::map<char, int>::iterator start = ft::next(stl.begin(), 2);
	std::map<char, int>::iterator end = ft::prev(stl.end(), 2);
	std::cout << "\n\n";
	std::cout << start->first << " => " << start->second << '\n';
	stl.erase(start);
	std::cout << ft::next(start)->first << " => " << ft::next(start)->second << '\n';

	// std::cout << end->first << " => " << end->second << '\n';

	// stl.erase(start, end);

	// for (std::map<char,int>::iterator it=stl.begin(); it!=stl.end(); ++it)
	// 	std::cout << it->first << " => " << it->second << '\n';
	// // ft::map<char, int>::iterator it = ft.begin();
	// // std::cout << it->first << " => " << it->second << std::endl;

	ft.insert(std::pair<char, int> ('f', 200));
	ft.insert(std::pair<char, int> ('a', 100));
	ft.insert(std::pair<char, int> ('i', 700));
	ft.insert(std::pair<char, int> ('c', 300));
	ft.insert(std::pair<char, int> ('e', 300));

	// std::cout << "begin : " << ft.begin()->first << " end : " << ft::prev(ft.end())->first << std::endl;
	// std::cout << "FT:\n";
	for (ft::map<char,int>::iterator it=ft.begin(); it!=ft.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	std::cout << std::endl;
	ft.erase('e');
	for (ft::map<char,int>::iterator it=ft.begin(); it!=ft.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	// std::cout << "past the end : " << ft::next(stl.end())->first << std::endl;
	// ft.print();
	// std::cout << "ft  : " << ft.max_size() << std::endl;
	// std::cout << "stl : " << stl.max_size() << std::endl;
}
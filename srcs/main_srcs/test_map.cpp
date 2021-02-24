#include <iostream>
#include <map>
#include "Map.hpp"
#include "utils.hpp"

template <class T>
void	insertion_tests(T &map, std::ostream& output)
{
	header("INSERTION", output);
	output << "\n\t\t== INSERTION USING INSERT METHOD ==\n";
	map.insert(std::pair<char, int> ('f', 200));
	map.insert(std::pair<char, int> ('a', 100));
	map.insert(std::pair<char, int> ('i', 700));
	map.insert(std::pair<char, int> ('c', 300));
	map.insert(std::pair<char, int> ('e', 300));
	map.insert(std::pair<char, int> ('e', 300));
	map.insert(std::pair<char, int> ('q', 300));
	map.insert(std::pair<char, int> ('h', 300));
	map.insert(std::pair<char, int> ('j', 300));
	map.insert(std::pair<char, int> ('r', 300));

	for (typename T::iterator it(map.begin()); it!=map.end(); ++it)
		output << it->first << " => " << it->second << ((it != ft::prev(map.end())) ? " | " : "\n");
	output << "\t\t== ERASE ELEMENT E ==\n";
	map.erase('e');
	for (typename T::iterator it(map.begin()); it!=map.end(); ++it)
		output << it->first << " => " << it->second << ((it != ft::prev(map.end())) ? " | " : "\n");
	output << "\t\t== ERASE ELEMENT J BASE ON POS ==\n";
	map.erase(map.find('j'));
	for (typename T::iterator it(map.begin()); it!=map.end(); ++it)
		output << it->first << " => " << it->second << ((it != ft::prev(map.end())) ? " | " : "\n");
	// typename T::iterator it = map.find('c');
	// output << it->first << " => " << it->second << "\n";
	// output << std::endl;
	
}


void	test_map()
{
	std::map<char,int> stl;
	ft::map<char, int> ft;

	// stl['f'] = 200;
	// stl['a'] = 100;
	// stl['i'] = 700;
	// stl['c'] = 300;
	// stl['e'] = 300;
	// stl['w'] = 400;
	// stl['q'] = 400;
	// stl['g'] = 400;
	// stl['u'] = 400;
	// stl['l'] = 400;

	// show content:
	insertion_tests(stl, std::cout);
	insertion_tests(ft, std::cout);
	// std::cout << ft::map<char,int>::value_compare()(*ft.begin(), *(ft::prev(ft.end())));
	// const ft::map<char, int> ft2(ft);
	// ft::map<char, int>::const_iterator it = ft2.begin();
}
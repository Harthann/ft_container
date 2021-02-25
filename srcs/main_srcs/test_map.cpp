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
	map.insert(std::pair<char, int> ('e', 600));
	map.insert(std::pair<char, int> ('e', 0));
	map.insert(std::pair<char, int> ('q', 3346));
	map.insert(std::pair<char, int> ('h', 3674));
	map.insert(std::pair<char, int> ('j', 396));
	map.insert(std::pair<char, int> ('r', 42));

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
	output << "\t\t== ACCESS C THROUGH ITERATOR GAIN VIA FIND ==\n";
	typename T::iterator it = map.find('c');
	output << it->first << " => " << it->second << "\n";
	output << std::endl;
	output << "\t\t== INSERTING AND MODIFYING VALUE THROUG OPERATOR[] ==\n";
	map['l'] = 564378;
	map['s'] = 4378;
	map['u'] = 568;
	map['e'] = -4;
	map['r'] = 21;
	map['f'] = 67;
	for (typename T::iterator it(map.begin()); it!=map.end(); ++it)
		output << it->first << " => " << it->second << ((it != ft::prev(map.end())) ? " | " : "\n");
	output << "\t\t== CAPACITY CHECK ==\n";
	output << "Is container empty ? " << map.empty() << std::endl;
	output << "Map has " << map.size() << " keys\n";
	output << "Map max capacity is : " << map.max_size() << std::endl;
	map.clear();
	for (typename T::iterator it(map.begin()); it!=map.end(); ++it)
		output << it->first << " => " << it->second << ((it != ft::prev(map.end())) ? " | " : "\n");
	
}


void	test_map()
{
	std::map<char,int> stl;
	ft::map<char, int> ft;

	// show content:
	insertion_tests(stl, std::cout);
	insertion_tests(ft, std::cout);

}
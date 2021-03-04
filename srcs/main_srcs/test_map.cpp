#include <iostream>
#include <map>
#include "Map.hpp"
#include "utils.hpp"

template <class T>
void	insertion_tests(T &map, std::ostream& output)
{
	T map_cpy;
	typename T::iterator start;
	typename T::iterator end;
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
	// for (typename T::reverse_iterator it(map.rbegin()); it!=map.rend(); ++it) {
	// 	output << it->first << " => " << it->second << std::endl;
	// }
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
	output << "\t\t== ASSIGN MAP INTO MAP_CPY ==\n";
	map_cpy = map;
	output << "Map contains :\n\t";
	for (typename T::iterator it(map.begin()); it!=map.end(); ++it)
		output << it->first << " => " << it->second << ((it != ft::prev(map.end())) ? " | " : "\n");
	output << "Map_cpy contains :\n\t";
	for (typename T::iterator it(map_cpy.begin()); it!=map_cpy.end(); ++it)
		output << it->first << " => " << it->second << ((it != ft::prev(map_cpy.end())) ? " | " : "\n");
	output << "\t\t== CLEARING MAP ==\n";
	output << "Map contains :\n\t";
	for (typename T::iterator it(map.begin()); it!=map.end(); ++it)
		output << it->first << " => " << it->second << ((it != ft::prev(map.end())) ? " | " : "\n");
	map.clear();
	output << "Map contains :\n\t";
	for (typename T::iterator it(map.begin()); it!=map.end(); ++it)
		output << it->first << " => " << it->second << ((it != ft::prev(map.end())) ? " | " : "\n");
	output << "Map_cpy contains :\n\t";
	for (typename T::iterator it(map_cpy.begin()); it!=map_cpy.end(); ++it)
		output << it->first << " => " << it->second << ((it != ft::prev(map_cpy.end())) ? " | " : "\n");
	output << "\t\t== ERASE HEAD ELEMENT IN MAP_CPY ==\n";
	map_cpy.erase('f');
	output << "\t\t== INSERTING ELEMENT FROM MAP_CPY TO MAP USING RANGE INSERT ==\n";
	map.insert(ft::next(map_cpy.begin(), 4), ft::prev(map_cpy.end(), 3));
	output << "Map contains :\n\t";
	for (typename T::iterator it(map.begin()); it!=map.end(); ++it)
		output << it->first << " => " << it->second << ((it != ft::prev(map.end())) ? " | " : "\n");
	output << "Map_cpy contains :\n\t";
	for (typename T::iterator it(map_cpy.begin()); it!=map_cpy.end(); ++it)
		output << it->first << " => " << it->second << ((it != ft::prev(map_cpy.end())) ? " | " : "\n");
	output << "\t\t== LOOKING FOR BOUND OF D ==\n";
	start = map_cpy.lower_bound('d');
	end = map_cpy.upper_bound('q');
	output << "Lower bound is : " << start->first << std::endl;
	output << "Upper bound is : " << end->first << std::endl;
	output << "\t\t== ERASING ELEMENT FROM LOWER_BOUND TO UPPER_BOUND IN MAP_CPY ==\n";
	map_cpy.erase(start, end);
	output << "Map_cpy contains :\n\t";
	for (typename T::iterator it(map_cpy.begin()); it!=map_cpy.end(); ++it)
		output << it->first << " => " << it->second << ((it != ft::prev(map_cpy.end())) ? " | " : "\n");
	output << "\t\t== SWAP MAP AND MAP_CPY ==\n";
	map.swap(map_cpy);
	output << "Map contains :\n\t";
	for (typename T::iterator it(map.begin()); it!=map.end(); ++it)
		output << it->first << " => " << it->second << ((it != ft::prev(map.end())) ? " | " : "\n");
	output << "Map_cpy contains :\n\t";
	for (typename T::iterator it(map_cpy.begin()); it!=map_cpy.end(); ++it)
		output << it->first << " => " << it->second << ((it != ft::prev(map_cpy.end())) ? " | " : "\n");
}

void	test_map()
{
	std::map<char,int> stl;
	ft::map<char, int> ft;


	std::ofstream stl_output;
	std::ofstream ft_output;

	stl_output.open(MAP_STL_OUTPUT);
	ft_output.open(MAP_FT_OUTPUT);

	insertion_tests(stl, stl_output);
	insertion_tests(ft, ft_output);

	for (ft::map<char, int>::const_iterator cit = ft.begin(); cit != ft.end(); ++cit)
		std::cout << cit->first << " => " << cit->second << ((cit != ft::prev(ft.end())) ? " | " : "\n");
	// cit = ft.begin();
	// cit->second = 900;
}
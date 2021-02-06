// // #include "List.hpp"
// #include <list>
// #include <string>
// #include <vector>
// #include <iostream>
// #include <fstream>

// template <class T>
// void init_list(T *test)
// {
// 	test->push_front(50);
// 	test->push_front(45);
// 	test->push_back(2);
// 	test->push_back(445);
// 	test->push_back(56);
// 	test->push_back(4);
// 	test->push_back(2);
// 	test->push_back(999);
// 	test->push_back(453456);
// }

// template <class T>
// std::string print_list(T start, T end, const std::string str)
// {
// 	// std::ofstream os;
// 	std::string tmp(str);

// 	// os << str;
// 	while (start != end)
// 	{
// 		tmp.append(std::to_string(*start));
// 		start++;
// 		if (start != end)
// 			tmp.append(" --> ");
// 	}
// 	tmp.append("\n");
// 	return (tmp);
// }

// template < class T>
// std::string test_const(T it, const std::string str)
// {
// 	// std::ofstream os;
// 	std::string tmp(str);
// 	tmp.append("\n\tValue of *it : ");
// 	tmp.append(std::to_string(*it));
// 	tmp.append("\n");
// 	// os << str << std::endl;
// 	// os << "\tValue of *it : " << *it << std::endl;
// 	*it = 0;
// 	// os << "\tModified value of *it : " << *it << std::endl;
// 	tmp.append("\tModified value of *it : ");
// 	tmp.append(std::to_string(*it));
// 	tmp.append("\n");
// 	return (tmp);
// }

// void test_lists(void)
// {
// 	std::ofstream myfile ("list_output", std::ios::out | std::ios::ate);

// 	ft::List<int> my_list;
// 	std::list<int> real_list;

// 	init_list(&real_list);
// 	init_list(&my_list);

// 	myfile << print_list(real_list.begin(), real_list.end(), "STL : ");
// 	myfile << print_list(my_list.begin(), my_list.end(), "ft : ");

// 	myfile << test_const(real_list.begin(), "STL : ");
// 	myfile << test_const(my_list.begin(), "ft : ");

// 	std::list<int>::const_iterator it_start = real_list.begin();
// 	std::list<int>::const_iterator it_end = real_list.end();
// 	// ft::List<int>::const_iterator i_start = my_list.begin();
// 	// ft::List<int>::const_iterator i_end = my_list.end();
// 	print_list(it_start, it_end, "STL : ");
// 	// print_list(i_start, i_end, "ft : ");
// 	// *it_start = 9;
// 	// *i_start = 9;
// 	// print_list(i_start, i_end, "ft : ");
// 	myfile.close();
// }
#include "List.hpp"
#include <list>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "utils.hpp"
#include "to_string.hpp"

typedef double my_type;
static Counter counter;

template <class T>
void	basic_tests(T &lst, std::ostream &output)
{
	header("BASICS TESTS", output);
	output << "List size before push is = " << lst.size() << std::endl;
	lst.push_front(5.67);
	lst.push_back(3.12);
	lst.push_back(9.56);
	lst.push_front(10.4);
	output << "\t\t== SIZE TESTS ==\n";
	output << "List max size = " << lst.max_size() << std::endl;
	output << "List actual size is = " << lst.size() << std::endl;
	lst.push_back(12.4232);
	lst.push_front(15.876);
	lst.push_back(6.9);
	lst.push_front(20.12);
	output << "\t\t== ITERATING THROUGH LIST USING ITERATOR AND REVERSE ==" << std::endl;
	print_container(lst.begin(), lst.end(), output, " -> ");
	print_container(lst.rbegin(), lst.rend(), output, " -> ");
	output << "\t\t== PRINT FRONT AND END ELEM ==\n";
	output << "Front : " << lst.front() << std::endl;
	output << "Back : " << lst.back() << std::endl;
	output << "\t\t== MODIFYIONG FRONT AND BACK THROUGH REFERENCE ==\n";
	lst.front() = 999.2312;
	lst.back() = 123.8964;
	output << "Front after modifying : " << lst.front() << std::endl;
	output << "Back after modifying : " << lst.back() << std::endl;	
	output << "\t\t== POP FRONT AND BACK ==\n";
	print_container(lst.begin(), lst.end(), output, " -> ");
	lst.pop_front();
	lst.pop_back();
	print_container(lst.begin(), lst.end(), output, " -> ");
	output << "\t\t== POP FRONT WHILE NOT EMPTY ==\n";
	while (!lst.empty())
		lst.pop_back();
	print_container(lst.begin(), lst.end(), output, " -> ");
}

template < class T>
void	insertion_tests(T &lst, std::ostream& output)
{
	T lst_tmp;
	header("INSERTION", output);
	output << "Is lst empty ? " << lst.empty() << std::endl;
	lst.assign(5, 5);
	print_container(lst.begin(), lst.end(), output, " -> ");
	output << "\t\t== CREATING NEW LIST ==\n";
	for (double i = 10.0; i > 0; i--)
		lst_tmp.push_back(i * 4.34 + 2.67  - 4.1);
	print_container(lst_tmp.begin(), lst_tmp.end(), output, " -> ");
	output << "\t\t== ASSIGN LST_TMP TO LST ==\n";
	lst.assign(lst_tmp.begin(), lst_tmp.end());
	print_container(lst.begin(), lst.end(), output, " -> ");
}

template <class T>
void	constructor_tests(T lst, std::ostream &output)
{
	header("CONSTRUCTOR", output);
	output << "lst construct from copy :\n";
	print_container(lst.begin(), lst.end(), output, " -> ");
	output << "\t\t== ASSIGANTION CONTRUCTOR ==\n";
	T lst_tmp = lst;
	print_container(lst_tmp.begin(), lst_tmp.end(), output, " -> ");
	output << "\t\t== CONTRUCTOR WITH CERTAIN NUMBER OF BASE VALUE ==\n";
	T lst_tmp2(6);
	print_container(lst_tmp2.begin(), lst_tmp2.end(), output, " -> ");
	output << "\t\t== ASSIGNATION CONTRUCTOR FROM LST ==\n";
	T lst_tmp4(ft::next(lst.begin(), 3), ft::prev(lst.end(), 2));
	print_container(lst_tmp4.begin(), lst_tmp4.end(), output, " -> ");
}

template <class T>
void	erase_tests(T lst, std::ostream& output)
{
	typename T::iterator it;
	std::string str_tmp;
	header("ERASE", output);
	output << "\t\t== STARTING CONTAINER IS ==\n";
	print_container(lst.begin(), lst.end(), output, " -> ");
	output << "\t\t== ERASE FRONT ELEMENT ==\n";
	output << "Erase return " << *lst.erase(lst.begin()) << std::endl;
	print_container(lst.begin(), lst.end(), output, " -> ");
	output << "Erase return " << *lst.erase(ft::next(lst.begin(), 4)) << std::endl;
	print_container(lst.begin(), lst.end(), output, " -> ");
	output << "\t\t== ERASE FROM 3 to 6 ELEMENTS ==\n";
	it = lst.erase(ft::next(lst.begin(), 3), ft::next(lst.begin(), 6));
	str_tmp = ((it == lst.end()) ? "end iterator": utils::to_string(*it));
	output << "Erase returned " << str_tmp << std::endl;
	print_container(lst.begin(), lst.end(), output, " -> ");
	output << "\t\t== ERASE BACK ELEMENT ELEMENT ==\n";
	it = lst.erase(ft::prev(lst.end()));
	str_tmp = ((it == lst.end()) ? "end iterator": utils::to_string(*it));
	output << "Erase returned " << str_tmp << std::endl;
	print_container(lst.begin(), lst.end(), output, " -> ");
	lst.clear();
	output << "List empty ? " << lst.empty() << std::endl;
	output << "List size : " << lst.size() << std::endl;
	print_container(lst.begin(), lst.end(), output, " -> ");
	output << "\t\t== ERASE ALL ELEMENTS ==\n";
	it = lst.erase(lst.begin(), lst.end());
	str_tmp = ((it == lst.end()) ? "end iterator": utils::to_string(*it));
	output << "Erase return " << str_tmp << std::endl;
	print_container(lst.begin(), lst.end(), output, " -> ");

}

template <class T>
void	insert_tests(T &lst, std::ostream &output)
{
	typename T::iterator it;
	std::string str_tmp;
	T	lst_tmp;

	header("INSERT", output);
	print_container(lst.begin(), lst.end(), output, " -> ");
	lst.insert(ft::next(lst.begin(), 4), 3, 999.123);
	print_container(lst.begin(), lst.end(), output, " -> ");
	output << "\t\t== INSERT ELEM AT BACK ==\n";
	lst.insert(lst.end(), 1, 66.32);
	print_container(lst.begin(), lst.end(), output, " -> ");
	output << "\t\t== INSERT ONE ELEM  WITH RETURN ITERATOR ==\n";
	it = lst.insert(ft::next(lst.begin(), 3), 32.3);
	str_tmp = ((it == lst.end()) ? "end iterator": utils::to_string(*it));
	output << "Insert returned : " << str_tmp << std::endl;
	print_container(lst.begin(), lst.end(), output, " -> ");
	
	output << "\t\t== INSERT ONE ELEM WITH RETURN ITERATOR AT BACK ==\n";
	it = lst.insert(lst.end(), 32.3);
	str_tmp = ((it == lst.end()) ? "end iterator": utils::to_string(*it));
	output << "Insert returned : " << str_tmp << std::endl;
	print_container(lst.begin(), lst.end(), output, " -> ");
	output << "\t\t== INSERT WITH ITERATOR RANGE ==\n";
	lst_tmp.insert(lst_tmp.begin(), ft::next(lst.begin(), 4), ft::next(lst.begin(), 7));
	print_container(lst_tmp.begin(), lst_tmp.end(), output, " -> ");
	output << "\t\t== CLEAR LST_TMP =\n";
	lst_tmp.clear();
	output << "Lst_tmp size : " << lst_tmp.size() << std::endl;
	output << "Lst_tmp empty ? " << lst_tmp.empty() << std::endl;
	print_container(lst_tmp.begin(), lst_tmp.end(), output, " -> ");


}

template <class T>
void	manipulation_tests(T &lst, std::ostream& output, std::string nspace)
{
	T lst_cpy(lst);
	header("MANIPULATION", output);
	print_container(lst.begin(), lst.end(), output, " -> ");
	output << "List size : " << lst.size() << std::endl;
	output << "\t\t== RESIZE TO SIZE 5 ==\n";
	lst.resize(5);
	print_container(lst.begin(), lst.end(), output, " -> ");
	output << "List size : " << lst.size() << std::endl;
	output << "\t\t== RESIZE TO SIZE 15 AGAIN ==\n";
	lst.resize(15);
	print_container(lst.begin(), lst.end(), output, " -> ");
	output << "List size : " << lst.size() << std::endl;
	output << "\t\t== SWAP LST AND LST_CPY ==\n";
	output << "Lst contains :\n";
	print_container(lst.begin(), lst.end(), output, " -> ");
	output << "Lst_cpy contains :\n";
	print_container(lst_cpy.begin(), lst_cpy.end(), output, " -> ");
	lst.swap(lst_cpy);
	output << "Lst after swap contains :\n";
	print_container(lst.begin(), lst.end(), output, " -> ");
	output << "Lst_cpy after swap contains :\n";
	print_container(lst_cpy.begin(), lst_cpy.end(), output, " -> ");
	output << "\t\t== SWAP BACK USING NON MEMBER FUNCTION ==\n";
	if (!nspace.compare("std"))
		using namespace std;
	else
		using namespace ft;
	swap(lst_cpy, lst);
	output << "Lst after swap contains :\n";
	print_container(lst.begin(), lst.end(), output, " -> ");
	output << "Lst_cpy after swap contains :\n";
	print_container(lst_cpy.begin(), lst_cpy.end(), output, " -> ");
	output << "\t\t== SPLICE ELEM FROM LST TO LST_CPY ==\n";
	lst.splice(ft::next(lst.begin(), 3), lst_cpy, ft::next(lst_cpy.begin(), 5));
	output << "Lst after splice contains :\n";
	print_container(lst.begin(), lst.end(), output, " -> ");
	output << "Lst_cpy after splice contains :\n";
	print_container(lst_cpy.begin(), lst_cpy.end(), output, " -> ");
	output << "\t\t== SPLICE ELEM FROM LST TO LST_CPY WITH RANGE ITERATOR ==\n";
	lst.splice(ft::next(lst.begin(), 3), lst_cpy, ft::next(lst_cpy.begin(), 2), ft::next(lst_cpy.begin(), 5));
	output << "Lst after splice contains :\n";
	print_container(lst.begin(), lst.end(), output, " -> ");
	output << "Lst_cpy after splice contains :\n";
	print_container(lst_cpy.begin(), lst_cpy.end(), output, " -> ");
	output << "\t\t== SPLICE ALL ELEM FROM LST TO LST_CPY ==\n";
	lst.splice(ft::next(lst.begin(), 7), lst_cpy);
	output << "Lst after splice contains :\n";
	print_container(lst.begin(), lst.end(), output, " -> ");
	output << "Lst_cpy after splice contains :\n";
	print_container(lst_cpy.begin(), lst_cpy.end(), output, " -> ");
	lst_cpy = lst;
	output << "\t\t== SORT LIST_CPY ASCENDING ORDER ==\n";
	output << "lst_cpy size : " << lst_cpy.size() << std::endl;
	print_container(lst_cpy.begin(), lst_cpy.end(), output, " -> ");
	lst_cpy.sort();
	print_container(lst_cpy.begin(), lst_cpy.end(), output, " -> ");
	output << "\t\t== MAKING VALUE IN LST_CPY UNIQUE ==\n";
	lst_cpy.unique();
	print_container(lst_cpy.begin(), lst_cpy.end(), output, " -> ");
	output << "\t\t== REVERSE LIST_CPY ==\n";
	lst_cpy.reverse();
	print_container(lst_cpy.begin(), lst_cpy.end(), output, " -> ");
	output << "\t\t== MERGING LST AND LST_CPY ==\n";
	lst.sort();
	lst_cpy.reverse();
	output << "Lst before merge : \n\t";
	print_container(lst.begin(), lst.end(), output, " -> ");
	output << "Lst_cpy before merge : \n\t";
	print_container(lst_cpy.begin(), lst_cpy.end(), output, " -> ");
	lst.merge(lst_cpy);
	output << "Lst after merge : \n\t";
	print_container(lst.begin(), lst.end(), output, " -> ");
	output << "Lst_cpy after merge : \n\t";
	print_container(lst_cpy.begin(), lst_cpy.end(), output, " -> ");
	output << "\t\t== REMOVE ELEMENTS WITH VALUE 32 ==\n";
	lst.remove(32);
	print_container(lst.begin(), lst.end(), output, " -> ");
	output << "\t\t== REMOVE ELEMENTS WITH VALUE 0 ==\n";
	lst.remove(0);
	print_container(lst.begin(), lst.end(), output, " -> ");
	output << "\t\t== REMOVE ODD ELEMENTS ==\n";
	lst.remove_if(is_odd());
	print_container(lst.begin(), lst.end(), output, " -> ");
	output << "\t\t== CLEAR LST AND LST_CPY AND CREATE NEW ONES ==\n";
	lst.clear();
	lst_cpy.clear();
	lst.push_back (3.1);
	lst.push_back (2.2);
	lst.push_back (2.9);
	lst_cpy.push_back (3.7);
	lst_cpy.push_back (7.1);
	lst_cpy.push_back (1.4);
	lst.sort();
	lst_cpy.sort();
	output << "Lst is now like this : \n\t";
	print_container(lst.begin(), lst.end(), output, " -> ");
	output << "Lst_cpy is now like this : \n\t";
	print_container(lst_cpy.begin(), lst_cpy.end(), output, " -> ");
	output << "\t\t== SORTING BOTH LIST THEN MERGING WITH COMP PREDICATE ==\n";
	lst.merge(lst_cpy, mycomparison);
	output << "Lst is now like this : \n\t";
	print_container(lst.begin(), lst.end(), output, " -> ");
	output << "Lst_cpy is now like this : \n\t";
	print_container(lst_cpy.begin(), lst_cpy.end(), output, " -> ");
}

// template <class T>
// void	comparison_tests(T &lst, std::ostream& output)
// {
// 	T a = lst;
// 	T b(a);
// 	lst.reverse();
// 	T c = lst;
// 	T d(ft::next(lst.begin()), lst.end());

	// typename std::iterator_traits<ft::list_iterator<const double> >::value_type test = 0.0;
	// if (a==b) output << "a and b are equal\n";
// 	if (b!=c) output << "b and c are not equal\n";
// 	if (b<c) output << "b is less than c\n";
// 	if (c>b) output << "c is greater than b\n";
// 	if (a<=b) output << "a is less than or equal to b\n";
// 	if (a>=b) output << "a is greater than or equal to b\n";
// 	if (d < a) output << "d is less than a\n";
// 	if (b < d) output << "b is geater than d\n";
// }

void test_lists(void)
{
    ft::list<my_type> ft;
    std::list<my_type> stl;

    std::ofstream stl_output;
	std::ofstream ft_output;

	stl_output.open(LIST_STL_OUTPUT);
	ft_output.open(LIST_FT_OUTPUT);

	basic_tests(stl, stl_output);
	basic_tests(ft, ft_output);

	insertion_tests(stl, stl_output);
	insertion_tests(ft, ft_output);

	constructor_tests(stl, stl_output);
	constructor_tests(ft, ft_output);

	erase_tests(stl, stl_output);
	erase_tests(ft, ft_output);

	insert_tests(stl, stl_output);
	insert_tests(ft, ft_output);

	manipulation_tests(stl, stl_output, "std");
	manipulation_tests(ft, ft_output, "ft");
	stl.clear();
	ft.clear();
	stl.push_back(10); stl.push_back(20); stl.push_back(30);
	ft.push_back(10); ft.push_back(20); ft.push_back(30);

	// ft::list<my_type>::const_iterator cit = ft.begin();
	// comparison_tests(stl, stl_output);
	// comparison_tests(ft, ft_output);
}

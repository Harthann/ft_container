#include "Vector.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

template <class T>
struct test_alloc : std::allocator<T> {
	T *allocate(size_t size) {
		std::cout << "Allocate request of size : " << size << std::endl;
		return (new T[size]);
	}
	void deallocate(T *ptr, size_t size) {
		std::cout << "Deallocation request of size : " << size << std::endl;
		delete ptr;
	}
};

template <class T>
std::string print_vec(T start, T end, const std::string str)
{
	std::string tmp(str);

	while (start != end) {
		tmp.append(std::to_string(*start));
		start++;
		if (start != end)
			tmp.append(" : ");
	}
	tmp.append("\n");
	return (tmp);
}

template < class T >
void test_exec(T &vec, std::string output_name)
{
	// std::cout << "entered templated functionm test :\n\n";
	for (int i = 0; i < 10; i++)
		vec.push_back(i);
	std::ofstream output (output_name, std::ios::out | std::ios::ate);
	output << "Size of vector is : " << vec.size() << std::endl;
	output << "Container vec's capacity is : " << vec.capacity() << std::endl;
	output << print_vec(vec.begin(), vec.end(), "Vector : \n");
	output << "Vec is empty : " << vec.empty() << std::endl;
	output << "Max_size of vec is : " << vec.max_size() << std::endl;
	vec.reserve(25);
	std::cout << "\n\tRESERVE\n";
	output << "\n\tRESERVE\n";
	output << "Size of vector after reserve is : " << vec.size() << std::endl;
	output << "Container vec's capacity after reserve is : " << vec.capacity() << std::endl;
	output << print_vec(vec.begin(), vec.end(), "Vector after reserve : \n");
	vec.shrink_to_fit();
	std::cout << "\n\tSHRINK\n";
	output << "\n\tSHRINK\n";
	output << "Container vec's capacity after shrink is : " << vec.capacity() << std::endl;
	output << print_vec(vec.begin(), vec.end(), "Vector after shrink : \n");
	vec.clear();
	std::cout << "\n\tCLEAR\n";
	output << "\n\tCLEAR\n";
	output << print_vec(vec.begin(), vec.end(), "Vector after clear : \n");
	output << "Container vec's capacity after clear is : " << vec.capacity() << std::endl;

	for (int i = 0; i < 10; i++)
		vec.push_back(i);
	std::cout << "\n\tERASE\n";
	output << "\n\tERASE\n";
	output << "Element returned by erase : " << *vec.erase(vec.begin() + 3) << std::endl;
	output << print_vec(vec.begin(), vec.end(), "Vector after erase : \n");
	output << "Container vec's capacity after erase is : " << vec.capacity() << std::endl;

	std::cout << "\n\tERASE 2\n";
	output << "\n\tERASE 2\n";
	output << "Element returned by erase : " << *vec.erase(vec.begin() + 3, vec.begin() + 5) << std::endl;
	output << print_vec(vec.begin(), vec.end(), "Vector after erase : \n");
	output << "Container vec's capacity after erase is : " << vec.capacity() << std::endl;

	std::cout << "\n\tINSERT\n";
	output << "\n\tINSERT\n";
	vec.insert(vec.begin() + 3, 5);
	vec.insert(vec.begin() + 3, 5);
	vec.insert(vec.begin() + 3, 5);
	vec.insert(vec.begin() + 3, 5);
	output << print_vec(vec.begin(), vec.end(), "Vector after insert : \n");
	output << "Container vec's capacity after insert is : " << vec.capacity() << std::endl;

	std::cout << "\n\tINSERT 2\n";
	output << "\n\tINSERT 2\n";
	vec.insert(vec.begin(), vec.begin(), vec.end());
	vec.shrink_to_fit();
	output << print_vec(vec.begin(), vec.end(), "Vector after insert : \n");
	output << "Container vec's capacity after insert is : " << vec.capacity() << std::endl;



	output.close();
	std::cout << "Exiting templated function test\n\n";
}

typedef int my_type;
void test_vector(void)
{
	// std::ofstream stlfile ("stl_vector_output", std::ios::out | std::ios::ate);
	ftc::Vector<my_type, test_alloc<my_type> > ftc;
	std::vector<my_type, test_alloc<my_type> > stl;
	// std::vector<my_type, test_alloc<my_type> > stl(7);
	// std::vector<my_type, test_alloc<my_type> > stl2(56);
	// std::vector<my_type, test_alloc<my_type> > ftc(7);
	// std::vector<my_type, test_alloc<my_type> > ftc2(56);
// 
	// stl.insert(stl.begin() + 2, stl2.begin(), stl2.end());
	// ftc.insert(ftc.begin() + 2, ftc2.begin(), ftc2.end());
	// std::cout << print_vec(stl.begin(), stl.end(), "Stl vector:\n");
	// std::cout << print_vec(ftc.begin(), ftc.end(), "Ftcvector:\n");
	test_exec(stl, "stl_vector_output");
	test_exec(ftc, "ftc_vector_output");
	// ftcfile.close();
	// stlfile.close();
	// getchar();
}
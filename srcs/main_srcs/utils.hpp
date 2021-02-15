#ifndef UTILS_HPP
#define UTILS_HPP

#include "Vector.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <stdlib.h>

#define VEC_STL_OUTPUT "outputs/vector/stl_vector_output"
#define VEC_FT_OUTPUT "outputs/vector/ft_vector_output"

#define LIST_STL_OUTPUT "outputs/list/stl_list_output"
#define LIST_FT_OUTPUT "outputs/list/ft_list_output"

struct Counter {
	Counter() : destroy_ft_count(0), destroy_stl_count(0), construct_ft_count(0), construct_stl_count(0) {};
	size_t destroy_ft_count;
	size_t destroy_stl_count;
	size_t construct_ft_count;
	size_t construct_stl_count;

    static Counter& get() {
        static Counter count;
        return (count);
    };

	void print() {
		std::cout << "Destroy stl call count : " << destroy_stl_count << std::endl;
		std::cout << "Construct stl call count : " << construct_stl_count << std::endl;
		std::cout << "Destroy ft call count : " << destroy_ft_count << std::endl;
		std::cout << "Construct ft call count : " << construct_ft_count << std::endl;
	}
};


template <class T>
struct alloc_ft{
	typedef T	value_type;
	typedef T*	pointer;
	typedef T&	reference;
	typedef const T*	const_pointer;
	typedef const T&	const_reference;
	typedef size_t		size_type;
	typedef std::ptrdiff_t	difference_type;
	template <class Type> struct rebind {
		typedef alloc_ft<Type> other;
	};	

	alloc_ft() {std::cout << "\033[32mAlloc_ft contructor called\n\033[0m";};
	alloc_ft(alloc_ft const &) {std::cout << "\033[32mAlloc_ft contructor cpy called\n\033[0m";};
	~alloc_ft() {};

	T *allocate(size_t size) {
		std::cout << "\033[32mAllocate request of size : " << size << std::endl;
		std::cout << "\033[0m";
		return (new T[size]);
	}
	void deallocate(T *ptr, size_t size) {
		std::cout << "\033[32mDeallocation request of size : " << size << std::endl;
		std::cout << "\033[0m";
		delete [] ptr;
	}
	
	pointer address(reference X) { return (&X); };
	const_pointer address(const_reference X) const { return (&X); };
	void	construct(pointer p, const_reference val) {
		Counter::get().construct_ft_count += 1;
		new(p) value_type(val);};
	void	destroy(pointer p) {
		// std::cout << "\033[32mDestroyer called\n\033[0m";
	    Counter::get().destroy_ft_count += 1;
		p->~value_type(); };
	size_t	max_size() const {return (std::numeric_limits<size_type>::max());}; 
};

template <class T>
struct alloc_std{
	typedef T	value_type;
	typedef T*	pointer;
	typedef T&	reference;
	typedef const T*	const_pointer;
	typedef const T&	const_reference;
	typedef size_t		size_type;
	typedef std::ptrdiff_t	difference_type;
	template <class Type> struct rebind {
		typedef alloc_std<Type> other;
	};	

	alloc_std() {std::cout << "\033[31mAlloc_std contructor called\n\033[0m";};
	alloc_std(alloc_std const &) {std::cout << "\033[31mAlloc_std contructor cpy called\n\033[0m";};
	~alloc_std() {};

	T *allocate(size_t size) {
		std::cout << "\033[31mAllocate request of size : " << size << std::endl;
		std::cout << "\033[0m";
		return (new T[size]);
	}
	void deallocate(T *ptr, size_t size) {
		std::cout << "\033[31mDeallocation request of size : " << size << std::endl;
		std::cout << "\033[0m";
		delete [] ptr;
	}
	
	pointer address(reference X) { return (&X); };
	const_pointer address(const_reference X) const { return (&X); };
	void	construct(pointer p, const_reference val) {
		Counter::get().construct_stl_count += 1;
		new(p) value_type(val);};
	void	destroy(pointer p) {
		// std::cout << "\033[31mDestroyer called\n\033[0m" ;
		Counter::get().destroy_stl_count += 1;
		p->~value_type(); };
	size_t	max_size() const {return (std::numeric_limits<size_type>::max());}; 
};

template <class T>
void	print_container(T start, T end, std::ostream &output)
{
	while (start != end) {
		output << *start;
		++start;
		if (start != end)
			output << " : ";
	}
	output << "\n";
}

void	header(std::string str, std::ostream& output);

#endif
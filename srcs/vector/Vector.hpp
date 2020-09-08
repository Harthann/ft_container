#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include "MyAlloc.hpp"
#include "Vector_iterator.hpp"

namespace ftc {

template <class T> class MyAlloc;
template <class T> class Vector_iterator;

template <class T, class A = MyAlloc<T> >
class Vector {

	typedef ftc::Vector_iterator<T> iterator;
	public:
		// Vector() : array(nullptr), size(0), allocated_size(1) {};
		Vector(size_t size = 0);
		Vector(const Vector&);
		~Vector() {
			A alloc;
			if (size_value)
				alloc.deallocate(array, allocated_size);
		};

		T* begin() { return (array); };
		T* end() { return (array + size_value); };

		size_t size() { return (size_value); };

		// Capacity block

		bool empty() const { return (size_value == 0); } ;
		size_t max_size() const { return (std::numeric_limits<int>::max()) ; };
		size_t capacity() const { return (allocated_size); };
		void reserve(size_t new_cap);
		void shrink_to_fit();

		// Modifiers block
		void push_back(T value);
		void clear();
		T* erase(T* start);
		T* erase(T* start, T* end);


		private:
		T *array;
		size_t size_value;
		size_t allocated_size;
};

//###############################
//#		CONSTRUCTOR/DESTRUCTOR	#
//###############################

template <class T, class A>
Vector<T, A>::Vector(size_t value)
{
	A alloc;
	if (value)
	{
		std::cout << "\033[0;35mFrom FTC : \n";
		array = alloc.allocate(value);
		for (size_t i = 0; i < value; i++)
			array[i] = 0;
		this->size_value = value;
		std::cout << "\033[0m";
	}
	else
		array = nullptr;
	allocated_size = value;
	this->size_value = value;
}

template <class T, class A>
Vector<T, A>::Vector(const Vector& base)
{
	A alloc;
	this->size_value = base.size_value;
	this->allocated_size = base.allocated_size;
	this->array = alloc.allocate(this->allocated_size);
	for (size_t i = 0; i < this->size_value; i++)
		this->array[i] = base.array[i];
}

//###########################
//#		MEMBER FUNCTION		#
//###########################

template <class T, class A>
void Vector<T, A>::push_back(T value)
{
	A alloc;
	T *tmp;

	std::cout << "Push back function, allocated value is : " << allocated_size << "\n";
	if (allocated_size < size_value + 1) {
		tmp = alloc.allocate(allocated_size * 2 + (allocated_size == 0));
	}
	else
			tmp = array;
	for (size_t i = 0; i < size_value; i++)
		tmp[i] = array[i];
	tmp[size_value] = value;

	if (allocated_size < size_value + 1) {
		if (allocated_size)
			alloc.deallocate(array, allocated_size);
		allocated_size = allocated_size * 2  + (allocated_size == 0);
	}
	size_value += 1;
	array = tmp;
}

template <class T, class A>
void Vector<T,A>::reserve(size_t new_cap)
{
	A alloc;
	T* tmp;

	if (new_cap > allocated_size)
	{

		std::cout << "\033[0;35mFrom FTC : \n";
		tmp = alloc.allocate(new_cap);
		std::cout << "\033[0m";
		for (size_t i = 0; i < size_value; i++)
			tmp[i] = array[i];
		std::cout << "\033[0;35mFrom FTC : \n";
		alloc.deallocate(array, allocated_size);
		std::cout << "\033[0m";
		array = tmp;
		allocated_size = new_cap;
	}
}

template <class T, class A>
void Vector<T,A>::shrink_to_fit()
{
	A alloc;
	T* tmp;

	if (size_value < allocated_size)
	{
		tmp = alloc.allocate(size_value);
		for (size_t i = 0; i < size_value; i++)
			tmp[i] = array[i];
		alloc.deallocate(array, allocated_size);
		array = tmp;
		allocated_size = size_value;
	}
}

//###################
//#		MODIFIERS	#
//###################

template <class T, class A>
void Vector<T,A>::clear()
{
	for (size_t i = 0; i < size_value; i++)
		array[i] = 0;
	size_value = 0;
}

template <class T, class A>
T* Vector<T,A>::erase(T* start)
{
	T* tmp;
	int i = 0;

	tmp = this->end();
	while (start + i != tmp)
	{
		if (start + i + 1 != tmp)
			*(start + i) = *(start + i) + 1;
		i++;
	}
	size_value--;
	if (start == tmp)
		return (this->end());
	return (start + 1);
}

template <class T, class A>
T* Vector<T,A>::erase(T* start, T*end)
{
	size_t i = size_value - (this->end() - start);
	size_t new_size = size_value - i;

	while (i < size_value)
	{
		if (i + 1 <= size_value)
			array[i] = array[i + 1];
		i++;
	}
	size_value = new_size;
	return (end);
}


} // namespace decalaration end

#endif
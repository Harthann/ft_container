#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <string>
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

		ftc::Vector_iterator<T> begin() { return (array); };
		ftc::Vector_iterator<T> end() { return (array + size_value); };

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

		ftc::Vector_iterator<T> erase(ftc::Vector_iterator<T> start);
		ftc::Vector_iterator<T> erase(ftc::Vector_iterator<T> start, ftc::Vector_iterator<T> end);

		ftc::Vector_iterator<T> insert(ftc::Vector_iterator<T> pos, const T& value);
		ftc::Vector_iterator<T> insert(ftc::Vector_iterator<T> pos, ftc::Vector_iterator<T> its, ftc::Vector_iterator<T> ite);

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
ftc::Vector_iterator<T> Vector<T,A>::erase(ftc::Vector_iterator<T> start)
{
	ftc::Vector_iterator<T> tmp;
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
	return (start);
}

template <class T, class A>
ftc::Vector_iterator<T> Vector<T,A>::erase(ftc::Vector_iterator<T> start, ftc::Vector_iterator<T>end)
{
	ftc::Vector_iterator<T> mem = start;
	while (end != this->end())
	{
		*start = *end;
		start++;
		end++;
	}
	size_value = start - this->begin();
	return (mem);
}


template <class T, class A>
ftc::Vector_iterator<T> Vector<T,A>::insert(ftc::Vector_iterator<T> pos, const T& value)
{
	ftc::Vector_iterator<T> it;
	size_t delta = pos - this->begin();

	if (allocated_size < size_value + 1) {
		this->reserve(allocated_size * 2 + (allocated_size == 0));
		pos = this->begin() + delta;
	}
	std::cout << "reserve done \n";
	it = this->end();
	while (it != pos)
	{
		*it = *(it - 1);
		it--;
	}
	*it = value;
	size_value++;
	return (pos);
}

template <class T, class A>
ftc::Vector_iterator<T> Vector<T,A>::insert(ftc::Vector_iterator<T> pos, ftc::Vector_iterator<T> its, ftc::Vector_iterator<T> ite)
{
	ftc::Vector_iterator<T> it;
	ftc::Vector_iterator<T> tmp = pos;
	size_t delta = its - ite;

	if (allocated_size < size_value + delta) {
		if (allocated_size * 2 < size_value + delta)
		{
			this->reserve(size_value + delta + (allocated_size == 0));
			std::cout << "Entered big alloc\n";
		}
		else
		{
			this->reserve(allocated_size * 2 + (allocated_size == 0));
			std::cout << "Entered little alloc\n";
		}
	}
	it = this->end();
	while (it != pos)
	{
		*(it + delta) = *(it);
		it--;
	}
	while (ite != its)
	{
		*it = *ite;
		ite++;
		it++;
	}
	size_value += delta;
	return (tmp);
}


} // namespace decalaration end

#endif
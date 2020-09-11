#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <initializer_list>
#include <string>
#include "MyAlloc.hpp"
#include "Vector_iterator.hpp"

namespace ftc {

template <class T> class MyAlloc;
template <class T> class Vector_iterator;

template <class T, class A = MyAlloc<T> >
class Vector {

	public:
		typedef ftc::Vector_iterator<T> iterator;
		// Vector() : array(nullptr), size(0), allocated_size(1) {};
		Vector(size_t size = 0);
		Vector(const Vector&);
		~Vector() {
			A alloc;
			if (size_value)
				alloc.deallocate(array, allocated_size);
		};

		iterator begin() { return (array); };
		iterator end() { return (array + size_value); };

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

		iterator erase(iterator start);
		iterator erase(iterator start, iterator end);

		iterator insert(iterator pos, const T& value);
		// iterator insert(iterator pos, const T&& value);
		iterator insert(iterator pos, iterator its, iterator ite);
		iterator insert(iterator pos, size_t count,const T& value );
		iterator insert(iterator pos, std::initializer_list<T> ilist );

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
		array = alloc.allocate(value);
		for (size_t i = 0; i < value; i++)
			array[i] = 0;
		this->size_value = value;
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

		tmp = alloc.allocate(new_cap);
		for (size_t i = 0; i < size_value; i++)
			tmp[i] = array[i];
		alloc.deallocate(array, allocated_size);
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


//################################################
//################################################
//##			ERASE MEMBERS	OVERLOAD		##
//################################################
//################################################

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

//################################################
//################################################
//##			INSERT MEMBERS	OVERLOAD		##
//################################################
//################################################


template <class T, class A>
ftc::Vector_iterator<T> Vector<T,A>::insert(ftc::Vector_iterator<T> pos, const T& value)
{
	ftc::Vector_iterator<T> it;
	size_t delta = pos - this->begin();

	if (allocated_size < size_value + 1) {
		this->reserve(allocated_size * 2 + (allocated_size == 0));
		pos = this->begin() + delta;
	}
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
	A alloc;
	T *tmp;
	size_t new_alloc;
	size_t delta = ite - its;
	size_t i;

	if (delta && allocated_size < size_value + delta) {
		if (allocated_size * 2 < size_value + delta)
			new_alloc = size_value + delta + (allocated_size == 0);
		else
			new_alloc = allocated_size * 2 + (allocated_size == 0); 
		delta = pos - this->begin();
		tmp = alloc.allocate(new_alloc);
		it = this->begin();
		i = 0;
		while (it != pos)
		{
			tmp[i] = *it;
			it++;
			i++;
		}
		while (its != ite)
		{
			tmp[i] = *its;
			i++;
			its++;
		}
		while (it != this->end())
		{
			tmp[i] = *it;
			it++;
			i++;
		}
		size_value = i;
		alloc.deallocate(array, allocated_size);
		allocated_size = new_alloc;
		array = tmp;
		pos = this->begin() + delta;
	}
	else {
		it = this->end();
		std::cout << *pos << std::endl;
		while (it != pos)
		{
			it--;
			*(it + delta) = *(it);
		}
		size_value += delta;
		while (its != ite)
		{
			*(it + delta) = *ite;
			ite--;
			delta--;
		}
		*(it + delta) = *ite;
	}
	return (pos);
}

template <class T, class A>
ftc::Vector_iterator<T>  ftc::Vector<T,A>::insert(ftc::Vector_iterator<T>  pos, size_t count, const T& value )
{
	ftc::Vector_iterator<T> it;
	size_t delta = pos - this->begin();

	if (allocated_size < size_value + count)
	{
		if (allocated_size * 2 < size_value + count)
			this->reserve(size_value + count);
		else
			this->reserve(allocated_size * 2);
		pos = this->begin() + delta;
	}
	it = this->end();
	while (it != pos)
	{
		it--;
		*(it + count) = *it;
	}
	for (size_t i = 0; i < count; i++)
		*(it + i) = value;
	size_value += count;
	return (count != 0 ? pos : this->begin());
}

template <class T, class A>
ftc::Vector_iterator<T> ftc::Vector<T,A>::insert(ftc::Vector_iterator<T> pos, std::initializer_list<T> ilist )
{
	ftc::Vector_iterator<T> it;
	T* tmp = ilist.begin();
	size_t size = ilist.size();
	size_t delta = pos - this->begin();
	size_t new_alloc;

	if (!size)
		return (this->begin());
	if (size && allocated_size < size_value + size) {
		if (allocated_size * 2 < size_value + size)
			new_alloc = size_value + size + (allocated_size == 0);
		else
			new_alloc = allocated_size * 2 + (allocated_size == 0);
		this->reserve(new_alloc);
		pos = this->begin() + delta;
	}
	it = this->end();
	while (it != pos)
	{
		it--;
		*(it + size) = *it;
	}
	for (size_t i = 0; i < size; i++)
		*(pos + i) = tmp[i];
	return (pos);
}

} // namespace decalaration end

#endif
#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <initializer_list>
#include <string>
#include "Vector_iterator.hpp"
#include "Vector_reverse_iterator.hpp"
#include "base_iterator.hpp"


namespace ft {

// template <class T> class Vector_iterator;
template <class T> class Vector_reverse_iterator;
template <class T> class __base_iterator;

template <class T, class A = std::allocator<T> >
class Vector {

	public:
		typedef ft::Vector_iterator<T>						iterator;
		typedef ft::Vector_reverse_iterator<T>				reverse_iterator;
		typedef ft::Vector_iterator<const T>				const_iterator;
		typedef ft::Vector_reverse_iterator<const T>		const_reverse_iterator;
		typedef ft::__base_iterator<T>						__input_it;
		typedef std::allocator_traits<A>					__alloc_traits;
		typedef typename __alloc_traits::size_type			size_type;
		typedef typename __alloc_traits::difference_type	difference_type;

		typedef A	allocator_type;
		typedef typename allocator_type::reference	reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer	pointer;
		typedef typename allocator_type::const_pointer	const_pointer;
		
		Vector(size_t size = 0);
		Vector(const Vector&);
		~Vector() {
			A alloc;
			if (size_value)
				alloc.deallocate(array, allocated_size);
		};

		allocator_type get_allocator() const;
		iterator begin() { return (array); };
		iterator end() { return (array + size_value); };
		const_iterator begin() const { return (array); };
		// const_iterator cbegin() { return (array); };
		const_iterator end() const { return (array + size_value); };
		// const_iterator cend() { return (array + size_value); };
		reverse_iterator rbegin() { return (array + size_value - 1); };
		// const_reverse_iterator crbegin() { return (array + size_value - 1); };
		const_reverse_iterator rbegin() const { return (array + size_value - 1); };
		reverse_iterator rend() { return (array - 1); };
		const_reverse_iterator rend() const { return (array - 1); };
		// const_reverse_iterator crend() { return (array - 1); };

		size_t size() { return (size_value); };

		// Capacity block

		bool empty() const { return (size_value == 0); } ;
		// size_t max_size() const { return (std::numeric_limits<difference_type>::max()) ; };
		size_t capacity() const { return (allocated_size); };
		void reserve(size_t new_cap);
		void shrink_to_fit();

		// Modifiers block
		void push_back(T value);
		void clear();

		iterator erase(iterator start);
		iterator erase(iterator start, iterator end);

		iterator insert(iterator pos, const T& value);
		// template <class InputIT>
		iterator insert(iterator pos, __input_it its, __input_it ite);
		iterator insert(iterator pos, size_t count,const T& value );

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
		this->array = tmp;
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
ft::Vector_iterator<T> Vector<T,A>::erase(ft::Vector_iterator<T> start)
{
	ft::Vector_iterator<T> tmp;
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
ft::Vector_iterator<T> Vector<T,A>::erase(ft::Vector_iterator<T> start, ft::Vector_iterator<T>end)
{
	ft::Vector_iterator<T> mem = start;
	while (start != end)
	{
		this->erase(start);
		end--;
	}
	return (mem);
}

//################################################
//################################################
//##			INSERT MEMBERS	OVERLOAD		##
//################################################
//################################################


template <class T, class A>
ft::Vector_iterator<T> Vector<T,A>::insert(ft::Vector_iterator<T> pos, const T& value)
{
	ft::Vector_iterator<T> it;
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
ft::Vector_iterator<T> Vector<T,A>::insert(ft::Vector_iterator<T> pos, __input_it its, __input_it ite)
{
	size_t delta = its.distance(its, ite);

	if (this->capacity() <= delta + this->size())
		this->reserve(delta + this->size());
	for (ft::Vector_iterator<T> it = this->end(); it != pos; it--)
		*(this->end() + delta - 1) = *it;
	for (size_t i = 0; i < delta; i++)
		*(pos + i) = *(its + i);
	this->size_value = delta + this->size();
	return (pos);
}

template <class T, class A>
ft::Vector_iterator<T>  ft::Vector<T,A>::insert(ft::Vector_iterator<T>  pos, size_t count, const T& value )
{
	ft::Vector_iterator<T> it;
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

} // namespace decalaration end

#endif
#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <string>
#include "vector_iterator.hpp"
#include "vector_reverse_iterator.hpp"
#include "base_iterator.hpp"


namespace ft {

// template <class T> class vector_iterator;
template <class T> class vector_reverse_iterator;
template <class T> class __base_iterator;

template <class T, class A = std::allocator<T> >
class vector {

	public:
		typedef ft::vector_iterator<T>						iterator;
		typedef ft::vector_reverse_iterator<T>				reverse_iterator;
		typedef ft::vector_iterator<const T>				const_iterator;
		typedef ft::vector_reverse_iterator<const T>		const_reverse_iterator;
		typedef ft::__base_iterator<T>						__input_it;
		// typedef std::allocator_traits<A>					__alloc_traits;
		typedef size_t			size_type;
		// typedef typename __alloc_traits::difference_type	difference_type;

		typedef A	allocator_type;
		typedef typename allocator_type::reference	reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer	pointer;
		typedef typename allocator_type::const_pointer	const_pointer;
		
		vector(size_t size = 0);
		vector(const vector&);
		~vector() {
			A alloc;
			if (size_value)
				alloc.deallocate(array, allocated_size);
		};

		ft::vector<T> & operator=(const ft::vector<int>& x);
		//###########################
		//#			ITERATORS		#
		//###########################

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

		//###########################
		//#			CAPACITY		#
		//###########################

		size_t	size() { return (size_value); };
		// size_t max_size() const { return (std::numeric_limits<difference_type>::max()) ; };
		// void	resize(size_type count);
		// void	resize(size_type count, T value = T());
		size_t	capacity() const { return (allocated_size); };
		bool	empty() const { return (size_value == 0); } ;
		void	reserve(size_t new_cap);
		void	shrink_to_fit();

		//###########################
		//#			ELEMENT ACCESS	#
		//###########################

		//###########################
		//#			MODIFIERS		#
		//###########################
		
		// assign
		void push_back(T value);
		// pop_back
		iterator	insert(iterator pos, const T& value);
		void		insert(iterator pos, size_t count,const T& value );
		void		insert(iterator pos, __input_it its, __input_it ite);
		iterator erase(iterator start);
		iterator erase(iterator start, iterator end);
		// swap
		void clear();
		// emplace
		// emplace_back


	private:
		T *array;
		size_t size_value;
		size_t allocated_size;
};

//###############################
//#		CONSTRUCTOR/DESTRUCTOR	#
//###############################

template <class T, class A>
vector<T, A>::vector(size_t value)
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
		array = 0;
	allocated_size = value;
	this->size_value = value;
}

template <class T, class A>
vector<T, A>::vector(const vector& base)
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
void vector<T, A>::push_back(T value)
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

// template <class T, class A>
// void	vector<T, A>::resize(size_type count)
// {
// 	(void)count;
// }

// template <class T, class A>
// void	vector<T, A>::resize(size_type count, T value)
// {
// 	(void)count;
// 	(void)value;

// }

template <class T, class A>
void vector<T,A>::reserve(size_t new_cap)
{
	A	alloc;
	T*	tmp;

	if (new_cap > allocated_size)
	{
		try {
			tmp = alloc.allocate(new_cap);
		}
		catch (std::bad_alloc& error) {
			throw (std::length_error("vector::reserve"));
		}
		for (size_t i = 0; i < size_value; i++)
			tmp[i] = array[i];
		
		alloc.deallocate(array, allocated_size);
		this->array = tmp;
		allocated_size = new_cap;
	}
}

template <class T, class A>
void vector<T,A>::shrink_to_fit()
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
void vector<T,A>::clear()
{
	for (size_t i = 0; i < size_value; i++)
		array[i] = 0;
	size_value = 0;
}

template <class T, class A>
ft::vector_iterator<T> vector<T,A>::erase(ft::vector_iterator<T> start)
{
	ft::vector_iterator<T> tmp;
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
ft::vector_iterator<T> vector<T,A>::erase(ft::vector_iterator<T> start, ft::vector_iterator<T>end)
{
	ft::vector_iterator<T> mem = start;
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
ft::vector_iterator<T> vector<T,A>::insert(ft::vector_iterator<T> pos, const T& value)
{
	ft::vector_iterator<T> it;
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
void	vector<T,A>::insert(ft::vector_iterator<T> pos, __input_it its, __input_it ite)
{
	size_t delta = its.distance(its, ite);

	if (this->capacity() <= delta + this->size())
		this->reserve(delta + this->size());
	for (ft::vector_iterator<T> it = this->end(); it != pos; it--)
		*(this->end() + delta - 1) = *it;
	for (size_t i = 0; i < delta; i++)
		*(pos + i) = *(its + i);
	this->size_value = delta + this->size();
}

template <class T, class A>
void	ft::vector<T,A>::insert(ft::vector_iterator<T>  pos, size_t count, const T& value )
{
	ft::vector_iterator<T> it;
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
}

} // namespace decalaration end

#endif
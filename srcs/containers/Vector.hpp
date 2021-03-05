#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <sstream>
#include <limits>
#include <string>
#include "sfinae_template.hpp"
#include "ft_iterator.hpp"
#include "Vector_iterator.hpp"
#include "reverse_iterator.hpp"


namespace ft {

template <class T, class A = std::allocator<T> >
class vector {

	public:

		typedef T												value_type;
		typedef A												allocator_type;
		typedef std::size_t										size_type;
		typedef	std::ptrdiff_t									difference_type;
		typedef typename allocator_type::reference				reference;
		typedef typename allocator_type::const_reference		const_reference;
		typedef typename allocator_type::pointer				pointer;
		typedef typename allocator_type::const_pointer			const_pointer;
		
		typedef ft::vector_iterator<T>							iterator;
		typedef ft::vector_iterator<const T>					const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
		
		vector(const allocator_type& alloc = allocator_type());
		vector(size_t size, const value_type& val = value_type(),
            				const allocator_type& alloc = allocator_type());
		template <class InputIT>
        vector(	typename ft::enable_if<is_input_iterator<InputIT>::value, InputIT>::type first,
				typename ft::enable_if<is_input_iterator<InputIT>::value, InputIT>::type last,
        		const allocator_type&	alloc = allocator_type());
		vector(const vector&);
		~vector() {
			if (size())
				for (iterator it = begin(); it != end(); ++it)
					__alloc.destroy(&*it);
				__alloc.deallocate(array, allocated_size);
		};

		ft::vector<T> & operator=(const ft::vector<int>& x);
		//###########################
		//#			ITERATORS		#
		//###########################

		iterator begin() { return (array); };
		iterator end() { return (array + size_value); };
		const_iterator begin() const { return (array); };
		const_iterator end() const { return (array + size_value); };

		reverse_iterator rbegin() {
			return (ft::prev(end()));
		};
		const_reverse_iterator rbegin() const {
			return (ft::prev(end()));
		};
		reverse_iterator rend() {
			return (ft::prev(begin()));
		};
		const_reverse_iterator rend() const {
			return (ft::prev(begin()));
		};

		//###########################
		//#			CAPACITY		#
		//###########################

		bool	empty() const { return (size_value == 0); } ;
		size_t	size() { return (size_value); };
		size_type max_size() const { return (allocator_type().max_size()) ; };
		void	reserve(size_t new_cap);
		void resize(size_type n, value_type value = value_type());
		size_t	capacity() const { return (allocated_size); };

		//###########################
		//#			ELEMENT ACCESS	#
		//###########################

		reference		at(size_type pos);
		const_reference at(size_type pos)			const;
		reference 		operator[](size_type pos)			{ return (this->array[pos]);		};
		const_reference operator[](size_type pos)	const	{ return (this->array[pos]);		};
		reference		front()								{ return (*(this->begin())); 		};
		const_reference front()						const	{ return (*(this->begin())); 		};
		reference		back()								{ return (*ft::prev(this->end()));	};
		const_reference back()						const	{ return (*ft::prev(this->end()));	};

		//###########################
		//#			MODIFIERS		#
		//###########################
		
		template <class InputIT>
		typename ft::enable_if<ft::is_input_iterator<InputIT>::value, InputIT>::void_t
					assign(InputIT its, InputIT ite);
		void		assign(size_t count, const value_type& value );
		void		push_back(T value);
		void		pop_back() { if (size() > 0) __alloc.destroy(&(*ft::prev(end()))); size_value--;};
		iterator	insert(iterator pos, const T& value);
		void		insert(iterator pos, size_t count,const T& value );
		template <class InputIT>
		typename ft::enable_if<ft::is_input_iterator<InputIT>::value, InputIT>::void_t
					insert(iterator pos,InputIT its, InputIT ite);
		iterator	erase(iterator start);
		iterator	erase(iterator start, iterator end);
		void		swap(vector& x);
		void		clear();

	private:
		T		*array;
		size_t	size_value;
		size_t	allocated_size;
		A		__alloc;

		void	__destroy_old__(pointer array, size_type allocated_size);
};

/*###################################################################################\
**	  _____ ____  _   _  _____ _______ _____  _    _  _____ _______ ____  _____  	##
**	 / ____/ __ \| \ | |/ ____|__   __|  __ \| |  | |/ ____|__   __/ __ \|  __ \ 	##
**	| |   | |  | |  \| | (___    | |  | |__) | |  | | |       | | | |  | | |__) |	##
**	| |   | |  | | . ` |\___ \   | |  |  _  /| |  | | |       | | | |  | |  _  / 	##
**	| |___| |__| | |\  |____) |  | |  | | \ \| |__| | |____   | | | |__| | | \ \ 	##
**	 \_____\____/|_| \_|_____/   |_|  |_|  \_\\____/ \_____|  |_|  \____/|_|  \_\	##
**																					##
\###################################################################################*/    

template <class T, class A>
vector<T, A>::vector(const A& alloc)
: array(0), size_value(0), allocated_size(0), __alloc(alloc)
{}

template <class T, class A>
vector<T, A>::vector(size_t value, const value_type& val, const A& alloc)
: __alloc(alloc)
{
	if (value)
	{
		array = __alloc.allocate(value);
		for (size_t i = 0; i < value; i++)
			__alloc.construct(&array[i], val);
		this->size_value = value;
	}
	else
		array = 0;
	this->allocated_size = value;
	this->size_value = value;
}

template <class T, class A>
template <class InputIT>
vector<T, A>::vector(	typename ft::enable_if<is_input_iterator<InputIT>::value, InputIT>::type	first,
						typename ft::enable_if<is_input_iterator<InputIT>::value, InputIT>::type	last,
																						const A&	alloc)
: __alloc(alloc)
{
	insert(first, last);
}

template <class T, class A>
vector<T, A>::vector(const vector& base) : __alloc()
{
	this->size_value = base.size_value;
	this->allocated_size = base.allocated_size;
	this->array = __alloc.allocate(this->allocated_size);
	for (size_t i = 0; i < this->size_value; i++)
		__alloc.construct(&(*this)[i], base[i]);
}

//###########################
//#		MEMBER FUNCTION		#
//###########################

template <class T, class A>
void vector<T, A>::push_back(T value)
{
	if (allocated_size < size_value + 1)
		reserve(allocated_size * 2 + (allocated_size == 0));
	__alloc.construct(&(*end()), value);
	size_value += 1;
}

template <class T, class A>
void	vector<T, A>::resize(size_type count, T value)
{
	if (count < size()) {
		for (size_type i = count; i < size(); ++i)
			__alloc.destroy(&(*this)[i]);
		size_value = count;
	}
	else {
		if (size() < capacity() && count > capacity())
			reserve(count);
		else if (count > capacity())
			reserve(std::max(allocated_size * 2, count));
		for (size_type i = size(); i < count; ++i)
			__alloc.construct(&(*this)[i], value);
		size_value = count;
	}
}

template <class T, class A>
void vector<T,A>::reserve(size_t new_cap)
{
	T*	tmp;

	if (new_cap > allocated_size)
	{
		try {
			tmp = __alloc.allocate(new_cap);
		}
		catch (std::bad_alloc& error) {
			throw std::length_error("vector::reserve");
		}
		for (size_t i = 0; i < size_value; i++)
			__alloc.construct(&tmp[i], array[i]);
		__destroy_old__(array, allocated_size);
		this->array = tmp;
		allocated_size = new_cap;
	}
}

//############################
//##	ELEMENT ACCESS		##
//############################

template <class T, class A>
typename ft::vector<T,A>::reference ft::vector<T,A>::at(size_type pos)
{
	std::stringstream str;
	if (!(pos < size()))
	{
		str << "vector::_M_range_check: __n (which is " << pos << ") >= this->size() (which is " << this->size() << ")";
		throw std::out_of_range(str.str());
	}
	else
		return (this->array[pos]);
};

template <class T, class A>
typename ft::vector<T,A>::const_reference ft::vector<T,A>::at(size_type pos) const
{
	std::stringstream str;
	if (!(pos < size()))
	{
		str << "vector::_M_range_check: __n (which is " << pos << ") >= this->size() (which is " << this->size() << ")";
		throw std::out_of_range(str.str());
	}
	else 
		return (this->array[pos]);
};


//###################
//#		MODIFIERS	#
//###################

//################################################################
//################################################################
//##			ASSIGN MEMBERS	OVERLOAD		##
//################################################################
//################################################################


template <class T, class A>
template <class InputIT>
typename ft::enable_if<ft::is_input_iterator<InputIT>::value, InputIT>::void_t
ft::vector<T, A>::assign(InputIT its, InputIT ite)
{
	typename ft::vector<T>::iterator it;
	size_t count = ft::distance(its, ite);

	if (this->capacity() < count)
		reserve(std::max(allocated_size * 2, count));
	for (size_t i = size(); i < count; i++)
		__alloc.construct(array + i, value_type());
	it = this->begin();
	while (its != ite)
	{
		*it = *its;
		++its;
		++it;
	}
	for (size_t i = count; i < size(); i++)
		__alloc.destroy(&*it + i);
	this->size_value = count;
}

template <class T, class A>
void	ft::vector<T,A>::assign(size_t count, const value_type& value )
{
	typename ft::vector<T>::iterator it;
	if (this->capacity() < count)
		reserve(std::max(allocated_size * 2, count));
	for (size_t i = size(); i < count; i++)
		__alloc.construct(array + i, value_type());
	this->size_value = count;
	it = this->begin();
	while (count != 0 )
	{
		*it = value;
		++it;
		count--;
	}
}


//################################################################
//################################################################
//##			ERASE MEMBERS	OVERLOAD		##
//################################################################
//################################################################

template <class T, class A>
void vector<T,A>::clear()
{
	for (size_t i = 0; i < size_value; i++)
		__alloc.destroy(&array[i]);
	size_value = 0;
}

template <class T, class A>
ft::vector_iterator<T> vector<T,A>::erase(ft::vector_iterator<T> start)
{
	ft::vector_iterator<T> tmp;
	int i = 0;

	tmp = this->end();
	__alloc.destroy(&(*start));
	while (start + i != tmp)
	{
		if (start + i + 1 != tmp)
			*(start + i) = *(start + i + 1);
		i++;
	}
	if (start == tmp)
		return (this->end());
	size_value--;
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
	size_t delta = ft::distance(this->begin(), pos);

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
	__alloc.construct(&*it, value);
	size_value++;
	return (pos);
}

template <class T, class A>
void	ft::vector<T,A>::insert(ft::vector_iterator<T>  pos, size_t count, const T& value )
{
	size_t delta = ft::distance(this->begin(), pos);

	if (allocated_size < size_value + count)
	{
		reserve(std::max(allocated_size * 2, count));
		pos = this->begin() + delta;
	}
	for (ft::vector_iterator<T> it = this->end(); it != pos; it--)
		*(this->end() + count - 1) = *it;
	for (size_t i = 0; i < count; i++)
		__alloc.construct(&*(pos + i), value);
	size_value += count;
}

template <class T, class A>
template <class InputIT>
typename ft::enable_if<ft::is_input_iterator<InputIT>::value, InputIT>::void_t	vector<T,A>::insert(ft::vector_iterator<T> pos, InputIT its,InputIT ite)
{
	size_t delta = ft::distance(its, ite);
	size_t index = ft::distance(this->begin(), pos);

	if (this->capacity() <= delta + this->size()) {
		this->reserve(delta + this->size());
		pos = this->begin() + index;
	}

	for (ft::vector_iterator<T> it = this->end(); it != pos; it--)
		*(this->end() + delta - 1) = *it;
	this->size_value += delta;
	while (delta > 0)
	{
		__alloc.construct(&*pos, *its);
		--delta;
		++pos;
		++its;
	}
}

template <class T, class A>
void	vector<T,A>::swap(vector& x)
{
	pointer tmp = this->array;
	size_type tmp_alloc = capacity();
	size_type tmp_size_value = size();

	this->array = x.array;
	this->allocated_size = x.capacity();
	this->size_value = x.size();

	x.array = tmp;
	x.allocated_size = tmp_alloc;
	x.size_value = tmp_size_value;
}

//############################
//##	PRIVATE METHOD		##
//############################


template <class T, class A>
void	vector<T,A>::__destroy_old__(pointer array, size_type allocated_size)
{
	if (allocated_size > 0)
	{
		for (size_type i = 0; i < size(); i++)
			__alloc.destroy(array + i);
		__alloc.deallocate(array, allocated_size);
	}
}

template <class T, class Alloc>
bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return (std::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <class T, class Alloc>
bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return (!(lhs == rhs));
}

template <class T, class Alloc>
bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return (std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template <class T, class Alloc>
bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return (!(rhs < lhs));
}

template <class T, class Alloc>
bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return (rhs < lhs);
}

template <class T, class Alloc>
bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return (!(lhs < rhs));
}


} // namespace decalaration end

#endif


#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <sstream>
#include <limits>
#include <string>

#include "sfinae_template.hpp"
#include "ft_iterator.hpp"
#include "Vector_iterator.hpp"
#include "Const_Vector_iterator.hpp"
#include "reverse_iterator.hpp"
#include "algorithm.hpp"
#include <cstddef>

namespace ft
{

	template <class T, class A = std::allocator<T> >
	class vector
	{

		public:
			typedef T											value_type;
			typedef A											allocator_type;
			typedef std::size_t									size_type;
			typedef std::ptrdiff_t								difference_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;

			typedef ft::vector_iterator<T>						iterator;
			typedef ft::const_vector_iterator<T>				const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

			vector(const allocator_type &alloc = allocator_type());
			vector(size_t size, const value_type &val = value_type(),
				const allocator_type &alloc = allocator_type());
			template <class InputIT>
			vector(typename ft::enable_if<is_input_iterator<InputIT>::value, InputIT>::type first,
				InputIT last,  const allocator_type &alloc = allocator_type());
			vector(const vector &);
			~vector()
			{
				this->clear();
				delete[] this->array;
			};

			ft::vector<value_type, allocator_type> &operator=(ft::vector<value_type, allocator_type> const &x);
			//###########################
			//#			ITERATORS		#
			//###########################

			iterator begin() { return (array); };
			iterator end() { return (array + size_value); };
			const_iterator begin() const { return (array); };
			const_iterator end() const { return (array + size_value); };

			reverse_iterator rbegin()
			{
				return (end());
			};
			const_reverse_iterator rbegin() const
			{
				return (end());
			};
			reverse_iterator rend()
			{
				return (begin());
			};
			const_reverse_iterator rend() const
			{
				return (begin());
			};

			//###########################
			//#			CAPACITY		#
			//###########################

			bool empty() const { return (size_value == 0); };
			size_t size() const { return (size_value); };
			size_type max_size() const { return (allocator_type().max_size()); };
			void reserve(size_t new_cap);
			void resize(size_type n, value_type value = value_type());
			size_t capacity() const { return (allocated_size); };

			//###########################
			//#			ELEMENT ACCESS	#
			//###########################

			reference at(size_type pos);
			const_reference at(size_type pos) const;
			reference operator[](size_type pos) { return (this->array[pos]); };
			const_reference operator[](size_type pos) const { return (this->array[pos]); };
			reference front() { return (*(this->begin())); };
			const_reference front() const { return (*(this->begin())); };
			reference back() { return (*ft::prev(this->end())); };
			const_reference back() const { return (*ft::prev(this->end())); };

			//###########################
			//#			MODIFIERS		#
			//###########################

			template <class InputIT>
			void assign(typename ft::enable_if<is_input_iterator<InputIT>::value, InputIT>::type its, InputIT ite);
			void assign(size_t count, const value_type &value);
			void push_back(T value);
			void pop_back() { resize(this->size() - 1); };
			iterator insert(iterator pos, const T &value);
			void insert(iterator pos, size_t count, const T &value);
			template <class InputIT>
			void insert(iterator pos, InputIT its,
						typename ft::enable_if<ft::is_input_iterator<InputIT>::value, InputIT>::type ite);
			iterator erase(iterator start);
			iterator erase(iterator start, iterator end);
			void swap(vector &x);
			void clear();

		private:
			T *array;
			size_t size_value;
			size_t allocated_size;
			A __alloc;
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
	vector<T, A>::vector(const A &alloc)
		: size_value(0), allocated_size(0), __alloc(alloc)
	{
		this->array = new value_type[0];
	}

	template <class T, class A>
	vector<T, A>::vector(size_t value, const value_type &val, const A &alloc)
		: size_value(value), allocated_size(value), __alloc(alloc)
	{
		this->array = new value_type[value];
		for (size_t i = 0; i < value; ++i)
			this->array[i] = val;
	}

	template <class T, class A>
	ft::vector<T, A> &vector<T, A>::operator=(vector<T, A> const &x)
	{
		this->assign(x.begin(), x.end());
		return (*this);
	}

	template <class T, class A>
	template <class InputIT>
	vector<T, A>::vector(typename ft::enable_if<is_input_iterator<InputIT>::value, InputIT>::type first,
						 InputIT last,
						 const A &alloc)
		: array(NULL), size_value(0), allocated_size(0), __alloc(alloc)
	{
		assign(first, last);
	}

	template <class T, class A>
	vector<T, A>::vector(const vector &base)
		: array(NULL), size_value(0), allocated_size(0), __alloc()
	{
		*this = base;
	}

	//###########################
	//#		MEMBER FUNCTION		#
	//###########################

	template <class T, class A>
	void vector<T, A>::push_back(T value)
	{
		this->insert(this->end(), value);
	}

	template <class T, class A>
	void vector<T, A>::resize(size_type count, T value)
	{

		if (count < this->size_value)
			erase(this->begin() + count, this->end());
		else
		{
			if (this->allocated_size < count) {
				if (this->size_value * 2 < count)
					this->reserve(count);
				else
					this->reserve(this->size_value * 2);
			}
			for (size_type i = this->size(); i < count; i++)
				this->array[i] = value;
			this->size_value = count;
		}
	}

	template <class T, class A>
	void vector<T, A>::reserve(size_t new_cap)
	{
		if (new_cap > this->allocated_size)
		{
			if (new_cap > this->max_size())
				throw std::length_error("vector::reserve");

			size_type size;
			size = this->size();
			T *tmp = new T[new_cap];
			for (size_type i = 0; i < size; i++)
			{
				tmp[i] = this->array[i];
			}
			delete[] this->array;
			this->array = tmp;
			this->allocated_size = new_cap;
		}
	}

	//############################
	//##	ELEMENT ACCESS		##
	//############################

	template <class T, class A>
	typename ft::vector<T, A>::reference ft::vector<T, A>::at(size_type pos)
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
	typename ft::vector<T, A>::const_reference ft::vector<T, A>::at(size_type pos) const
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
	void vector<T, A>::assign(typename ft::enable_if<is_input_iterator<InputIT>::value, InputIT>::type its,
							  InputIT ite)
	{
		this->clear();
		this->insert(this->begin(), its, ite);
	}

	template <class T, class A>
	void ft::vector<T, A>::assign(size_t count, const value_type &value)
	{
		this->clear();
		this->reserve(count);
		this->insert(this->begin(), count, value);
	}

	//################################################################
	//################################################################
	//##			ERASE MEMBERS	OVERLOAD		##
	//################################################################
	//################################################################

	template <class T, class A>
	void vector<T, A>::clear()
	{
		erase(this->begin(), this->end());
	}

	template <class T, class A>
	ft::vector_iterator<T> vector<T, A>::erase(ft::vector_iterator<T> pos)
	{
		return erase(pos, pos + 1);
	}

	template <class T, class A>
	typename vector<T, A>::iterator vector<T, A>::erase(iterator first, iterator last)
	{
		size_type n = last.ptr - first.ptr;
		size_type offset = first.ptr - array;
		allocator_type actr;

		for (size_type i = 0; i < size_value - n - offset; i++)
		{
			array[offset + i] = array[offset + i + n];
		}
		size_value -= n;
		return (iterator(array + offset));
	}

	//################################################
	//################################################
	//##			INSERT MEMBERS	OVERLOAD		##
	//################################################
	//################################################

	template <class T, class A>
	ft::vector_iterator<T> vector<T, A>::insert(ft::vector_iterator<T> pos, const T &value)
	{
		difference_type delta = pos - this->begin();

		this->insert(pos, 1, value);
		return (this->begin() + delta);
	}

	template <class T, class A>
	void ft::vector<T, A>::insert(ft::vector_iterator<T> pos, size_t count, const T &value)
	{
		size_t delta = pos - this->begin();
		size_t capa;

		capa = 1;
		if (this->allocated_size < this->size_value + count)
		{
			if (this->allocated_size * 2 < this->size_value + count)
				this->reserve(this->size_value + count);
			else
				this->reserve(this->allocated_size * 2 + !this->allocated_size);
		}
		pos = this->begin() + delta;
		size_value += count;
		for (iterator it = ft::prev(this->end()); it != ft::next(pos, count - 1); --it)
			*it = *ft::prev(it, count);
		for (iterator it = pos; it != pos + count; ++it)
			*it = value;
	}

	template <class T, class A>
	template <class InputIT>
	void vector<T, A>::insert(ft::vector_iterator<T> pos,
							  InputIT its,
							  typename ft::enable_if<is_input_iterator<InputIT>::value, InputIT>::type ite)
	{
		size_t delta = 0;
		size_t index = pos - this->begin();

		for (InputIT tmp = its; tmp != ite; ++tmp)
			++delta;

		if (this->allocated_size < this->size_value + delta)
		{
			if (this->size_value * 2 < this->size_value + delta)
				this->reserve(this->size_value + delta);
			else
				this->reserve(this->size_value * 2 + !this->allocated_size);
		}
		pos = this->begin() + index;
		this->size_value += delta;
		for (iterator it = ft::prev(this->end()); it != pos + delta - 1; --it)
			*it = *(it - delta);
		while (its != ite)
		{
			*pos = *its;
			++pos;
			++its;
		}
	}

	template <class T, class A>
	void vector<T, A>::swap(vector &x)
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

	template <class T, class Alloc>
	void swap(ft::vector<T, Alloc> &lhs, ft::vector<T, Alloc> &rhs)
	{
		rhs.swap(lhs);
	}

	template <class T, class Alloc>
	bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		typename vector<T, Alloc>::const_iterator lit;
		typename vector<T, Alloc>::const_iterator rit;
		if (lhs.size() != rhs.size())
			return (0);
		for (unsigned int i = 0; i < lhs.size(); ++i)
		{
			lit = ft::next(lhs.begin(), i);
			rit = ft::next(rhs.begin(), i);
			if (*lit != *rit)
				return (0);
		}
		return (1);
	}

	template <class T, class Alloc>
	bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T, class Alloc>
	bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (!(lhs < rhs));
	}

} // namespace decalaration end

#endif

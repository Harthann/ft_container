#ifndef RANDOM_ACCESS_IT_HPP
# define RANDOM_ACCESS_IT_HPP

#include "ft_iterator.hpp"
#include <cstddef>

namespace ft {

	template <class T>
	class random_access_iterator
	{
		public:
			typedef T			value_type;
			typedef value_type* pointer;
			typedef value_type& reference;
			typedef ptrdiff_t	difference_type;
			typedef	ft::random_access_iterator_tag iterator_category;
			
			random_access_iterator();
			random_access_iterator(value_type *x);
			random_access_iterator(const random_access_iterator &x);
			random_access_iterator	&operator=(random_access_iterator const &rhs);
			virtual ~random_access_iterator();

			bool	operator==(const random_access_iterator &rhs) const;
			bool	operator!=(const random_access_iterator &rhs) const;
			bool	operator<(const random_access_iterator &rhs) const;
			bool	operator<=(const random_access_iterator &rhs) const;
			bool	operator>(const random_access_iterator &rhs) const;
			bool	operator>=(const random_access_iterator &rhs) const;

			random_access_iterator<value_type>	&operator++();
			random_access_iterator<value_type>	operator++(int);
			random_access_iterator<value_type>	&operator--();
			random_access_iterator<value_type>	operator--(int);

			difference_type			operator-(const random_access_iterator &rhs) const;
			random_access_iterator<value_type>			operator+(difference_type n) const;
			random_access_iterator<value_type>			operator-(difference_type n) const;
			friend random_access_iterator<value_type>	operator+(difference_type n, const random_access_iterator &rhs)
				{ return rhs.operator+(n); };

		protected:
			pointer		ptr;
	};

	template <typename T>
	random_access_iterator<T>::random_access_iterator() : ptr(NULL) {
		return ;
	}

	template <typename T>
	random_access_iterator<T>::random_access_iterator(T *x) : ptr(x) {
		return ;
	}

	template <typename T>
	random_access_iterator<T>::random_access_iterator(const random_access_iterator &x) {
		*this = x;
	}

	template <typename T>
	random_access_iterator<T>::~random_access_iterator() {
		return ;
	}

	template <typename T>
	random_access_iterator<T> &random_access_iterator<T>::operator=(const random_access_iterator &rhs) {
		if (this == &rhs)
			return (*this);
		this->ptr = rhs.ptr;
		return (*this);
	}

	template <typename T>
	bool	random_access_iterator<T>::operator==(const random_access_iterator &rhs) const {
		return (this->ptr == rhs.ptr);
	}

	template <typename T>
	bool	random_access_iterator<T>::operator!=(const random_access_iterator &rhs) const {
		return (this->ptr != rhs.ptr);
	}

	template <typename T>
	bool	random_access_iterator<T>::operator<(const random_access_iterator &rhs) const {
		return (this->ptr < rhs.ptr);
	}

	template <typename T>
	bool	random_access_iterator<T>::operator<=(const random_access_iterator &rhs) const {
		return (this->ptr <= rhs.ptr);
	}

	template <typename T>
	bool	random_access_iterator<T>::operator>(const random_access_iterator &rhs) const {
		return (this->ptr > rhs.ptr);
	}

	template <typename T>
	bool	random_access_iterator<T>::operator>=(const random_access_iterator &rhs) const {
		return (this->ptr >= rhs.ptr);
	}

	template <typename T>
	random_access_iterator<T> &random_access_iterator<T>::operator++() {
		++this->ptr;
		return (*this);
	}

	template <typename T>
	random_access_iterator<T>random_access_iterator<T>::operator++(int) {
		random_access_iterator<T>	tmp(*this);
		++this->ptr;
		return (tmp);
	}

	template <typename T>
	random_access_iterator<T>& random_access_iterator<T>::operator--() {
		--this->ptr;
		return (*this);
	}

	template <typename T>
	random_access_iterator<T> random_access_iterator<T>::operator--(int) {
		random_access_iterator<T>	tmp(*this);
		--this->ptr;
		return (tmp);
	}

	template <typename T>
	typename random_access_iterator<T>::difference_type
		random_access_iterator<T>::operator-(const random_access_iterator &rhs) const {
		return (this->ptr - rhs.ptr);
	}

	template <typename T>
	random_access_iterator<T> random_access_iterator<T>::operator+(difference_type n) const {
		return (random_access_iterator(this->ptr + n));
	}

	template <typename T>
	random_access_iterator<T>random_access_iterator<T>::operator-(difference_type n) const {
		return (random_access_iterator(this->ptr - n));
	}

}
#endif
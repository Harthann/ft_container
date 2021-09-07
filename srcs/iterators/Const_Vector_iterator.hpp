#ifndef CONST_VECTOR_ITERATOR_HPP
#define CONST_VECTOR_ITERATOR_HPP

#include "random_access_it.hpp"
#include <cstddef>

namespace ft {

	template <class T>
	class const_vector_iterator : public random_access_iterator<T>
	{
		protected:
		
			typedef random_access_iterator<T> __it__;
			const_vector_iterator(T *src) : random_access_iterator<T>(src) {};
		
		public:
			const_vector_iterator(void) : random_access_iterator<T>() {};
			const_vector_iterator(const random_access_iterator<T> &src) : random_access_iterator<T>(src) {};

			typedef const T&		reference;
			typedef const T*		pointer;
			typedef	ptrdiff_t		difference_type;

			reference					operator*(void) const;
			pointer						operator->(void) const;
			const_vector_iterator		&operator+=(difference_type n);
			const_vector_iterator		&operator-=(difference_type n);
			reference					operator[](difference_type n) const;

			difference_type				operator-(const random_access_iterator<T> &n) const {
				return __it__::operator-(n);
			};
			const_vector_iterator		operator-(difference_type n) const {
				return __it__::operator-(n);
			};
			const_vector_iterator		operator+(difference_type n) const {
				return __it__::operator+(n);
			};
			friend const_vector_iterator	operator+(difference_type n, const const_vector_iterator &rhs) {
				return rhs.operator+(n);
			};

			const_vector_iterator		&operator++(void) {
				__it__::operator++(); return *this;
			};
			const_vector_iterator		operator++(int) {
				return __it__::operator++(0);
			};
			const_vector_iterator		&operator--(void) {
				__it__::operator--(); return *this;
			};
			const_vector_iterator		operator--(int) {
				return __it__::operator--(0);
			};

			template <class Type, class A>
			friend class vector;
	};

	template <class T>
	typename const_vector_iterator<T>::reference
		const_vector_iterator<T>::operator*(void) const {
		return (*this->ptr);
	}

	template <class T>
	typename const_vector_iterator<T>::pointer
		const_vector_iterator<T>::operator->(void) const {
		return (this->ptr);
	}

	template <class T>
	const_vector_iterator<T>&
		const_vector_iterator<T>::operator+=(const_vector_iterator<T>::difference_type n) {
		this->ptr += n; return *this;
	}

	template <class T>
	const_vector_iterator<T>&
		const_vector_iterator<T>::operator-=(const_vector_iterator<T>::difference_type n) {
		this->ptr -= n; return *this;
	}

	template <class T>
	typename const_vector_iterator<T>::reference
		const_vector_iterator<T>::operator[](const_vector_iterator<T>::difference_type n) const {
		return (this->ptr[n]);
	}

} // end namespace definition

#endif

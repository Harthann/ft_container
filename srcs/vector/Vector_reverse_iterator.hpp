#ifndef VECTOR_REVERSE_ITERATOR_HPP
#define VECTOR_REVERSE_ITERATOR_HPP

#include "base_iterator.hpp"

namespace ft {

// template <class T, class A> class Vector;
template <class T> class __base_iterator;

template <class T>
class vector_reverse_iterator : public ft::__base_iterator<T>
{

	public:
		typedef T& reference;
		vector_reverse_iterator() : __base_iterator<T>(0) { };
		vector_reverse_iterator(T* ptr) : __base_iterator<T>(ptr) {} ;
		vector_reverse_iterator(const vector_reverse_iterator&);

		bool operator==(const vector_reverse_iterator<T>& base) {
			return (*base == **this) ;
		}

		vector_reverse_iterator<T> operator+(size_t i) {
			vector_reverse_iterator<T> tmp(this->ptr - i);
			return (tmp);
		}

		vector_reverse_iterator<T> operator-(size_t i) {
			vector_reverse_iterator<T> tmp(this->ptr + i);
			return (tmp);
		}

		size_t operator-(vector_reverse_iterator<T> i) {
			return (**this + *i);
		}

		size_t operator+(vector_reverse_iterator<T> i) {
			return (**this - *i);
		}

		void operator=(const vector_reverse_iterator& base) {
			this->ptr = base.ptr;
		}

		bool operator!=(const vector_reverse_iterator<T>& x) {
			return (**this != *x);
		}
		
		vector_reverse_iterator<T>& operator++() {
			this->ptr--;
			return (*this);
		}
		
		vector_reverse_iterator<T>& operator--() {
			this->ptr++;
			return (*this);
		}

		vector_reverse_iterator<T> operator++(int) {
			vector_reverse_iterator<T> tmp(*this);
			operator++();
			return (tmp);
		}

		vector_reverse_iterator<T> operator--(int) {
			vector_reverse_iterator<T> tmp(*this);
			operator--();
			return (tmp);
		}

		using __base_iterator<T>::operator*;
		// using __base_iterator<T>::operator--;
		// using __base_iterator<T>::operator++;
};

//###################################
//##	CONSTRUCTOR/DESTRUCTOR		#
//###################################

template <class T>
vector_reverse_iterator<T>::vector_reverse_iterator(const vector_reverse_iterator<T>& base)
{
	this->ptr = base.ptr;
}

//###################################
//#		CONST VERSION OF ITERATOR	#
//###################################

} // end namespace definition

#endif
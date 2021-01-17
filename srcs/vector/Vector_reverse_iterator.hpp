#ifndef VECTOR_REVERSE_ITERATOR_HPP
#define VECTOR_REVERSE_ITERATOR_HPP

#include "base_iterator.hpp"

namespace ftc {

// template <class T, class A> class Vector;
template <class T> class __base_iterator;

template <class T>
class Vector_reverse_iterator : public ftc::__base_iterator<T>
{

	public:
		typedef T& reference;
		Vector_reverse_iterator() : __base_iterator<T>(nullptr) { };
		Vector_reverse_iterator(T* ptr) : __base_iterator<T>(ptr) {} ;
		Vector_reverse_iterator(const Vector_reverse_iterator&);

		bool operator==(const Vector_reverse_iterator<T>& base) {
			return (*base == **this) ;
		}

		Vector_reverse_iterator<T> operator+(size_t i) {
			Vector_reverse_iterator<T> tmp(this->ptr - i);
			return (tmp);
		}

		Vector_reverse_iterator<T> operator-(size_t i) {
			Vector_reverse_iterator<T> tmp(this->ptr + i);
			return (tmp);
		}

		size_t operator-(Vector_reverse_iterator<T> i) {
			return (**this + *i);
		}

		size_t operator+(Vector_reverse_iterator<T> i) {
			return (**this - *i);
		}

		void operator=(const Vector_reverse_iterator& base) {
			this->ptr = base.ptr;
		}

		bool operator!=(const Vector_reverse_iterator<T>& x) {
			return (**this != *x);
		}
		
		Vector_reverse_iterator<T>& operator++() {
			this->ptr--;
			return (*this);
		}
		
		Vector_reverse_iterator<T>& operator--() {
			this->ptr++;
			return (*this);
		}

		Vector_reverse_iterator<T> operator++(int) {
			Vector_reverse_iterator<T> tmp(*this);
			operator++();
			return (tmp);
		}

		Vector_reverse_iterator<T> operator--(int) {
			Vector_reverse_iterator<T> tmp(*this);
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
Vector_reverse_iterator<T>::Vector_reverse_iterator(const Vector_reverse_iterator<T>& base)
{
	this->ptr = base.ptr;
}

//###################################
//#		CONST VERSION OF ITERATOR	#
//###################################

} // end namespace definition

#endif
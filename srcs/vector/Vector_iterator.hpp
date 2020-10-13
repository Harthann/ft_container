#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include "base_iterator.hpp"

namespace ftc {

// template <class T, class A> class Vector;
template <class T> class __base_iterator;

template <class T>
class Vector_iterator : public ftc::__base_iterator<T>
{

	public:
		typedef T& reference;
		Vector_iterator() : __base_iterator<T>(nullptr) { };
		Vector_iterator(T* ptr) : __base_iterator<T>(ptr) {} ;
		Vector_iterator(const Vector_iterator&);

		// Vector_iterator<T>& operator++() {
		// 	this->ptr++;
		// 	return (*this);
		// }

		// Vector_iterator<T> operator++(int) {
		// 	Vector_iterator<T> tmp(*this);
		// 	operator++();
		// 	return (tmp);
		// }

		// Vector_iterator<T>& operator--() {
		// 	ptr--;
		// 	return (*this);
		// }

		// Vector_iterator<T> operator--(int) {
		// 	Vector_iterator<T> tmp(*this);
		// 	operator--();
		// 	return (tmp);
		// }

		bool operator==(const Vector_iterator<T>& base) {
			return (*base == **this) ;
		}

		Vector_iterator<T> operator+(size_t i) {
			Vector_iterator<T> tmp(this->ptr + i);
			return (tmp);
		}

		Vector_iterator<T> operator-(size_t i) {
			Vector_iterator<T> tmp(this->ptr - i);
			return (tmp);
		}

		size_t operator-(Vector_iterator<T> i) {
			return (**this - *i);
		}

		void operator=(const Vector_iterator& base) {
			this->ptr = base.ptr;
		}

		bool operator!=(const Vector_iterator<T>& x) {
			return (**this != *x);
		}
		
		using __base_iterator<T>::operator*;
		using __base_iterator<T>::operator--;
		using __base_iterator<T>::operator++;
		// reference operator*() const {
		// 	return (*this->ptr);
		// }

	// private:
	// 	T *ptr;
};

//###################################
//##	CONSTRUCTOR/DESTRUCTOR		#
//###################################

template <class T>
Vector_iterator<T>::Vector_iterator(const Vector_iterator<T>& base)
{
	this->ptr = base.ptr;
}

//###################################
//#		CONST VERSION OF ITERATOR	#
//###################################

} // end namespace definition

#endif
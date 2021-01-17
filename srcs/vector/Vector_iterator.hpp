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

		bool operator==(const Vector_iterator<T>& base) {
			return (base.ptr == this->ptr) ;
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

		size_t operator+(Vector_iterator<T> i) {
			return (**this + *i);
		}

		void operator=(const Vector_iterator& base) {
			this->ptr = base.ptr;
		}

		bool operator!=(const Vector_iterator<T>& x) {
			return (this->ptr != x.ptr);
		}
		
		using __base_iterator<T>::operator*;
		using __base_iterator<T>::operator--;
		using __base_iterator<T>::operator++;
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
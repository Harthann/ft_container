#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include "base_iterator.hpp"

namespace ft {

// template <class T, class A> class Vector;
template <class T> class __base_iterator;

template <class T>
class vector_iterator : public ft::__base_iterator<T>
{

	public:
		typedef T& reference;
		vector_iterator() : __base_iterator<T>(0) { };
		vector_iterator(T* ptr) : __base_iterator<T>(ptr) {} ;
		vector_iterator(const vector_iterator&);

		bool operator==(const vector_iterator<T>& base) {
			return (base.ptr == this->ptr) ;
		}

		vector_iterator<T> operator+(size_t i) {
			vector_iterator<T> tmp(this->ptr + i);
			return (tmp);
		}

		vector_iterator<T> operator-(size_t i) {
			vector_iterator<T> tmp(this->ptr - i);
			return (tmp);
		}

		size_t operator-(vector_iterator<T> i) {
			return (**this - *i);
		}

		size_t operator+(vector_iterator<T> i) {
			return (**this + *i);
		}

		void operator=(const vector_iterator& base) {
			this->ptr = base.ptr;
		}

		bool operator!=(const vector_iterator<T>& x) {
			return (this->ptr != x.ptr);
		}
		
		reference operator*() const {
			return (*this->ptr);
		}

		// using __base_iterator<T>::operator*;
		using __base_iterator<T>::operator--;
		using __base_iterator<T>::operator++;
};

//###################################
//##	CONSTRUCTOR/DESTRUCTOR		#
//###################################

template <class T>
vector_iterator<T>::vector_iterator(const vector_iterator<T>& base)
{
	this->ptr = base.ptr;
}

//###################################
//#		CONST VERSION OF ITERATOR	#
//###################################

} // end namespace definition

#endif
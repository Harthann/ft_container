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
		typedef std::ptrdiff_t	difference_type;
		typedef T			value_type;
		typedef value_type*	pointer;
		typedef value_type&	reference;
		typedef ft::random_access_iterator_tag iterator_category;
		vector_iterator() : __base_iterator<T>(0) { };
		vector_iterator(T* ptr) : __base_iterator<T>(ptr) {} ;
		vector_iterator(const vector_iterator&);

		bool operator==(const vector_iterator<T>& base) {
			return (base.ptr == this->ptr) ;
		}
		
		bool operator!=(const vector_iterator<T>& base) {
			return (this->ptr != base.ptr);
		}
		
		reference operator*() {
			return (*this->ptr);
		}

		pointer operator->() {
			return (this->ptr);
		}

		using __base_iterator<T>::operator--;
		using __base_iterator<T>::operator++;
		
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
		
		vector_iterator<T> &operator+=(const int &n) {
			this->ptr += n;
			return (*this);
		}
		
		vector_iterator<T> &operator-=(const int &n) {
			this->ptr -= n;
			return (*this);
		}

		bool	operator<(const vector_iterator<T> &rhs) {
			return (this->ptr < &(*rhs));
		}

		bool	operator>(const vector_iterator<T> &rhs) {
			return (this->ptr > &(*rhs));
		}
		
		bool	operator<=(const vector_iterator<T> &rhs) {
			return (this->ptr <= &(*rhs));
		}
		
		bool	operator>=(const vector_iterator<T> &rhs) {
			return (this->ptr >= &(*rhs));
		}
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

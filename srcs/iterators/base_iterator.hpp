#ifndef BASE_ITERATOR_HPP
#define BASE_ITERATOR_HPP

namespace ft {

template <class T>
class __base_iterator
{

	public:
		typedef T& reference;
		__base_iterator() : ptr(nullptr) { };
		__base_iterator(T* ptr) : ptr(ptr) {} ;
		__base_iterator(const __base_iterator&);
		size_t distance(__base_iterator<T> start, __base_iterator<T> end);

		__base_iterator<T>& operator++() {
			this->ptr++;
			return (*this);
		}

		__base_iterator<T> operator++(int) {
			__base_iterator<T> tmp(*this);
			operator++();
			return (tmp);
		}

		__base_iterator<T>& operator--() {
			ptr--;
			return (*this);
		}

		__base_iterator<T> operator--(int) {
			__base_iterator<T> tmp(*this);
			operator--();
			return (tmp);
		}

		bool operator==(const __base_iterator<T>& base) {
			return (base.ptr == this->ptr) ;
		}

		__base_iterator<T> operator+(size_t i) {
			__base_iterator<T> tmp(ptr + i);
			return (tmp);
		}

		__base_iterator<T> operator-(size_t i) {
			__base_iterator<T> tmp(ptr - i);
			return (tmp);
		}

		size_t operator-(__base_iterator<T> i) {
			return (ptr - i.ptr);
		}

		void operator=(const __base_iterator& base) {
			ptr = base.ptr;
		}

		bool operator!=(const __base_iterator<T>& x) {
			return (this->ptr != x.ptr);
		}
		

		reference operator*() const {
			return (*ptr);
		}

	protected:
		T *ptr;
};

//###################################
//##	CONSTRUCTOR/DESTRUCTOR		#
//###################################

template <class T>
__base_iterator<T>::__base_iterator(const __base_iterator& base)
{
	this->ptr = base.ptr;
}

//###################################
//#		CONST VERSION OF ITERATOR	#
//###################################

template <class T>
size_t __base_iterator<T>::distance(__base_iterator<T> start, __base_iterator<T> end)
{
	size_t i = 0;
	__base_iterator<T> tmp = start;

	while (tmp != end)
	{
		i++;
		tmp++;
	}
	return (i);
}

} // end namespace definition

#endif
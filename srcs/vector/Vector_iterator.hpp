#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

namespace ftc {

// template <class T, class A> class Vector;

template <class T>
class Vector_iterator
{
	typedef T& reference;

	public:
		Vector_iterator() : ptr(nullptr) { };
		Vector_iterator(T* ptr) : ptr(ptr) {} ;
		Vector_iterator(const Vector_iterator&);

		Vector_iterator<T>& operator++() {
			this->ptr++;
			return (*this);
		}

		Vector_iterator<T> operator++(int) {
			Vector_iterator<T> tmp(*this);
			operator++();
			return (tmp);
		}

		Vector_iterator<T>& operator--() {
			ptr--;
			return (*this);
		}

		Vector_iterator<T> operator--(int) {
			Vector_iterator<T> tmp(*this);
			operator--();
			return (tmp);
		}

		bool operator==(const Vector_iterator<T>& base) {
			return (base.ptr == this->ptr) ;
		}

		Vector_iterator<T> operator+(int i) {
			Vector_iterator<T> tmp(ptr + i);
			return (tmp);
		}

		Vector_iterator<T> operator-(int i) {
			Vector_iterator<T> tmp(ptr - i);
			return (tmp);
		}

		size_t operator-(Vector_iterator<T> i) {
			return (ptr - i.ptr);
		}

		void operator=(const Vector_iterator& base) {
			ptr = base.ptr;
		}

		bool operator!=(const Vector_iterator<T>& x) {
			return (this->ptr != x.ptr);
		}
		

		reference operator*() const {
			return (*ptr);
		}

	private:
		T *ptr;
};

//###################################
//##	CONSTRUCTOR/DESTRUCTOR		#
//###################################

template <class T>
Vector_iterator<T>::Vector_iterator(const Vector_iterator& base)
{
	this->ptr = base.ptr;
}

//###################################
//#		CONST VERSION OF ITERATOR	#
//###################################

} // end namespace definition

#endif
#ifndef CONST_VECTOR_ITERATOR_HPP
#define CONST_VECTOR_ITERATOR_HPP

#include "random_access_it.hpp"

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

			reference			operator*(void) const;
			pointer				operator->(void) const;
			const_vector_iterator		&operator+=(difference_type n);
			const_vector_iterator		&operator-=(difference_type n);
			reference			operator[](difference_type n) const;

			difference_type		operator-(const random_access_iterator<T> &n) const { return __it__::operator-(n); };
			const_vector_iterator		operator-(difference_type n) const { return __it__::operator-(n); };
			const_vector_iterator		operator+(difference_type n) const { return __it__::operator+(n); };
			friend const_vector_iterator	operator+(difference_type n, const const_vector_iterator &rhs) { return rhs.operator+(n); };

			const_vector_iterator		&operator++(void) { __it__::operator++(); return *this; };
			const_vector_iterator		operator++(int) { return __it__::operator++(0); };
			const_vector_iterator		&operator--(void) { __it__::operator--(); return *this; };
			const_vector_iterator		operator--(int) { return __it__::operator--(0); };

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
// template <class T>
// class const_vector_iterator
// {

// 	public:
// 		typedef std::ptrdiff_t					difference_type;
// 		typedef const T							value_type;
// 		typedef value_type*						pointer;
// 		typedef const value_type*				const_pointer;
// 		typedef value_type&						reference;
// 		typedef const value_type&				const_reference;
// 		typedef ft::random_access_iterator_tag	iterator_category;

// 		template <class T1, class A>
// 		friend class vector;

// 		template <class T1>
// 		friend class vector_iterator;

// 		const_vector_iterator() : ptr(0) { };
// 		const_vector_iterator(value_type* ptr) : ptr(ptr) {} ;
// 		const_vector_iterator(const const_vector_iterator<T>& x) {
// 			ptr = x.ptr;
// 		};
// 		const_vector_iterator(const vector_iterator<T>& x) {
// 			ptr = reinterpret_cast<pointer>(x.ptr);
// 		};

// 		operator vector_iterator<T>() {
// 			return vector_iterator<T>(this->ptr);
// 		};

// 		const_vector_iterator<T> &operator=(const const_vector_iterator<T> & x) {
// 			ptr = reinterpret_cast<pointer>(x.ptr);
// 			return *this;
// 		};

// 		bool operator==(const const_vector_iterator<T> & base) const {
// 			return (base.ptr == this->ptr) ;
// 		}
		
// 		bool operator!=(const const_vector_iterator<T> & base) const {
// 			return (!operator==(base));
// 		}
		
// 		reference operator*() {
// 			return (*this->ptr);
// 		}

// 		const_reference operator*() const {
// 			return (*this->ptr);
// 		}

// 		pointer operator->() {
// 			return (this->ptr);
// 		}

// 		const_pointer operator->() const {
// 			return (this->ptr);
// 		}

// 		const_vector_iterator& operator++() {
// 			this->ptr++;
// 			return (*this);
// 		}

// 		const_vector_iterator& operator++() const {
// 			this->ptr++;
// 			return (*this);
// 		}

// 		const_vector_iterator operator++(int) {
// 			const_vector_iterator tmp(*this);
// 			operator++();
// 			return (tmp);
// 		}

// 		const_vector_iterator operator++(int) const {
// 			const_vector_iterator tmp(*this);
// 			operator++();
// 			return (tmp);
// 		}

// 		const_vector_iterator& operator--() {
// 			ptr--;
// 			return (*this);
// 		}

// 		const_vector_iterator& operator--() const {
// 			ptr--;
// 			return (*this);
// 		}

// 		const_vector_iterator operator--(int) {
// 			const_vector_iterator tmp(*this);
// 			operator--();
// 			return (tmp);
// 		}

// 		const_vector_iterator operator--(int) const {
// 			const_vector_iterator tmp(*this);
// 			operator--();
// 			return (tmp);
// 		}
		
// 		const_vector_iterator operator+(size_t i) const {
// 			const_vector_iterator tmp(this->ptr + i);
// 			return (tmp);
// 		}

// 		const_vector_iterator operator-(size_t i) const {
// 			const_vector_iterator tmp(this->ptr - i);
// 			return (tmp);
// 		}

// 		difference_type operator-(const const_vector_iterator<T> &i) const {
// 			return (this->ptr - i.ptr);
// 		}

// 		difference_type operator+(const const_vector_iterator<T> &i) const {
// 			return (this->ptr + i.ptr);
// 		}

// 		difference_type operator-(const vector_iterator<T> &i) const {
// 			return (this->ptr - i.ptr);
// 		}

// 		difference_type operator+(const vector_iterator<T> &i) const {
// 			return (this->ptr + i.ptr);
// 		}

// 		const_vector_iterator &operator+=(const int &n) {
// 			this->ptr += n;
// 			return (*this);
// 		}
		
// 		const_vector_iterator &operator-=(const int &n) {
// 			this->ptr -= n;
// 			return (*this);
// 		}

// 		value_type &operator[](size_t i) {
// 			return this->ptr[i];
// 		}

// 		const value_type &operator[](size_t i) const {
// 			return this->ptr[i];
// 		}

// 		bool	operator<(const const_vector_iterator<T> &rhs) const {
// 			return (this->ptr < &(*rhs));
// 		}

// 		bool	operator>(const const_vector_iterator<T> &rhs) const {
// 			return (this->ptr > &(*rhs));
// 		}
		
// 		bool	operator<=(const const_vector_iterator<T> &rhs) const {
// 			return (this->ptr <= &(*rhs));
// 		}
		
// 		bool	operator>=(const const_vector_iterator<T> &rhs) const {
// 			return (this->ptr >= &(*rhs));
// 		}

// 	private:
// 		value_type *ptr;
// };

// //###################################
// //##	CONSTRUCTOR/DESTRUCTOR		#
// //###################################

// template <class T>
// ft::const_vector_iterator<T> operator+(size_t lhs, ft::const_vector_iterator<T> rhs)
// {
// 	return rhs + lhs;
// }

// template <class T>
// ft::const_vector_iterator<T> operator-(size_t lhs, ft::const_vector_iterator<T> rhs)
// {
// 	return rhs - lhs;
// }

// template <class T>
// bool	operator<(const vector_iterator<T> &lhs, const const_vector_iterator<T> &rhs) {
// 	return (&*lhs < &*rhs);
// }

// template <class T>
// bool	operator>(const vector_iterator<T> &lhs, const const_vector_iterator<T> &rhs) {
// 		return (&*lhs > &*rhs);
// }
	
// template <class T>
// bool	operator<=(const vector_iterator<T> &lhs, const const_vector_iterator<T> &rhs) {
// 	return (&*lhs <= &*rhs);
// }
	
// template <class T>
// bool	operator>=(const vector_iterator<T> &lhs, const const_vector_iterator<T> &rhs) {
// 	return (&*lhs >= &*rhs);
// }

//###################################
//#		CONST VERSION OF ITERATOR	#
//###################################

} // end namespace definition

#endif

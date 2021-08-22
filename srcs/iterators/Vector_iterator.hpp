#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include "random_access_it.hpp"

namespace ft {

	template <class T>
	class vector_iterator : public random_access_iterator<T>
	{
		protected:
		
			typedef random_access_iterator<T> __it__;
		
		public:
			vector_iterator(T *src) : random_access_iterator<T>(src) {};
			vector_iterator(void) : random_access_iterator<T>() {};
			vector_iterator(const random_access_iterator<T> &src) : random_access_iterator<T>(src) {};
			vector_iterator(const vector_iterator &src) : random_access_iterator<T>(src) {};

			typedef T&			reference;
			typedef T*			pointer;
			typedef ptrdiff_t	difference_type;

			reference			operator*(void) const;
			pointer				operator->(void) const;
			vector_iterator			&operator+=(difference_type n);
			vector_iterator			&operator-=(difference_type n);
			reference			operator[](difference_type n) const;

			difference_type		operator-(const random_access_iterator<T> &n) const { return __it__::operator-(n); };
			vector_iterator			operator-(difference_type n) const { return __it__::operator-(n); };
			vector_iterator			operator+(difference_type n) const { return __it__::operator+(n); };
			friend vector_iterator		operator+(difference_type n, const vector_iterator &rhs) { return rhs.operator+(n); };

			vector_iterator			&operator++(void) { __it__::operator++(); return *this; };
			vector_iterator			operator++(int) { return __it__::operator++(0); };
			vector_iterator			&operator--(void) { __it__::operator--(); return *this; };
			vector_iterator			operator--(int) { return __it__::operator--(0); };

			template <class Type, class A>
			friend class vector;
	};

template <class T>
typename vector_iterator<T>::reference
	vector_iterator<T>::operator*(void) const {
	return (*this->ptr);
}

template <class T>
typename vector_iterator<T>::pointer
	vector_iterator<T>::operator->(void) const {
	return (this->ptr);
}

template <class T>
vector_iterator<T>&
	vector_iterator<T>::operator+=(vector_iterator<T>::difference_type n) {
	this->ptr += n; return *this;
}

template <class T>
vector_iterator<T>&
	vector_iterator<T>::operator-=(vector_iterator<T>::difference_type n) {
	this->ptr -= n; return *this;
}

template <class T>
typename vector_iterator<T>::reference
	vector_iterator<T>::operator[](vector_iterator<T>::difference_type n) const {
	return (this->ptr[n]);
}

// template <class T>
// class vector_iterator
// {

// 	public:
// 		typedef std::ptrdiff_t					difference_type;
// 		typedef T								value_type;
// 		typedef value_type*						pointer;
// 		typedef const value_type*				const_pointer;
// 		typedef value_type&						reference;
// 		typedef const value_type&				const_reference;
// 		typedef ft::random_access_iterator_tag	iterator_category;

// 		template <class T1, class A>
// 		friend class vector;

// 		template <class T1>
// 		friend class const_vector_iterator;

// 		vector_iterator() : ptr(0) { };
// 		vector_iterator(value_type* ptr) : ptr(ptr) {} ;
// 		vector_iterator(const vector_iterator<T>& x) {
// 			ptr = reinterpret_cast<pointer>(x.ptr);
// 		};

// 		operator const_vector_iterator<T>() {
// 			return const_vector_iterator<T>(this->ptr);
// 		};

// 		vector_iterator &operator=(const vector_iterator<T> & x) {
// 			ptr = reinterpret_cast<pointer>(x.ptr);
// 			return *this;
// 		};

// 		bool operator==(const vector_iterator<T> & base) const {
// 			return (base.ptr == this->ptr) ;
// 		}
		
// 		bool operator!=(const vector_iterator<T> & base) const {
// 			return (!operator==(base));
// 		}
		
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

// 		vector_iterator& operator++() {
// 			this->ptr++;
// 			return (*this);
// 		}

// 		vector_iterator& operator++() const {
// 			this->ptr++;
// 			return (*this);
// 		}

// 		vector_iterator operator++(int) {
// 			vector_iterator tmp(*this);
// 			operator++();
// 			return (tmp);
// 		}

// 		vector_iterator operator++(int) const {
// 			vector_iterator tmp(*this);
// 			operator++();
// 			return (tmp);
// 		}

// 		vector_iterator& operator--() {
// 			ptr--;
// 			return (*this);
// 		}

// 		vector_iterator& operator--() const {
// 			ptr--;
// 			return (*this);
// 		}

// 		vector_iterator operator--(int) {
// 			vector_iterator tmp(*this);
// 			operator--();
// 			return (tmp);
// 		}

// 		vector_iterator operator--(int) const {
// 			vector_iterator tmp(*this);
// 			operator--();
// 			return (tmp);
// 		}
		
// 		vector_iterator operator+(size_t i) const {
// 			vector_iterator tmp(this->ptr + i);
// 			return (tmp);
// 		}

// 		vector_iterator operator-(size_t i) const {
// 			vector_iterator tmp(this->ptr - i);
// 			return (tmp);
// 		}

// 		difference_type operator-(const vector_iterator<T> &i) const {
// 			return (this->ptr - i.ptr);
// 		}

// 		difference_type operator+(const vector_iterator<T> &i) const {
// 			return (this->ptr + i.ptr);
// 		}

// 		difference_type operator-(const const_vector_iterator<T> &i) const {
// 			return (this->ptr - i.ptr);
// 		}

// 		difference_type operator+(const const_vector_iterator<T> &i) const {
// 			return (this->ptr + i.ptr);
// 		}


// 		vector_iterator &operator+=(const int &n) {
// 			this->ptr += n;
// 			return (*this);
// 		}
		
// 		vector_iterator &operator-=(const int &n) {
// 			this->ptr -= n;
// 			return (*this);
// 		}

// 		value_type &operator[](size_t i) {
// 			return this->ptr[i];
// 		}

// 		const value_type &operator[](size_t i) const {
// 			return this->ptr[i];
// 		}

// 		bool	operator<(const vector_iterator<T> &rhs) const {
// 			return (this->ptr < &(*rhs));
// 		}

// 		bool	operator>(const vector_iterator<T> &rhs) const {
// 			return (this->ptr > &(*rhs));
// 		}
		
// 		bool	operator<=(const vector_iterator<T> &rhs) const {
// 			return (this->ptr <= &(*rhs));
// 		}
		
// 		bool	operator>=(const vector_iterator<T> &rhs) const {
// 			return (this->ptr >= &(*rhs));
// 		}

// 	private:
// 		value_type *ptr;
// };

// //###################################
// //##	CONSTRUCTOR/DESTRUCTOR		#
// //###################################

// template <class T>
// ft::vector_iterator<T> operator+(size_t lhs, ft::vector_iterator<T> rhs)
// {
// 	return rhs + lhs;
// }

// template <class T>
// ft::vector_iterator<T> operator-(size_t lhs, ft::vector_iterator<T> rhs)
// {
// 	return rhs - lhs;
// }

//###################################
//#		CONST VERSION OF ITERATOR	#
//###################################

} // end namespace definition

#endif

#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include "random_access_it.hpp"
#include <cstddef>

namespace ft {

	template <class T>
	class vector_iterator : public random_access_iterator<T>
	{
		protected:		
			typedef random_access_iterator<T> __it__;
			vector_iterator(T *src) : random_access_iterator<T>(src) {};

		public:
			vector_iterator(void) : random_access_iterator<T>() {};
			vector_iterator(const vector_iterator &src) : random_access_iterator<T>(src) {};

			typedef T&			reference;
			typedef T*			pointer;
			typedef ptrdiff_t	difference_type;

			reference			operator*(void) const;
			pointer				operator->(void) const;
			vector_iterator			&operator+=(difference_type n);
			vector_iterator			&operator-=(difference_type n);
			reference			operator[](difference_type n) const;

			difference_type		operator-(const random_access_iterator<T> &n) const {
				return __it__::operator-(n);
			};
			vector_iterator			operator-(difference_type n) const {
				return __it__::operator-(n);
			};
			vector_iterator			operator+(difference_type n) const {
				return __it__::operator+(n);
			};
			friend vector_iterator		operator+(difference_type n, const vector_iterator &rhs) {
				return rhs.operator+(n);
			};

			vector_iterator			&operator++(void) { __it__::operator++(); return *this; };
			vector_iterator			operator++(int) { return __it__::operator++(0); };
			vector_iterator			&operator--(void) { __it__::operator--(); return *this; };
			vector_iterator			operator--(int) { return __it__::operator--(0); };

			template <class Type, class A>
			friend class vector;

		private:
			vector_iterator(const random_access_iterator<T> &src) : random_access_iterator<T>(src) {};
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

} // end namespace definition

#endif

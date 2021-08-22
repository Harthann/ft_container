#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

namespace ft {

template <class T, bool B = false>
class vector_iterator
{

	public:
		typedef std::ptrdiff_t					difference_type;
		typedef typename ft::is_const_if<B, T>::value_type	value_type;
		typedef value_type*						pointer;
		typedef const value_type*				const_pointer;
		typedef value_type&						reference;
		typedef const value_type&				const_reference;
		typedef ft::random_access_iterator_tag	iterator_category;

		template <class T1, class A>
		friend class vector;

		template <class Type>
		operator vector_iterator<Type, true>() {
			return (vector_iterator<Type, true>(this->ptr));
		}

		vector_iterator() : ptr(0) { };
		vector_iterator(value_type* ptr) : ptr(ptr) {} ;
		vector_iterator(const vector_iterator<T>& x) {
			ptr = reinterpret_cast<pointer>(x.ptr);
		};

		vector_iterator &operator=(const vector_iterator<T> & x) {
			ptr = reinterpret_cast<pointer>(x.ptr);
			return *this;
		};

		bool operator==(const vector_iterator<T, true> & base) const {
			return (base.ptr == this->ptr) ;
		}
		
		bool operator!=(const vector_iterator<T,true> & base) const {
			return (!operator==(base));
		}
		
		reference operator*() {
			return (*this->ptr);
		}

		const_reference operator*() const {
			return (*this->ptr);
		}

		pointer operator->() {
			return (this->ptr);
		}

		const_pointer operator->() const {
			return (this->ptr);
		}

		vector_iterator& operator++() {
			this->ptr++;
			return (*this);
		}

		vector_iterator& operator++() const {
			this->ptr++;
			return (*this);
		}

		vector_iterator operator++(int) {
			vector_iterator tmp(*this);
			operator++();
			return (tmp);
		}

		vector_iterator operator++(int) const {
			vector_iterator tmp(*this);
			operator++();
			return (tmp);
		}

		vector_iterator& operator--() {
			ptr--;
			return (*this);
		}

		vector_iterator& operator--() const {
			ptr--;
			return (*this);
		}

		vector_iterator operator--(int) {
			vector_iterator tmp(*this);
			operator--();
			return (tmp);
		}

		vector_iterator operator--(int) const {
			vector_iterator tmp(*this);
			operator--();
			return (tmp);
		}
		
		vector_iterator operator+(size_t i) {
			vector_iterator tmp(this->ptr + i);
			return (tmp);
		}

		vector_iterator operator+(size_t i) const {
			vector_iterator tmp(this->ptr + i);
			return (tmp);
		}

		vector_iterator operator-(size_t i) {
			vector_iterator tmp(this->ptr - i);
			return (tmp);
		}

		vector_iterator operator-(size_t i) const {
			vector_iterator tmp(this->ptr - i);
			return (tmp);
		}

		difference_type operator-(vector_iterator<T, true> i) {
			return (this->ptr - i.ptr);
		}

		difference_type operator-(const vector_iterator<T, true> i) const {
			return (this->ptr - i.ptr);
		}

		difference_type operator+(vector_iterator i) {
			return (this->ptr + i.ptr);
		}

		vector_iterator &operator+=(const int &n) {
			this->ptr += n;
			return (*this);
		}
		
		vector_iterator &operator-=(const int &n) {
			this->ptr -= n;
			return (*this);
		}

		value_type &operator[](size_t i) {
			return this->ptr[i];
		}

		const value_type &operator[](size_t i) const {
			return this->ptr[i];
		}

		bool	operator<(const vector_iterator<T, true> &rhs) const {
			return (this->ptr < &(*rhs));
		}

		bool	operator>(const vector_iterator<T, true> &rhs) const {
			return (this->ptr > &(*rhs));
		}
		
		bool	operator<=(const vector_iterator<T, true> &rhs) const {
			return (this->ptr <= &(*rhs));
		}
		
		bool	operator>=(const vector_iterator<T, true> &rhs) const {
			return (this->ptr >= &(*rhs));
		}

	private:
		template <class, bool> friend class vector_iterator;
		value_type *ptr;
};

//###################################
//##	CONSTRUCTOR/DESTRUCTOR		#
//###################################

template <class T>
ft::vector_iterator<T> operator+(size_t lhs, ft::vector_iterator<T> rhs)
{
	return rhs + lhs;
}

template <class T>
ft::vector_iterator<T> operator-(size_t lhs, ft::vector_iterator<T> rhs)
{
	return rhs - lhs;
}

//###################################
//#		CONST VERSION OF ITERATOR	#
//###################################

} // end namespace definition

#endif

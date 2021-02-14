#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

namespace ft {

template <class T>
class vector_iterator
{

	public:
		typedef std::ptrdiff_t					difference_type;
		typedef T								value_type;
		typedef value_type*						pointer;
		typedef const value_type*				const_pointer;
		typedef value_type&						reference;
		typedef const value_type&				const_reference;
		typedef ft::random_access_iterator_tag	iterator_category;

		vector_iterator() : ptr(0) { };
		vector_iterator(T* ptr) : ptr(ptr) {} ;
		vector_iterator(const vector_iterator&);

		bool operator==(const vector_iterator<T>& base) const {
			return (base.ptr == this->ptr) ;
		}
		
		bool operator!=(const vector_iterator<T>& base) const {
			return (this->ptr != base.ptr);
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

		vector_iterator<T>& operator++() {
			this->ptr++;
			return (*this);
		}

		vector_iterator<T> operator++(int) {
			vector_iterator<T> tmp(*this);
			operator++();
			return (tmp);
		}

		vector_iterator<T>& operator--() {
			ptr--;
			return (*this);
		}

		vector_iterator<T> operator--(int) {
			vector_iterator<T> tmp(*this);
			operator--();
			return (tmp);
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
		
		vector_iterator<T> &operator+=(const int &n) {
			this->ptr += n;
			return (*this);
		}
		
		vector_iterator<T> &operator-=(const int &n) {
			this->ptr -= n;
			return (*this);
		}

		bool	operator<(const vector_iterator<T> &rhs) const {
			return (this->ptr < &(*rhs));
		}

		bool	operator>(const vector_iterator<T> &rhs) const {
			return (this->ptr > &(*rhs));
		}
		
		bool	operator<=(const vector_iterator<T> &rhs) const {
			return (this->ptr <= &(*rhs));
		}
		
		bool	operator>=(const vector_iterator<T> &rhs) const {
			return (this->ptr >= &(*rhs));
		}

	private:
		T *ptr;
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

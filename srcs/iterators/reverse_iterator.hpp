#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

namespace ft {

	template <class Iterator>
class reverse_iterator {
	protected:
		typedef Iterator	super;
		Iterator _base;
	public:
		typedef Iterator							iterator_type;
		typedef typename super::difference_type		difference_type;
		typedef typename super::reference			reference;
		typedef typename super::pointer				pointer;

		reverse_iterator(void);
		reverse_iterator(Iterator x);
		template <class U> reverse_iterator(const reverse_iterator<U> &u);
		template <class U> reverse_iterator &operator=(const reverse_iterator<U> &u);
		Iterator base(void) const { return this->_base; };

		reference			operator*(void) const { return (--super(this->_base)).operator*(); };
		pointer				operator->(void) const { return &this->operator*(); };

		reverse_iterator	&operator++(void) { this->_base.operator--(); return *this; };
		reverse_iterator	operator++(int) { return reverse_iterator(this->_base.operator--(0)); };
		reverse_iterator	&operator--(void) { this->_base.operator++(); return *this; };
		reverse_iterator	operator--(int) { return reverse_iterator(this->_base.operator++(0)); };

		template <class U>
		difference_type		operator-(const reverse_iterator<U> &u) { return u.base().operator-(this->_base); };
		reverse_iterator	operator+ (difference_type n) const { return reverse_iterator(this->_base.operator-(n)); };
		reverse_iterator	&operator+=(difference_type n) { this->_base.operator-=(n); return *this; };
		reverse_iterator	operator- (difference_type n) const { return reverse_iterator(this->_base.operator+(n)); };
		reverse_iterator	&operator-=(difference_type n) { this->_base.operator+=(n); return *this; };
		reference			operator[](difference_type n) const { return *this->operator+(n); };

		friend reverse_iterator	operator+(difference_type n, const reverse_iterator &rhs)
			{ return rhs.operator+(n); };

		template <class U> bool	operator==(const reverse_iterator<U> &rhs) const { return this->_base.operator==(rhs.base()); };
		template <class U> bool	operator!=(const reverse_iterator<U> &rhs) const { return this->_base.operator!=(rhs.base()); };
		template <class U> bool	operator< (const reverse_iterator<U> &rhs) const { return this->_base.operator> (rhs.base()); };
		template <class U> bool	operator<=(const reverse_iterator<U> &rhs) const { return this->_base.operator>=(rhs.base()); };
		template <class U> bool	operator> (const reverse_iterator<U> &rhs) const { return this->_base.operator< (rhs.base()); };
		template <class U> bool	operator>=(const reverse_iterator<U> &rhs) const { return this->_base.operator<=(rhs.base()); };

	}; // ************************************************** class ReverseIte end //

	template <class Iterator>
	reverse_iterator<Iterator>::reverse_iterator(void) : _base() { };

	template <class Iterator>
	reverse_iterator<Iterator>::reverse_iterator(Iterator x) : _base(x) { };

	template <class Iterator> template <class U>
	reverse_iterator<Iterator>::reverse_iterator(const reverse_iterator<U> &u) : _base(u.base()) { };

	template <class Iterator> template <class U>
	reverse_iterator<Iterator>	&reverse_iterator<Iterator>::operator=(const reverse_iterator<U> &u) {
		if (reinterpret_cast<const void *>(this) == reinterpret_cast<const void *>(&u))
			return (*this);
		this->_base = u.base();
		return (*this);
};

// 	template <class T, class Comp, bool B> class map_iterator;
// 	template <class T, bool B> class list_iterator;

// 	template <class Iter>
// 	class reverse_iterator
// 	{

// 		public:
// 			typedef Iter													iterator_type;
// 			typedef typename ft::iterator_traits<Iter>::difference_type		difference_type;
// 			typedef typename ft::iterator_traits<Iter>::value_type			value_type;
// 			typedef typename ft::iterator_traits<Iter>::pointer				pointer;
// 			typedef typename ft::iterator_traits<Iter>::reference			reference;
// 			typedef const value_type&											const_reference;
// 			typedef const value_type*											const_pointer;
// 			typedef typename ft::iterator_traits<Iter>::iterator_category	iterator_category;

// 			reverse_iterator() : ptr() { };
// 			reverse_iterator(pointer &ptr) : ptr(ptr) {} ;
// 			reverse_iterator(const iterator_type &base) : ptr(base) {};
// 			reverse_iterator(const reverse_iterator<Iter> &);

// 			template <class T, class Comp>
// 			operator reverse_iterator<ft::map_iterator<T, Comp, true> >() {
// 				return (reverse_iterator<ft::map_iterator<T, Comp, true> >(this->ptr));
// 			}

// 			template <class T>
// 			operator reverse_iterator<ft::const_vector_iterator<T> >() {
// 				return (reverse_iterator<ft::const_vector_iterator<T> >(this->ptr));
// 			}

// 			bool operator==(const reverse_iterator<Iter>& base) const {
// 				return (base.ptr == ptr);
// 			}

// 			bool operator!=(const reverse_iterator<Iter>& x) const {
// 				return (x.ptr != ptr);
// 			}

// 			reference operator*() {
// 				Iter tmp = ptr;
// 				return *--tmp;
// 			}

// 			const_reference operator*() const {
// 				return (*ptr);
// 			}

// 			pointer operator->() {
// 				Iter tmp = ptr;
// 				--tmp;
// 				return (tmp.operator->());
// 			}

// 			const_pointer operator->() const {
// 				return (ptr.operator->());
// 			}

// 			reverse_iterator<Iter> operator+(size_t n ) const {
// 				reverse_iterator<Iter> tmp(ptr - n);
// 				return (tmp);
// 			}

// 			reverse_iterator<Iter> operator-(size_t n ) const {
// 				reverse_iterator<Iter> tmp(ptr + n);
// 				return (tmp);
// 			}

// 			// difference_type operator-(const reverse_iterator<Iter> x) const {
// 			// 	return (this->ptr + x.ptr);
// 			// }

// 			// difference_type operator+(const reverse_iterator<Iter> x) const {
// 			// 	return (this->ptr - x.ptr);
// 			// }

// 			void operator=(const reverse_iterator& base) {
// 				this->ptr = base.ptr;
// 			}
			
// 			reverse_iterator<Iter>& operator++() {
// 				--ptr;
// 				return (*this);
// 			}
			
// 			reverse_iterator<Iter>& operator--() {
// 				++ptr;
// 				return (*this);
// 			}

// 			reverse_iterator<Iter> operator++(int) {
// 				reverse_iterator<Iter> tmp(*this);
// 				--ptr;
// 				return (tmp);
// 			}

// 			reverse_iterator<Iter> operator--(int) {
// 				reverse_iterator<Iter> tmp(*this);
// 				++ptr;
// 				return (tmp);
// 			}

						
// 			reverse_iterator<Iter>& operator++() const {
// 				--ptr;
// 				return (*this);
// 			}
			
// 			reverse_iterator<Iter>& operator--() const {
// 				++ptr;
// 				return (*this);
// 			}

// 			reverse_iterator<Iter> operator++(int) const {
// 				reverse_iterator<Iter> tmp(*this);
// 				--ptr;
// 				return (tmp);
// 			}

// 			reverse_iterator<Iter> operator--(int) const {
// 				reverse_iterator<Iter> tmp(*this);
// 				++ptr;
// 				return (tmp);
// 			}

// 			reverse_iterator<Iter> operator-=(const int & i) {
// 				return (this->ptr + i);
// 			}

// 			reverse_iterator<Iter> operator-=(const int & i) const {
// 				return (this->ptr + i);
// 			}

// 			reverse_iterator<Iter> operator+=(const int & i) {
// 				return (this->ptr - i);
// 			}

// 			reverse_iterator<Iter> operator+=(const int & i) const {
// 				return (this->ptr - i);
// 			}

// 			value_type &operator[](size_t i) {
// 				return *this->operator+(i);
// 			}

// 			const value_type &operator[](size_t i) const {
// 				return *this->operator+(i);
// 			}

// 			bool	operator<(const reverse_iterator &rhs) const {
// 				return (&(*ptr) < &(*rhs));
// 			}

// 			bool	operator>(const reverse_iterator &rhs) const {
// 				return (&(*ptr) > &(*rhs));
// 			}
			
// 			bool	operator<=(const reverse_iterator &rhs) const {
// 				return (&(*ptr) <= &(*rhs));
// 			}
			
// 			bool	operator>=(const reverse_iterator &rhs) const {
// 				return (&(*ptr) >= &(*rhs));
// 			}

// 		private:
// 			Iter ptr;

// 	};

// 	//###################################
// 	//##	CONSTRUCTOR/DESTRUCTOR		#
// 	//###################################

// 	template <class Iter>
// 	reverse_iterator<Iter>::reverse_iterator(const reverse_iterator<Iter>& base)
// 	{
// 		this->ptr = base.ptr;
// 	}

// template <class Iter>
// ft::reverse_iterator<Iter> operator+(size_t lhs, ft::reverse_iterator<Iter> rhs)
// {
// 	return rhs + lhs;
// }

// template <class Iter>
// ft::reverse_iterator<Iter> operator-(size_t lhs, ft::reverse_iterator<Iter> rhs)
// {
// 	return rhs - lhs;
// }


} // end namespace definition

#endif
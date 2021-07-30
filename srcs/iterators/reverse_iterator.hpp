#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

namespace ft {

	template <class T, class Comp, bool B> class map_iterator;
	template <class T, bool B> class list_iterator;
	template <class T, bool B> class vector_iterator;

	template <class Iter>
	class reverse_iterator
	{

		public:
			typedef Iter													iterator_type;
			typedef typename ft::iterator_traits<Iter>::difference_type		difference_type;
			typedef typename ft::iterator_traits<Iter>::value_type			value_type;
			typedef typename ft::iterator_traits<Iter>::pointer				pointer;
			typedef typename ft::iterator_traits<Iter>::reference			reference;
			typedef const value_type&											const_reference;
			typedef const value_type*											const_pointer;
			typedef typename ft::iterator_traits<Iter>::iterator_category	iterator_category;

			reverse_iterator() : ptr() { };
			reverse_iterator(pointer &ptr) : ptr(ptr) {} ;
			reverse_iterator(const iterator_type &base) : ptr(base) {};
			reverse_iterator(const reverse_iterator&);

			template <class T, class Comp>
			operator reverse_iterator<ft::map_iterator<T, Comp, true> >() {
				return (reverse_iterator<ft::map_iterator<T, Comp, true> >(this->ptr));
			}

			template <class T>
			operator reverse_iterator<ft::list_iterator<T,true> >() {
				return (reverse_iterator<ft::list_iterator<T,true> >(this->ptr));
			}

			template <class T>
			operator reverse_iterator<ft::vector_iterator<T,true> >() {
				return (reverse_iterator<ft::vector_iterator<T,true> >(this->ptr));
			}

			bool operator==(const reverse_iterator<Iter>& base) const {
				return (base.ptr == ptr);
			}

			reference operator*() {
				Iter tmp = ptr;
				return *--tmp;
				return (*ptr);
			}

			const_reference operator*() const {
				return (*ptr);
			}

			pointer operator->() {
				Iter tmp = ptr;
				--tmp;
				return (tmp.operator->());
			}

			const_pointer operator->() const {
				return (ptr.operator->());
			}

			reverse_iterator<Iter> operator+(size_t n ) const {
				reverse_iterator<Iter> tmp(ptr - n);
				return (tmp);
			}

			reverse_iterator<Iter> operator-(size_t n ) const {
				reverse_iterator<Iter> tmp(ptr + n);
				return (tmp);
			}

			void operator=(const reverse_iterator& base) {
				this->ptr = base.ptr;
			}

			bool operator!=(const reverse_iterator<Iter>& x) const {
				return (x.ptr != ptr);
			}
			
			reverse_iterator<Iter>& operator++() {
				--ptr;
				return (*this);
			}
			
			reverse_iterator<Iter>& operator--() {
				++ptr;
				return (*this);
			}

			reverse_iterator<Iter> operator++(int) {
				reverse_iterator<Iter> tmp(*this);
				--ptr;
				return (tmp);
			}

			reverse_iterator<Iter> operator--(int) {
				reverse_iterator<Iter> tmp(*this);
				++ptr;
				return (tmp);
			}

						
			reverse_iterator<Iter>& operator++() const {
				--ptr;
				return (*this);
			}
			
			reverse_iterator<Iter>& operator--() const {
				++ptr;
				return (*this);
			}

			reverse_iterator<Iter> operator++(int) const {
				reverse_iterator<Iter> tmp(*this);
				--ptr;
				return (tmp);
			}

			reverse_iterator<Iter> operator--(int) const {
				reverse_iterator<Iter> tmp(*this);
				++ptr;
				return (tmp);
			}

			reverse_iterator<Iter> operator-=(const int & i) {
				return (this->ptr - i);
			}

			reverse_iterator<Iter> operator-=(const int & i) const {
				return (this->ptr - i);
			}

			reverse_iterator<Iter> operator+=(const int & i) {
				return (this->ptr + i);
			}

			reverse_iterator<Iter> operator+=(const int & i) const {
				return (this->ptr + i);
			}


			value_type &operator[](size_t i) {
				return ptr[i];
			}

			const value_type &operator[](size_t i) const {
				return ptr[i];
			}

			bool	operator<(const reverse_iterator &rhs) const {
				return (&(*ptr) < &(*rhs));
			}

			bool	operator>(const reverse_iterator &rhs) const {
				return (&(*ptr) > &(*rhs));
			}
			
			bool	operator<=(const reverse_iterator &rhs) const {
				return (&(*ptr) <= &(*rhs));
			}
			
			bool	operator>=(const reverse_iterator &rhs) const {
				return (&(*ptr) >= &(*rhs));
			}

		private:
			Iter ptr;

	};

	//###################################
	//##	CONSTRUCTOR/DESTRUCTOR		#
	//###################################

	template <class Iter>
	reverse_iterator<Iter>::reverse_iterator(const reverse_iterator<Iter>& base)
	{
		this->ptr = base.ptr;
	}

} // end namespace definition

#endif
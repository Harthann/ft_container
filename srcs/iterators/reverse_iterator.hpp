#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

namespace ft {

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

		reverse_iterator() : ptr(0) { };
		reverse_iterator(pointer &ptr) : ptr(ptr) {} ;
		reverse_iterator(const iterator_type &base) : ptr(base) {};
		reverse_iterator(const reverse_iterator&);

		bool operator==(const reverse_iterator<Iter>& base) const {
			return (&(*base) == &(*ptr)) ;
		}

		reference operator*() {
			return (*ptr);
		}

		const_reference operator*() const {
			return (*ptr);
		}

		reverse_iterator<Iter> operator+(difference_type n ) const {
			reverse_iterator<Iter> tmp(*(ptr - n));
			return (tmp);
		}

		reverse_iterator<Iter> operator-( difference_type n ) const {
			reverse_iterator<Iter> tmp(*(ptr + n));
			return (tmp);
		}
		//reverse_iterator<Iter>& operator+=( difference_type n );
		//reverse_iterator<Iter>& operator-=( difference_type n );
		void operator=(const reverse_iterator& base) {
			this->ptr = base.ptr;
		}

		bool operator!=(const reverse_iterator<Iter>& x) const {
			return (&(*ptr) != &(*x));
		}
		
		reverse_iterator<Iter>& operator++() {
			ptr--;
			return (*this);
		}
		
		reverse_iterator<Iter>& operator--() {
			ptr++;
			return (*this);
		}

		reverse_iterator<Iter> operator++(int) {
			reverse_iterator<Iter> tmp(*this);
			operator++();
			return (tmp);
		}

		reverse_iterator<Iter> operator--(int) {
			reverse_iterator<Iter> tmp(*this);
			operator--();
			return (tmp);
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
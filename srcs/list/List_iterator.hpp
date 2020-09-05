#ifndef LIST_ITERATOR_HPP
#define LIST_ITERATOR_HPP

namespace ftc {

template <class T> class List;
template <class T> class List_node;

template <class T>
class List_iterator
{
	typedef T& reference;

	public:
		List_iterator() : ptr(nullptr) { };
		List_iterator(List_node<T>* ptr) : ptr(ptr) {} ;
		List_iterator(const List_iterator&);

		List_iterator<T>& operator++() {
			this->ptr = this->ptr->next;
			return (*this);
		}

		List_iterator<T> operator++(int) {
			List_iterator<T> tmp(*this);
			operator++();
			return (tmp);
		}

		List_iterator<T>& operator--() {
			ptr = ptr->previous;
			return (*this);
		}

		List_iterator<T> operator--(int) {
			List_iterator<T> tmp(*this);
			operator--();
			return (tmp);
		}

		void operator=(const List_iterator& base) {
			ptr = base.ptr;
		}

		bool operator!=(const List_iterator<T>& x) {
			return (this->ptr != x.ptr);
		}
		

		reference operator*() const {
			return (ptr->data);
		}

	private:
		ftc::List_node<T> *ptr;
};

//###################################
//##	CONSTRUCTOR/DESTRUCTOR		#
//###################################

template <class T>
List_iterator<T>::List_iterator(const List_iterator& base)
{
	this->ptr = base.ptr;
}

//###################################
//#		CONST VERSION OF ITERATOR	#
//###################################

template <class T>
class List_const_iterator : ftc::List_iterator<T> {
	typedef const T& const_reference;

	public:
		List_const_iterator() : ptr(nullptr) { };
		List_const_iterator(ftc::List_node<T>* ptr) : ptr(ptr) {} ;
		List_const_iterator(const List_const_iterator&);

		List_const_iterator<T>& operator++() {
			this->ptr = this->ptr->next;
			return (*this);
		}

		List_const_iterator<T> operator++(int) {
			List_const_iterator<T> tmp(*this);
			operator++();
			return (tmp);
		}

		List_const_iterator<T>& operator--() {
			ptr = ptr->previous;
			return (*this);
		}

		List_const_iterator<T> operator--(int) {
			List_const_iterator<T> tmp(*this);
			operator--();
			return (tmp);
		}

		void operator=(const List_const_iterator& base) {
			ptr = base.ptr;
		}

		bool operator!=(const List_const_iterator<T>& x) {
			return (this->ptr != x.ptr);
		}
		

		const_reference operator*() const {
			return (ptr->data);
		}
	private:
		ftc::List_node<T> *ptr;
};

template <class T>
List_const_iterator<T>::List_const_iterator(const List_const_iterator& base)
{
	this->ptr = base.ptr;
}

} // end namespace definition

#endif
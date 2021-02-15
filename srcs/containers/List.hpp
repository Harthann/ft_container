#ifndef LIST_HPP
#define LIST_HPP
#include <iostream>
#include "list_iterator.hpp"
#include "reverse_iterator.hpp"

namespace ft {

template <class T>
struct	__list_node {
	typedef T						value_type;
	typedef T*						pointer;
	typedef T&						reference;
	typedef std::ptrdiff_t			difference_type;
	typedef __list_node<value_type>	__node;
	typedef __node*					__node_pointer;
	typedef __node&					__node_reference;

	__list_node() : data(0), next(0), previous(0) {};
	__list_node(value_type const &data, __node_pointer const &next, __node_pointer const& prev) : data(data), next(next), previous(prev) {};
	__list_node(const __list_node& base) : data(base.data), next(base.next), previous(base.previous) {};

	__list_node &operator=(const __list_node& base) {
		data = base.data;
		next = base.next;
		previous = base.previous;
	};
	// private:
		value_type		data;
		__node_pointer	next;
		__node_pointer	previous;
};

template <class T, class Alloc = std::allocator<T> >
class list
{
	public:

		typedef T														value_type;
		typedef Alloc													allocator_type;
		typedef typename allocator_type::reference						reference;
		typedef typename allocator_type::const_reference				const_reference;
		typedef typename allocator_type::pointer						pointer;
		typedef typename allocator_type::const_pointer					const_pointer;
		typedef ft::list_iterator<__list_node<T> >						iterator;
		typedef ft::list_iterator<__list_node<const T> >				const_iterator;
		typedef ft::reverse_iterator<iterator>							reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;
		typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
		typedef size_t													size_type;


		list(const allocator_type &alloc = allocator_type()) : head(), ghost(), __alloc(alloc) {};
		// list(size_type n, const value_type &val = value_type(), const allocaotr_type &alloc = allocator_type());
		// template <class InputIT>
		// list(InputIT its, InputIT ite, const allocaotr_type &alloc = allocator_type());
		// list(const list<T>& tmp);
		//list const& operator=(list const &base);
		~list() { delete head; }
		
		//		ITERATORS

		iterator begin() { return (iterator(head)); };
		iterator end() { return (iterator(ghost)); };
		reverse_iterator rbegin() { return (reverse_iterator(ghost)); };
		reverse_iterator rend() { return (reverse_iterator(head)); };
		const_iterator begin() const { return (iterator(head)); };
		const_iterator end() const { return (iterator(ghost)); };
		const_reverse_iterator rbegin() const { return (reverse_iterator(ghost)); };
		const_reverse_iterator rend() const { return (reverse_iterator(begin)); };

		//		CAPACITY

		// bool empty() const {return (std::static_cast<bool>(head)); };
		// size_type	size() const {return (length); };
		size_type	max_size() const { return (__alloc.max_size()); };

		//		ELEMENT ACCESS

		// reference front() {};
		// const_reference front() const {};
		// reference back() {};
		// const_reference back() const {};

		//		MODIFIERS

		//	assign
		void push_front(const reference tmp);
		//	pop front
		// void push_back(T tmp);
		//	push front
		//	insert
		//	erase
		//	swap
		//	resize
		//	clear

		//		OPERATIONS

		//	splice
		//	remove
		//	remove_if
		//	unique
		//	merge
		//	sort
		//	reverse

	private:
		typedef __list_node<value_type>		__node;
		typedef __list_node<value_type>*	__node_pointer;
		typedef __list_node<value_type>&	__node_reference;
		
		__node_pointer	head;
		__node_pointer	ghost;
		allocator_type	__alloc;
};



//###################################
//##	CONSTRUCTOR/DESTRUCTOR		#
//###################################

template <class T, class A>
void list<T,A>::push_front(const reference value)
{
	__node_pointer tmp = __alloc.allocate(sizeof(__list_node<value_type>));

	tmp->data = value;
	tmp->next = head ? head : ghost;
	tmp->previous = ghost;
	ghost->next = tmp;
	if (!ghost->previous)
		ghost->previous = tmp;
	if (head)
		head->previous = tmp;

}

//###############################
//##							#
//###############################

//###################
//#		ITERATOR	#
//###################

//###################
//#		OTHER		#
//###################


}
#endif
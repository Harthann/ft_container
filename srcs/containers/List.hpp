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
		typedef ft::list_iterator<value_type>							iterator;
		typedef ft::list_iterator<const value_type >					const_iterator;
		typedef ft::reverse_iterator<iterator>							reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;
		typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
		typedef size_t													size_type;


		list(const allocator_type &alloc = allocator_type()) : head(), __alloc(alloc), __node_alloc() { ghost = __node_alloc.allocate(1);};
		// list(size_type n, const value_type &val = value_type(), const allocaotr_type &alloc = allocator_type());
		// template <class InputIT>
		// list(InputIT its, InputIT ite, const allocaotr_type &alloc = allocator_type());
		// list(const list<T>& tmp);
		//list const& operator=(list const &base);
		~list() { delete head; }
		
		//		ITERATORS

		iterator begin() { return (head); };
		iterator end() { return (ghost); };
		reverse_iterator rbegin() { return (ft::prev(iterator(ghost))); };
		reverse_iterator rend() { return (ft::prev(iterator(head))); };
		const_iterator begin() const { return (head); };
		const_iterator end() const { return (ghost); };
		const_reverse_iterator rbegin() const { return (ft::prev(iterator(ghost))); };
		const_reverse_iterator rend() const { return (ft::prev(iterator(begin))); };

		//		CAPACITY

		// bool empty() const {return (std::static_cast<bool>(head)); };
		// size_type	size() const {return (length); };
		size_type	max_size() const { return (__node_allocator().max_size()); };

		//		ELEMENT ACCESS

		// reference front() {};
		// const_reference front() const {};
		// reference back() {};
		// const_reference back() const {};

		//		MODIFIERS

		//	assign
		void push_front(const value_type& tmp);
		//	pop front
		void push_back(const value_type& tmp);
		//	pop back
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
		typedef ft::__list_node<value_type>									__node;
		typedef typename allocator_type::template rebind<__node>::other	__node_allocator;
		typedef ft::__list_node<value_type>*								__node_pointer;
		
		__node_pointer	head;
		__node_pointer	ghost;
		allocator_type	__alloc;
		__node_allocator __node_alloc;

};



//###################################
//##	CONSTRUCTOR/DESTRUCTOR		#
//###################################

template <class T, class A>
void list<T,A>::push_front(const value_type& value)
{
	__node_pointer tmp = __node_alloc.allocate(1);
	tmp->data = value;
	tmp->next = head ? head : ghost;
	tmp->previous = ghost;
	ghost->next = tmp;
	if (!ghost->previous)
		ghost->previous = tmp;
	if (head)
		head->previous = tmp;
	head = tmp;
}

template <class T, class A>
void list<T,A>::push_back(const value_type& value)
{
	__node_pointer tmp = __node_alloc.allocate(1);
	tmp->data = value;
	tmp->next = ghost;
	if (!head) {
		tmp->previous = ghost;
		head = tmp;
	}
	else {
		tmp->previous = ghost->previous;
		ghost->previous->next = tmp;
	}
	ghost->previous = tmp;
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
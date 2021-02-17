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
	typedef std::ptrdiff_t		difference_type;
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


		list(const allocator_type &alloc = allocator_type()) : __alloc(alloc), __node_alloc() { ghost = __node_alloc.allocate(1); head = ghost;};
		// list(size_type n, const value_type &val = value_type(), const allocaotr_type &alloc = allocator_type());
		// template <class InputIT>
		// list(InputIT its, InputIT ite, const allocaotr_type &alloc = allocator_type());
		// list(const list<T>& tmp);
		//list const& operator=(list const &base);
		~list() {
			while (!empty())
				pop_front();
			delete ghost;
		};
		
		//		ITERATORS

		iterator begin() { return (head); };
		iterator end() { return (ghost); };
		reverse_iterator rbegin() { return (ft::prev(iterator(ghost))); };
		reverse_iterator rend() { return (ft::prev(iterator(head))); };
		const_iterator begin() const {
			typedef __list_node<const value_type>* __const_node;
			__const_node const_head = reinterpret_cast<__const_node>(head);
			return (const_head);
		};
		const_iterator end() const {
			typedef __list_node<const value_type>* __const_node;
			__const_node const_ghost = reinterpret_cast<__const_node>(ghost);
			return (const_ghost);
		};
		const_reverse_iterator rbegin() const { return (ft::prev(iterator(ghost))); };
		const_reverse_iterator rend() const { return (ft::prev(iterator(begin))); };

		//		CAPACITY

		bool empty() const {return (head == ghost); };
		size_type	size() const {
			return (ft::distance(begin(), end())); };
		size_type	max_size() const { return (__node_allocator().max_size()); };

		//		ELEMENT ACCESS

		reference front() { return head->data;};
		const_reference front() const {return head->data;};
		reference back() {return *ft::prev(end());};
		const_reference back() const {return ft::prev(end());};

		//		MODIFIERS

		//	assign
		void push_front(const value_type& tmp);
		void	pop_front() ;
		void push_back(const value_type& tmp);
		void	pop_back();
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


//####################################
//###		PUSH/POP FRONT/BACK		##
//####################################


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
	if (head == ghost) {
		tmp->previous = ghost;
		head = tmp;
		ghost->next = tmp;
	}
	else {
		tmp->previous = ghost->previous;
		ghost->previous->next = tmp;
	}
	ghost->previous = tmp;
}

template <class T, class A>
void	list<T,A>::pop_front()
{
	__node_pointer tmp = head->next;
	__node_alloc.destroy(head);
	delete head;
	head = tmp;
}

template <class T, class A>
void	list<T,A>::pop_back()
{
	__node_pointer tmp = ghost->previous;
	if (tmp == head) {
		head = ghost;
		ghost->next = 0;
		ghost->previous = 0;
	}
	else {
		tmp->previous->next = ghost;
		ghost->previous = tmp->previous;
	}
	__node_alloc.destroy(tmp);
	delete tmp;
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
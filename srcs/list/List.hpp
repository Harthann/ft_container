#ifndef LIST_HPP
#define LIST_HPP
#include <iostream>

namespace ft {

template <class T>
struct	__list_node {
	typedef T						value_type;
	typedef T*						pointer;
	typedef T&						reference;
	typedef __list_node<value_type>	__node;
	typedef __node*					__node_pointer;
	typedef __node&					__node_reference;

	value_type		data;
	__node_pointer	next;
	__node_pointer	previous;
};

template <class T, class Alloc = std::allocator<T> >
class List
{
	public:

		typedef T												value_type;
		typedef Alloc											allocator_type;
		typedef allocator_type::reference						reference;
		typedef allocator_type::const_reference					const_reference;
		typedef allocator_type::pointer							pointer;
		typedef allocator_type::const_pointer					const_pointer;
		typedef ft::list_iterator<T>							iterator;
		typedef ft::list_iterator<const T>						const_iterator;
		typedef ft::reverse_iterator<iterator>					reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
		typedef ft::iterator_traits<iterator>::difference_type	difference_type;
		typedef size_t											size_type;


		List() : head(0), __alloc() {};
		// List(const List<T>& tmp);
		~List() { delete head; }
		
		void push_front(T tmp);
		void push_back(T tmp);
		ft::List_iterator<T> begin();
		ft::List_iterator<T> end();
		ft::List_const_iterator<T> begin() const;
		ft::List_const_iterator<T> end() const;

	private:
		typedef __list_node<value_type>						__node;
		typedef __list_node<value_type>::__node_pointer		__node_pointer;
		typedef __list_node<value_type>::__node_reference	__node_reference;
		
		__node_pointer	head;
		allocator_type	__alloc;
};



//###################################
//##	CONSTRUCTOR/DESTRUCTOR		#
//###################################

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
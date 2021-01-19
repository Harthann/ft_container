#ifndef LIST_HPP
#define LIST_HPP
#include <iostream>

namespace ft {


#include "List_iterator.hpp"
#include "List_node.hpp"

// template <class T> class List_node;
// template <class T> class List_iterator;

template <class T>
class List
{
	public:

		typedef ft::List_iterator<T> iterator;
		typedef ft::List_const_iterator<T> const_iterator;

		List() : head(nullptr), tail(nullptr) {}
		// List(const List<T>& tmp);
		~List() { delete head; }
		
		void push_front(T tmp);
		void push_back(T tmp);
		ft::List_iterator<T> begin();
		ft::List_iterator<T> end();
		ft::List_const_iterator<T> begin() const;
		ft::List_const_iterator<T> end() const;

		void print(); // testing function, will be delete
	private:
		ft::List_node<T> *head;
		ft::List_node<T> *tail;

};



//###################################
//##	CONSTRUCTOR/DESTRUCTOR		#
//###################################

//###############################
//##							#
//###############################

template <class T>
void List<T>::push_front(T tmp)
{
	ft::List_node<T> *new_node = new ft::List_node<T>(tmp, head);
	if (!tail)
		tail = head;
	head = new_node;
	if (head->next)
		head->next->previous = head;
}

template <class T>
void List<T>::push_back(T tmp)
{
	ft::List_node<T> *new_node = new ft::List_node<T>(tmp, nullptr);

	new_node->previous = head;
	if (!head)
		head = new_node;
	else if (tail)
		tail->next = new_node;
	tail = new_node;
}

//###################
//#		ITERATOR	#
//###################

template <class T>
ft::List_iterator<T> List<T>::begin(void)
{
	return (ft::List_iterator<T>(head));
}

template <class T>
ft::List_iterator<T> List<T>::end(void)
{
	return (ft::List_iterator<T>(tail->next));
}

template <class T>
ft::List_const_iterator<T> List<T>::begin(void) const
{
	return (ft::List_const_iterator<T>(head));
}

template <class T>
ft::List_const_iterator<T> List<T>::end(void) const
{
	return (ft::List_const_iterator<T>(tail->next));
}

//###################
//#		OTHER		#
//###################

template <class T>
void List<T>::print()
{
	ft::List_node<T> *tmp = head;

	while (tmp)
	{
		std::cout << tmp->data;
		tmp = tmp->next;
		if (tmp) 
			std::cout << " --> ";
	}
	std::cout << "\n";
}

}
#endif
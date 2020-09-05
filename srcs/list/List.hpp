#ifndef LIST_HPP
#define LIST_HPP
#include <iostream>

namespace ftc {


#include "List_iterator.hpp"
#include "List_node.hpp"

// template <class T> class List_node;
// template <class T> class List_iterator;

template <class T>
class List
{
	public:

		typedef ftc::List_iterator<T> iterator;
		typedef ftc::List_const_iterator<T> const_iterator;

		List() : head(nullptr), tail(nullptr) {}
		// List(const List<T>& tmp);
		~List() { delete head; }
		
		void push_front(T tmp);
		void push_back(T tmp);
		ftc::List_iterator<T> begin();
		ftc::List_iterator<T> end();
		ftc::List_const_iterator<T> begin() const;
		ftc::List_const_iterator<T> end() const;

		void print(); // testing function, will be delete
	private:
		ftc::List_node<T> *head;
		ftc::List_node<T> *tail;

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
	ftc::List_node<T> *new_node = new ftc::List_node<T>(tmp, head);
	if (!tail)
		tail = head;
	head = new_node;
	if (head->next)
		head->next->previous = head;
}

template <class T>
void List<T>::push_back(T tmp)
{
	ftc::List_node<T> *new_node = new ftc::List_node<T>(tmp, nullptr);

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
ftc::List_iterator<T> List<T>::begin(void)
{
	return (ftc::List_iterator<T>(head));
}

template <class T>
ftc::List_iterator<T> List<T>::end(void)
{
	return (ftc::List_iterator<T>(tail->next));
}

template <class T>
ftc::List_const_iterator<T> List<T>::begin(void) const
{
	return (ftc::List_const_iterator<T>(head));
}

template <class T>
ftc::List_const_iterator<T> List<T>::end(void) const
{
	return (ftc::List_const_iterator<T>(tail->next));
}

//###################
//#		OTHER		#
//###################

template <class T>
void List<T>::print()
{
	ftc::List_node<T> *tmp = head;

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
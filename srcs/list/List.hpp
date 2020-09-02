#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>

template <typename T> class List;
template <typename T> class List_iterator;

template <typename T>
class list_node
{
	public:
		list_node(T data, list_node *ptr) : data(data), next(ptr) {}
		~list_node() { delete next; }

		friend class List<T>;
	private:
		T data;
		list_node *next;
};

template <typename T>
class List
{
	public:

		typedef list_iterator<T> iterator;

		List() : head(nullptr), tail(nullptr) {}
		// List(const List<T>& tmp);
		~List() { delete head; }
		
		void push_front(T tmp);
		void push_back(T tmp);
		// iterator begin(void) const;
		// iterator end(void) const;

		void print(); // testing function, will be delete
	private:
		list_node<T> *head;
		list_node<T> *tail;

};

template <typename T>
class list_iterator
{
	public:
		list_iterator()

	private:
		T *data;
}

//###################################
//##	CONSTRUCTOR/DESTRUCTOR		#
//###################################

// template <typename T>
// List<T>::List(const List<T>& tmp)
// {
	
// }

//###############################
//##							#
//###############################

template <typename T>
void List<T>::push_front(T tmp)
{
	list_node<T> *new_node = new list_node<T>(tmp, head);
	if (!tail)
		tail = head;
	head = new_node;
}

template <typename T>
void List<T>::push_back(T tmp)
{
	list_node<T> *new_node = new list_node<T>(tmp, nullptr);

	if (!head)
		head = new_node;
	else if (tail)
		tail->next = new_node;
	tail = new_node;
}

//###################
//#		ITERATOR	#
//###################

// template <typename T>
// List<T>::iterator List<T>::begin(void) const
// {
// 	return (iterator(this->first));
// }

// template <typename T>
// List<T>::iterator List<T>::end(void) const
// {
// 	List<T>::iterator it = this->begin();
// 	while (it->next)
// 		it = it->next;
// 	return (it);
// }

//###################
//#		OTHER		#
//###################

template <typename T>
void List<T>::print()
{
	list_node<T> *tmp = head;

	while (tmp)
	{
		std::cout << tmp->data;
		tmp = tmp->next;
		if (tmp) 
			std::cout << " --> ";
	}
	std::cout << "\n";
}

#endif
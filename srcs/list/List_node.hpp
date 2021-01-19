#ifndef LIST_NODE_HPP
#define LIST_NODE_HPP

namespace ft {

template <class T> class List;
template <class T> class List_iterator;

template <class T>
class List_node
{

	public:
		List_node(T data, List_node *ptr) :next(ptr), previous(nullptr),  data(data) {}
		~List_node() { delete next; }

		friend class List<T>;
		friend class List_iterator<T>;
		friend class List_const_iterator<T>;
		List_node *next; // Both next and previous need further test
		List_node *previous; // since i use my own namespace, friend class isn't enough to allow list to use it while they are private
	private:
		T data;
};

}
#endif
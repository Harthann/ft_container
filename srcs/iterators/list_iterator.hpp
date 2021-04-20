#ifndef LIST_ITERATOR_HPP
#define LIST_ITERATOR_HPP

#include "List.hpp"
#include "ft_iterator.hpp"

namespace ft {

template <class T> struct __list_node;
template <class T, class A> class list;

template <class T, bool B = false>
class   list_iterator
{
	public:
		typedef typename ft::is_const_if<B, T>::value_type	value_type;
		typedef value_type*								pointer;
		typedef value_type&								reference;
		typedef std::ptrdiff_t					difference_type;
		typedef ft::bidirectional_iterator_tag  iterator_category;
		template<class, class> friend class list;
	private:
		typedef ft::__list_node<value_type> __node;
		typedef __node*						__node_pointer;
		template <class, bool> friend class list_iterator;
	
	public:
		list_iterator() : node(0) {};
		list_iterator(__node_pointer const node) : node(node) {} ;
		list_iterator(const list_iterator<T>& base) : node(reinterpret_cast<__node_pointer>(base.node)) {} ;
		list_iterator &operator=(const list_iterator<T>& base) {
			node = reinterpret_cast<__node_pointer>(base.node);
			return *this;
		};

		reference operator*() { return node->data; };

		pointer operator->() { return (&node->data); };

		bool operator!=(const list_iterator& base) const {
			return (node != base.node);
		}

		bool operator==(const list_iterator& base) const {
			return (node == base.node);
		}

		list_iterator operator++() {
			node = node->next;
			return (*this);
		};
		
		list_iterator operator++(int) {
			list_iterator tmp(*this);
			node = node->next;
			return (tmp);
		};

		list_iterator operator--() {
			node = node->previous;
			return (*this);
		};
		
		list_iterator operator--(int) {
			list_iterator tmp(*this);
			node = node->previous;
			return (tmp);
		};

	private:
		__node*	node;
};


}

#endif
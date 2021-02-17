#ifndef LIST_ITERATOR_HPP
#define LIST_ITERATOR_HPP

#include "List.hpp"
#include "ft_iterator.hpp"

namespace ft {

template <class T> struct __list_node;

template <class T>
class   list_iterator
{
	public:
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef const T*						const_pointer;
		typedef const T&						const_reference;
		typedef std::ptrdiff_t					difference_type;
		typedef ft::bidirectional_iterator_tag  iterator_category;
	
		list_iterator() : node(0) {};
		// list_iterator(ft::__list_node<T>* node) : node(node) {} ;
		list_iterator(ft::__list_node<T>* const node) : node(node) {} ;
		list_iterator(const list_iterator& base) : node(base.node) {} ;
		list_iterator &operator=(const list_iterator& base) {node = base.node; return *this; };

		reference operator*() { return node->data; };
		const_reference operator*() const { return node->data; };

		pointer operator->() { return (&node->data); };
		const_pointer operator->() const { return (&node->data); };

		bool operator!=(const list_iterator<value_type>& base) const {
			return (node != base.node);
		}

		bool operator==(const list_iterator<value_type>& base) const {
			return (node == base.node);
		}

		list_iterator<value_type> operator++() {
			node = node->next;
			return (*this);
		};
		
		list_iterator<value_type> operator++(int) {
			list_iterator<value_type> tmp(*this);
			node = node->next;
			return (tmp);
		};

		list_iterator<value_type> operator--() {
			node = node->previous;
			return (*this);
		};
		
		list_iterator<value_type> operator--(int) {
			list_iterator<value_type> tmp(*this);
			node = node->previous;
			return (tmp);
		};

	private:
		typedef ft::__list_node<T> __node;
		__node*	node;
};

}

#endif
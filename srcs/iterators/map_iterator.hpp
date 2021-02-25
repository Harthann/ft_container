#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include "Map.hpp"
#include "ft_iterator.hpp"

namespace ft {

template <class T> struct __map_node;

template <class T, class Comp>
class map_iterator
{

	public:
		typedef T*							pointer;
		typedef T&							reference;
		typedef T							value_type;
		typedef std::ptrdiff_t				difference_type;
		typedef	ft::bidirectional_iterator_tag		iterator_category;

		map_iterator() : node() {};
		map_iterator(const map_iterator & x) : node(x.node) {};
		map_iterator &operator=(const map_iterator & x) {node = x.node; return *this; };
		map_iterator(ft::__map_node<value_type>* const x) : node(x) {};

		bool operator!=(const map_iterator<value_type, Comp>& base) const {
			return (node != base.node);
		}

		bool operator==(const map_iterator<value_type, Comp>& base) const {
			return (node == base.node);
		}
		reference operator*() {
			return ((*node).__pair);
		}

		pointer	operator->() {
			return (&(*node).__pair);
		}

		map_iterator<value_type, Comp> operator++() {
			if (!node->right && Comp()(node->__pair, node->parent->__pair))
				node = node->parent;
			else if (!node->right && Comp()(node->parent->__pair, node->__pair))
				node = node->parent->parent;
			else
				node = __findMin__(node->right);
			return *this;
		};

		map_iterator<value_type, Comp> operator++(int) {
			map_iterator<value_type, Comp> tmp(*this);
			operator++();
			return (tmp);
		};

		map_iterator<value_type, Comp> operator--() {
			if ((!node->left && Comp()(node->parent->__pair, node->__pair)) || (node->left == node->right))
				node = node->parent;
			else if (!node->left && Comp()(node->__pair, node->parent->__pair))
				node = node->parent->parent;
			else
				node = __findMax__(node->left);
			return *this;
		};

		map_iterator<value_type, Comp> operator--(int) {
			map_iterator<value_type, Comp> tmp(*this);
			operator--();
			return (tmp);
		};

	private:
		typedef ft::__map_node<T>		__node;
		typedef __node*					__node_pointer;
		typedef	__node&					__node_reference;
		typedef Comp					value_compare;
		template<class, class, class, class> friend class map;

		__node_pointer	__findMin__(__node_pointer);
		__node_pointer	__findMax__(__node_pointer);

	private:
		__node_pointer node;
};

template <class T, class Comp>
typename map_iterator<T,Comp>::__node_pointer map_iterator<T,Comp>::__findMin__(__node_pointer node)
{
	if (!node || (node->parent == node->left && node->parent == node->right))
		return node;
	while (node->left)
		node= node->left;
	return (node);
}

template <class T, class Comp>
typename map_iterator<T,Comp>::__node_pointer map_iterator<T,Comp>::__findMax__(__node_pointer node)
{
	if (!node)
		return node;
	while (node->right)
		node= node->right;
	return (node);
}



}

#endif
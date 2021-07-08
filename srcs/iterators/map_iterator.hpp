#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include "map.hpp"
#include "ft_iterator.hpp"

namespace ft {

template <class T> struct __map_node;
template <class T, class Comp> class map_const_iterator;

template <class T, class Comp, bool B = false>
class map_iterator
{
	public:
		typedef typename ft::is_const_if<B, T>::value_type	value_type;
		typedef value_type&									reference;
		typedef value_type*									pointer;
		typedef std::ptrdiff_t								difference_type;
		typedef	ft::bidirectional_iterator_tag				iterator_category;
	
	protected:
		typedef ft::__map_node<value_type>		__node;
		typedef __node*							__node_pointer;
		typedef	__node&							__node_reference;
		typedef Comp							value_compare;
		template<class, class, class, class> friend class map;
		template<class, class, bool> friend class map_iterator;

	public:
		map_iterator() : node() {};
		map_iterator(const map_iterator<T, Comp> & x) : node(reinterpret_cast<__node_pointer>(x.node)) {};
		map_iterator &operator=(const map_iterator<T, Comp> & x) {
			node = reinterpret_cast<__node_pointer>(x.node);
			return *this;
		};
		map_iterator(__node_pointer const x) : node(x) {};
		
		bool operator!=(const map_iterator& base) const {
			return (node != base.node);
		}

		bool operator==(const map_iterator& base) const {
			return (node == base.node);
		}
		reference operator*() {
			return ((*node).__pair);
		}

		pointer	operator->() {
			return (&(*node).__pair);
		}

		map_iterator operator++() {
			if (!node->right && value_compare()(node->__pair, node->parent->__pair))
				node = node->parent;
			else if (!node->right && value_compare()(node->parent->__pair, node->__pair))
				node = node->parent->parent;
			else
				node = __findMin__(node->right);
			return *this;
		};

		map_iterator operator++(int) {
			map_iterator tmp(*this);
			operator++();
			return (tmp);
		};

		map_iterator operator--() {
			if ((!node->left && Comp()(node->parent->__pair, node->__pair)) || (node->left == node->parent))
				node = node->parent;
			else if (!node->left && Comp()(node->__pair, node->parent->__pair))
				node = node->parent->parent;
			else
				node = __findMax__(node->left);
			return *this;
		};

		map_iterator operator--(int) {
			map_iterator tmp(*this);
			operator--();
			return (tmp);
		};

		// operator map_iterator<T, Comp, true>() const {
		// 	return (map_iterator<T, Comp, true>(*this));
		// }

	protected:
		// typedef ft::__map_node<T>		__node;
		__node_pointer	__findMin__(__node_pointer);
		__node_pointer	__findMax__(__node_pointer);

	protected:
		__node_pointer node;
};

template <class T, class Comp, bool B>
typename map_iterator<T,Comp, B>::__node_pointer map_iterator<T,Comp, B>::__findMin__(__node_pointer node)
{
	if (!node || (node->parent == node->left))
		return node;
	while (node->left)
		node= node->left;
	return (node);
}

template <class T, class Comp, bool B>
typename map_iterator<T,Comp, B>::__node_pointer map_iterator<T,Comp, B>::__findMax__(__node_pointer node)
{
	if (!node || (node->parent == node->right))
		return node;
	while (node->right)
		node= node->right;
	return (node);
}

}

#endif
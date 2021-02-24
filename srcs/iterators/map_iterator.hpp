#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include "Map.hpp"
#include "ft_iterator.hpp"

namespace ft {

template <class T> struct __map_node;

template <class T>
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

		bool operator!=(const map_iterator<value_type>& base) const {
			return (node != base.node);
		}

		bool operator==(const map_iterator<value_type>& base) const {
			return (node == base.node);
		}
		reference operator*() {
			return ((*node).__pair);
		}

		pointer	operator->() {
			return (&(*node).__pair);
		}

		map_iterator<value_type> operator++() {
			if (node->right)
				node = node->right;
			else {
				if (node->parent && node->parent->__pair.first > node->__pair.first)
					node = node->parent;
				else
					node = node->parent->parent;
			}
			return *this;
		};

		map_iterator<value_type> operator++(int) {
			map_iterator<value_type> tmp(*this);
			operator++();
			return (tmp);
		};

		map_iterator<value_type> operator--() {
			if (node->left)
				node = node->left;
			else {
				if (node->parent && node->parent->__pair.first > node->__pair.first)
					node = node->parent;
				else
					node = node->parent->parent;
			}
			return *this;
		};

		map_iterator<value_type> operator--(int) {
			map_iterator<value_type> tmp(*this);
			operator--();
			return (tmp);
		};

	private:
		typedef ft::__map_node<T>		__node;
		typedef __node*					__node_pointer;
		typedef	__node&					__node_reference;
		template<class, class, class, class> friend class map;

	private:
		__node_pointer node;
};

}

#endif